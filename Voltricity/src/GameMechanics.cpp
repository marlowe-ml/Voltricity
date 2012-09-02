#include "GameMechanics.h"
#include "Clock.h"
#include "Layout.h"
#include "ScreenManager.h"
#include "GameSettings.h"

using namespace volt;

const game::ClockSecond GameMechanics::FULL_DROP_INTERVAL = game::ClockSecond(1.0);
const int GameMechanics::ROWS_PER_LEVEL = 1;
// todo: add repeat initial delay

GameMechanics::GameMechanics(Grid& grid, PieceQueue& pieceQueue) : _grid(grid), _pieceQueue(pieceQueue),
_automaticDropMove(game::Direction::bottom, FULL_DROP_INTERVAL), 
_manualDropMove(game::Direction::bottom, game::ClockSecond(0.075)),
_horizontalMove(game::Direction::none, game::ClockSecond(0.08)),
_rotationMove(game::Direction::none, game::ClockSecond(0.15)),
_allowHardDrop(true), _gameEventListener(NULL)
{}

void GameMechanics::SetGameEventListener(IGameEventListener* listener) {
	_gameEventListener = listener;
}

void GameMechanics::StartNewGame(game::ClockTick activeScreenTime) {
	_level = 0;
	_score = 0;
	_rowsToNextLevel = ROWS_PER_LEVEL;

	
	int maxPieces = _pieceQueue.GetMaxPieces();
	for (int i=0; i<maxPieces; i++) {
		_pieceQueue.PushNewPiece(_pieceFactory.CreateRandomPiece(GameSettings::BlockSizeForQueue));			
	}

	spawnNextPiece();
}


void GameMechanics::AdvanceGame(game::ClockTick activeScreenTime) {
	_activeScreenTime = activeScreenTime;

	int moveDistance = 0;

	if (!_automaticDropMove.IsStarted() && !_automaticDropMove.IsPaused())
		_automaticDropMove.Start(_activeScreenTime);

	moveDistance = _automaticDropMove.DistanceUnitsSinceLastMove(_activeScreenTime);
	movePiece(_automaticDropMove.GetDirection(), moveDistance);

	if (_horizontalMove.IsStarted()) {
		moveDistance = _horizontalMove.DistanceUnitsSinceLastMove(_activeScreenTime);
		movePiece(_horizontalMove.GetDirection(), moveDistance);
	}

	if (_manualDropMove.IsStarted()) {
		moveDistance = _manualDropMove.DistanceUnitsSinceLastMove(_activeScreenTime);
		movePiece(_manualDropMove.GetDirection(), moveDistance);
	}

	if (_rotationMove.IsStarted()) {
		moveDistance = _rotationMove.DistanceUnitsSinceLastMove(_activeScreenTime);
		while (moveDistance > 0) {
			if (!_grid.RotateCurrentPiece(_rotationMove.GetDirection())) {
				// rotation blocked
				_rotationMove.Pause(_activeScreenTime);
			}

			moveDistance--;
		}
	}
}

void GameMechanics::ProcessMoveCommand(game::Direction::e direction) {
	IntervalMove& affectedMove = (direction ==  game::Direction::bottom) ? _manualDropMove : _horizontalMove;

	if (direction == game::Direction::bottom)
		if (!_automaticDropMove.IsPaused())
			_automaticDropMove.Pause(_activeScreenTime);

	if (!affectedMove.IsStarted() || affectedMove.GetDirection() != direction) {
		affectedMove.StartInDirection(_activeScreenTime, direction);
		movePiece(direction, 1);	// move by one immediately
	}
}

void GameMechanics::ProcessMoveCommand_Release(game::Direction::e direction) {
	if (direction == game::Direction::bottom) {
		if (_manualDropMove.IsStarted()) {
			_manualDropMove.Stop();
			_automaticDropMove.Resume(_activeScreenTime);
		}
	} else if (_horizontalMove.IsStarted() && _horizontalMove.GetDirection() == direction) {
		_horizontalMove.Stop();
	}
}

void GameMechanics::ProcessRotationCommand(game::Direction::e direction) {
	if (!_rotationMove.IsStarted() || _rotationMove.GetDirection() != direction) {
		_rotationMove.StartInDirection(_activeScreenTime, direction);

		if (!_grid.RotateCurrentPiece(direction)) {
			// encountered resistance
			_rotationMove.Pause(_activeScreenTime);
		}
	}
}

void GameMechanics::ProcessRotationCommand_Release(game::Direction::e direction) {
	if (_rotationMove.IsStarted() && _rotationMove.GetDirection() == direction) {
		_rotationMove.Stop();
	}				
}

void GameMechanics::ProcessHardDropCommand() {
	if (_allowHardDrop) {
		hardDrop();
		_allowHardDrop = false;
	}
}


void GameMechanics::ProcessHardDropCommand_Release() {
	_allowHardDrop = true;
}

int GameMechanics::GetLevel() const {
	return _level;
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
			_horizontalMove.Resume(_activeScreenTime);

		if (_rotationMove.IsPaused())
			_rotationMove.Resume(_activeScreenTime);
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
				_horizontalMove.Pause(_activeScreenTime);
			}
		}
		units--;
	}

}


void GameMechanics::spawnNextPiece() {
	Piece nextFromQueue = _pieceQueue.PushNewPiece(_pieceFactory.CreateRandomPiece(GameSettings::BlockSizeForQueue));
	
	Piece nextPiece = _pieceFactory.CreatePiece(nextFromQueue.GetPieceType());
	 nextPiece.SetPosition(sf::Vector2f(0,0));

	_grid.SetCurrentPiece(nextPiece);
	_grid.MoveCurrentPieceTo(0,0);
	_automaticDropMove.Stop();

	_gameEventListener->NextPieceSpawned(nextPiece);
}

void GameMechanics::hardDrop() {
	bool dropped = false;
	do {
		dropped = _grid.MoveCurrentPieceBy(0, 1);
	} while (dropped);

	onPieceDropBottom();
}

void GameMechanics::onPieceDropBottom() {
	// hit the bottom - attach piece and spawn next
	_grid.AttachCurrentPieceBlocksToGrid(true);
	std::vector<int> completedRows = _grid.GetCompletedRows();
	_grid.ClearRows(completedRows);
	_grid.CompactClearedRows();

	onRowsCompleted(completedRows.size());

	spawnNextPiece();
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