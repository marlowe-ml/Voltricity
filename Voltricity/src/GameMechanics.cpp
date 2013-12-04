#include "GameMechanics.h"
#include "Clock.h"
#include "Layout.h"
#include "ScreenManager.h"
#include "GameSettings.h"

using namespace volt;

const game::ClockSecond GameMechanics::FULL_DROP_INTERVAL = game::ClockSecond(1.0);
const int GameMechanics::ROWS_PER_LEVEL = 1;
// todo: add repeat initial delay

GameMechanics::GameMechanics() : _grid(10, 22), _pieceQueue(4), _holdPieceQueue(1),
_automaticDropMove(game::Direction::bottom, FULL_DROP_INTERVAL), 
_manualDropMove(game::Direction::bottom, game::ClockSecond(0.075)),
_horizontalMove(game::Direction::none, game::ClockSecond(0.08)),
_rotationMove(game::Direction::none, game::ClockSecond(0.15)),
_allowHardDrop(true), _holdPieceInUse(false), _gameEventListener(NULL), _isPaused(false), _isGameOver(false)
{
}


void GameMechanics::SetGameEventListener(IGameEventListener* listener) {
	_gameEventListener = listener;
}

Grid& GameMechanics::GetGrid() {
	return _grid;
}

PieceQueue& GameMechanics::GetPieceQueue() {
	return _pieceQueue;
}

PieceQueue& GameMechanics::GetHoldPieceQueue() {
	return _holdPieceQueue;
}

int GameMechanics::GetLevel() const {
	return _level;
}

int GameMechanics::GetScore() const {
	return _score;
}


void GameMechanics::StartNewGame(game::ClockTick activeScreenTime) {
	_level = 0;
	_score = 0;

	_gameEventListener->LevelChanged(0, 0);
	_gameEventListener->ScoreChanged(0, 0);

	_grid.Clear();

	_rowsToNextLevel = ROWS_PER_LEVEL;

	_isPaused = false;
	_isGameOver = false;
	_timeAccumultor.Reset();
	_automaticDropMove.SetDelayBetweenMoves(FULL_DROP_INTERVAL);
	
	int maxPieces = _pieceQueue.GetMaxPieces();
	for (int i=0; i<maxPieces; i++) {
		_pieceQueue.PushNewPiece(_pieceFactory.CreateRandomPiece(GameSettings::BlockSizeForQueue));			
	}

	spawnNextPieceFromQueue();
}


void GameMechanics::AdvanceGame(game::ClockTick activeScreenTime) {
	if (_isPaused)
		return;

	_timeAccumultor.AccumulateElapsedTime(activeScreenTime);

	_activeGameTime = _timeAccumultor.GetAccumulatedTime();
	

	int moveDistance = 0;

	if (!_automaticDropMove.IsStarted() && !_automaticDropMove.IsPaused())
		_automaticDropMove.Start(_activeGameTime);

	moveDistance = _automaticDropMove.DistanceUnitsSinceLastMove(_activeGameTime);
	movePiece(_automaticDropMove.GetDirection(), moveDistance);

	if (_horizontalMove.IsStarted()) {
		moveDistance = _horizontalMove.DistanceUnitsSinceLastMove(_activeGameTime);
		movePiece(_horizontalMove.GetDirection(), moveDistance);
	}

	if (_manualDropMove.IsStarted()) {
		moveDistance = _manualDropMove.DistanceUnitsSinceLastMove(_activeGameTime);
		movePiece(_manualDropMove.GetDirection(), moveDistance);
	}

	if (_rotationMove.IsStarted()) {
		moveDistance = _rotationMove.DistanceUnitsSinceLastMove(_activeGameTime);
		while (moveDistance > 0) {
			if (!_grid.RotateCurrentPiece(_rotationMove.GetDirection())) {
				// rotation blocked
				_rotationMove.Pause(_activeGameTime);
			}

			moveDistance--;
		}
	}
}

void GameMechanics::PauseGame(game::ClockTick activeScreenTime) {
	_isPaused = true;
	_timeAccumultor.Pause(activeScreenTime);
}

void GameMechanics::ResumeGame(game::ClockTick activeScreenTime) {
	_isPaused = false;
}

bool GameMechanics::IsPaused() const {
	return _isPaused;
}

bool GameMechanics::IsGameOver() const {
	return _isGameOver;
}

bool GameMechanics::IsRunning() const {
	return !_isPaused && !_isGameOver;
}



void GameMechanics::ProcessMoveCommand(game::Direction::e direction) {
	if (_isPaused)
		return;

	IntervalMove& affectedMove = (direction ==  game::Direction::bottom) ? _manualDropMove : _horizontalMove;

	if (direction == game::Direction::bottom)
		if (!_automaticDropMove.IsPaused())
			_automaticDropMove.Pause(_activeGameTime);

	if (!affectedMove.IsStarted() || affectedMove.GetDirection() != direction) {
		affectedMove.StartInDirection(_activeGameTime, direction);
		movePiece(direction, 1);	// move by one immediately
	}
}

void GameMechanics::ProcessMoveCommand_Release(game::Direction::e direction) {
	if (_isPaused)
		return;

	if (direction == game::Direction::bottom) {
		if (_manualDropMove.IsStarted()) {
			_manualDropMove.Stop();
			_automaticDropMove.Resume(_activeGameTime);
		}
	} else if (_horizontalMove.IsStarted() && _horizontalMove.GetDirection() == direction) {
		_horizontalMove.Stop();
	}
}

void GameMechanics::ProcessRotationCommand(game::Direction::e direction) {
	if (_isPaused)
		return;

	if (!_rotationMove.IsStarted() || _rotationMove.GetDirection() != direction) {
		_rotationMove.StartInDirection(_activeGameTime, direction);

		// try to rotate immediately
		if (!_grid.RotateCurrentPiece(direction)) {
			// encountered resistance
			_rotationMove.Pause(_activeGameTime);
		}
	}
}

void GameMechanics::ProcessRotationCommand_Release(game::Direction::e direction) {
	if (_isPaused)
		return;

	if (_rotationMove.IsStarted() && _rotationMove.GetDirection() == direction) {
		_rotationMove.Stop();
	}				
}

void GameMechanics::ProcessHardDropCommand() {
	if (_isPaused)
		return;

	if (_allowHardDrop) {
		hardDrop();
		_allowHardDrop = false;
	}
}


void GameMechanics::ProcessHardDropCommand_Release() {
	if (_isPaused)
		return;

	_allowHardDrop = true;
}


void GameMechanics::ProcessHoldPieceSwapCommand_Release() {
	if (_isPaused)
		return;

	if (_holdPieceInUse)
		return;

	_holdPieceInUse = true;

	PieceType::e currentPieceType = _grid.GetCurrentPiece().GetPieceType();

	Piece holdPiece = _holdPieceQueue.PushNewPiece(_pieceFactory.CreatePiece(currentPieceType, GameSettings::BlockSizeForQueue));

	PieceType::e holdPieceType = holdPiece.GetPieceType();

	if (holdPieceType == PieceType::none) {
		// no hold piece present yet
		spawnNextPieceFromQueue();
	} else {
		spawnSpecificPiece(holdPieceType);
	}
}


void GameMechanics::movePiece(game::Direction::e direction, int units) {
	int step = (direction == game::Direction::left) ? -1 : 1;
	bool isHorizontal = (direction == game::Direction::left || direction == game::Direction::right);
	bool moveCommitted = false;
	bool reCheckResistance = false;

	if (units > 0 && direction == game::Direction::bottom)
	{
		// blocked or not on downwards movement, the row will change (spawn new on first row or drop one row)
		if (_horizontalMove.IsPaused())
			_horizontalMove.Resume(_activeGameTime);

		if (_rotationMove.IsPaused())
			_rotationMove.Resume(_activeGameTime);
	}

	while (units > 0) {
		if (isHorizontal)
			moveCommitted = _grid.MoveCurrentPieceBy(step, 0);
		else
			moveCommitted = _grid.MoveCurrentPieceBy(0, step);

		if (!moveCommitted) {
			if (direction == game::Direction::bottom)
			{
				onPieceDropBottom();
			} else {
				// encountered resistance on horizontal level - hold movement
				_horizontalMove.Pause(_activeGameTime);
			}
		}
		units--;
	}

}

void GameMechanics::spawnSpecificPiece(PieceType::e pieceType) {
	Piece nextPiece = _pieceFactory.CreatePiece(pieceType);
	nextPiece.SetPosition(sf::Vector2f(0,0));

	_grid.SetCurrentPiece(nextPiece);
	if (_grid.MoveCurrentPieceTo(3,0)) {
		_gameEventListener->NextPieceSpawned(nextPiece);
	} else {
		_isGameOver = true;
		_gameEventListener->GameOver();
		std::cout << "game over";
	}
	_automaticDropMove.Stop();
}

void GameMechanics::spawnNextPieceFromQueue() {
	Piece nextFromQueue = _pieceQueue.PushNewPiece(_pieceFactory.CreateRandomPiece(GameSettings::BlockSizeForQueue));
	
	spawnSpecificPiece(nextFromQueue.GetPieceType());
}

void GameMechanics::hardDrop() {
	bool dropped = false;
	do {
		dropped = _grid.MoveCurrentPieceBy(0, 1);
	} while (dropped);

	onPieceDropBottom();
}

void GameMechanics::onPieceDropBottom() {
	_holdPieceInUse = false;
	
	// hit the bottom - attach piece and spawn next
	_grid.AttachCurrentPieceBlocksToGrid(true);
	std::vector<int> completedRows = _grid.GetCompletedRows();
	_grid.ClearRows(completedRows);
	_grid.CompactClearedRows();

	onRowsCompleted(completedRows.size());

	spawnNextPieceFromQueue();
}

void GameMechanics::onRowsCompleted(int numRows) {
	// todo: refine scoring, allow for combo points, timing
	int addScore = static_cast<int>(((_level+1) * 1.2) * static_cast<double>(numRows) * (static_cast<double>(numRows)/4.0) * 100.0);
	_gameEventListener->ScoreChanged(_score, _score+addScore);
	_score +=  addScore;

	while (numRows >= _rowsToNextLevel) {
		numRows -= _rowsToNextLevel;
		increaseLevel();
	}

	if (numRows > 0)
		_rowsToNextLevel -= numRows;
}

void GameMechanics::increaseLevel() {
	if (_gameEventListener!=NULL)
		_gameEventListener->LevelChanged(_level, _level+1);

	_level++;
	_rowsToNextLevel = ROWS_PER_LEVEL;

	game::ClockSecond dropInteval = _automaticDropMove.GetDelayBetweenMoves();
	dropInteval = static_cast<double>(dropInteval) * 0.92;
	_automaticDropMove.SetDelayBetweenMoves(dropInteval);

	std::cout << "level: " << _level << ", " << static_cast<double>(dropInteval) << std::endl;

	
}