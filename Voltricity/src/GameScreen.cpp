#include "ScreenManager.h"
#include "GameScreen.h"
#include "Layout.h"

using namespace volt;

const game::ClockTick GameScreen::FULL_DROP_INTERVAL = game::ClockSecond(1.0);

GameScreen::GameScreen() 
	: _grid(30,22),
	_automaticDropMove(game::Direction::bottom, FULL_DROP_INTERVAL), 
	_manualDropMove(game::Direction::bottom, game::ClockSecond(0.075)),
	_horizontalMove(game::Direction::none, game::ClockSecond(0.08)),
	_rotationMove(game::Direction::none, game::ClockSecond(0.15)),
	_allowHardDrop(true)
{}

// todo: add repeat initial delay

void GameScreen::handleEvent(const sf::Event& e) {
	if (e.Type == sf::Event::KeyPressed) {
		switch(e.Key.Code) {
			case sf::Key::Left:
				processMoveCommand(game::Direction::left);
				break;
			case sf::Key::Right:
				processMoveCommand(game::Direction::right);
				break;
			case sf::Key::Down:
				processMoveCommand(game::Direction::bottom);
				break;
			case sf::Key::Z:
				processRotationCommand(game::Direction::left);
				break;
			case sf::Key::X:
				processRotationCommand(game::Direction::right);
				break;
			case sf::Key::Space:
				if (_allowHardDrop) {
					hardDrop();
					_allowHardDrop = false;
				}
				break;
		}
	} else if (e.Type == sf::Event::KeyReleased) {
		switch(e.Key.Code) {
			case sf::Key::Left:
				if (_horizontalMove.IsStarted() && _horizontalMove.GetDirection() == game::Direction::left)
					_horizontalMove.Stop();
				break;
			case sf::Key::Right:
				if (_horizontalMove.IsStarted() && _horizontalMove.GetDirection() == game::Direction::right)
					_horizontalMove.Stop();
				break;
			case sf::Key::Down:
				if (_manualDropMove.IsStarted()) {
					_manualDropMove.Stop();
					_automaticDropMove.Resume(_activeScreenTime);
				}
				break;
			case sf::Key::Up:
			case sf::Key::Z:
				if (_rotationMove.IsStarted() && _rotationMove.GetDirection() == game::Direction::left) {
					_rotationMove.Stop();
				}				
				break;
			case sf::Key::X:
				if (_rotationMove.IsStarted() && _rotationMove.GetDirection() == game::Direction::right) {
					_rotationMove.Stop();
				}
				break;
			case sf::Key::Space:
				_allowHardDrop = true;
				break;
		}

	}

}

void GameScreen::update() {
	sf::Event e;
	while(nextEvent(e))
		handleEvent(e);

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


void GameScreen::present() {
	_app->Clear(sf::Color(0,0,0));
	_app->Draw(_grid);
}

int GameScreen::onInit() {
	game::Layout layout = game::ScreenManager::GetLayout();
	layout.AlignDrawable(_grid, _grid.GetSize(), game::Direction::center, game::Direction::center);

	spawnNewPiece();

	return EXIT_SUCCESS;
}

void GameScreen::hardDrop() {
	bool dropped = false;
	do {
		dropped = _grid.MoveCurrentPieceBy(0, 1);
	} while (dropped);

	onPieceDropBottom();
}

void GameScreen::onPieceDropBottom() {
	// hit the bottom - attach piece and spawn next
	_grid.AttachCurrentPieceBlocksToGrid(true);
	_grid.ClearRows(_grid.GetCompletedRows());
	_grid.CompactClearedRows();
	spawnNewPiece();
}

void GameScreen::processMoveCommand(game::Direction::e direction) {
	IntervalMove& affectedMove = (direction ==  game::Direction::bottom) ? _manualDropMove : _horizontalMove;

	if (direction == game::Direction::bottom)
		if (!_automaticDropMove.IsPaused())
			_automaticDropMove.Pause(_activeScreenTime);

	if (!affectedMove.IsStarted() || affectedMove.GetDirection() != direction) {
		affectedMove.StartInDirection(_activeScreenTime, direction);
		movePiece(direction, 1);	// move by one immediately
	}
}

void GameScreen::processRotationCommand(game::Direction::e direction) {
	if (!_rotationMove.IsStarted() || _rotationMove.GetDirection() != direction) {
		_rotationMove.StartInDirection(_activeScreenTime, direction);
		
		if (!_grid.RotateCurrentPiece(direction)) {
			// encountered resistance
			_rotationMove.Pause(_activeScreenTime);
		}
	}
}


void GameScreen::movePiece(game::Direction::e direction, int units) {
	int step = (direction == game::Direction::left) ? -1 : 1;
	bool isHorizontal = (direction == game::Direction::left || direction == game::Direction::right);
	bool moveCommitted = false;
	bool reCheckResistance = false;

	if (units > 0 && direction == game::Direction::bottom)
	{
		// blocked or not on downwards movement, the row will change (spawn or drop one row)
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


void GameScreen::spawnNewPiece() {
	Piece piece = _pieceFactory.CreateRandomPiece();

	_grid.SetCurrentPiece(piece);
	_grid.MoveCurrentPieceTo(0,0);
	_automaticDropMove.Stop();
}