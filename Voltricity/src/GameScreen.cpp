#include "ScreenManager.h"
#include "ResourceManager.h"
#include "GameScreen.h"
#include "GameSettings.h"
#include "Layout.h"
#include "Utils.h"

using namespace volt;

void GameScreen::LevelChanged(int oldLevel, int newLevel) {
	_labelLevelDigits.SetText(game::Utils::IntToStr(newLevel));
}

void GameScreen::ScoreChanged(int oldScore, int newScore) {
	_labelScoreDigits.SetText(game::Utils::IntToStr(newScore));
}

void GameScreen::NextPieceSpawned(const Piece& nextPiece) {

}

GameScreen::GameScreen() 
: _gameMechanics()
{
	_gameMechanics.SetGameEventListener(this);
	_mainMenu.SetInGame(true);
}

void GameScreen::handleEvent(const sf::Event& e) {
	if (e.Type == sf::Event::KeyPressed) {
		
		if (_gameMechanics.IsPaused()) {
			_mainMenu.HandleEvent(e);
			if (_mainMenu.CheckWasClosed()) {
				_gameMechanics.ResumeGame(_activeScreenTime);
			}
			return;
		}

		switch(e.Key.Code) {
			case sf::Key::Left:
				_gameMechanics.ProcessMoveCommand(game::Direction::left);
				break;
			case sf::Key::Right:
				_gameMechanics.ProcessMoveCommand(game::Direction::right);
				break;
			case sf::Key::Down:
				_gameMechanics.ProcessMoveCommand(game::Direction::bottom);
				break;
			case sf::Key::Z:
				_gameMechanics.ProcessRotationCommand(game::Direction::left);
				break;
			case sf::Key::X:
				_gameMechanics.ProcessRotationCommand(game::Direction::right);
				break;
			case sf::Key::Space:
				_gameMechanics.ProcessHardDropCommand();
				break;
			case sf::Key::Escape:
				_gameMechanics.PauseGame(_activeScreenTime);
				break;

		}
	} else if (e.Type == sf::Event::KeyReleased) {
		switch(e.Key.Code) {
			case sf::Key::Left:
				_gameMechanics.ProcessMoveCommand_Release(game::Direction::left);
				break;
			case sf::Key::Right:
				_gameMechanics.ProcessMoveCommand_Release(game::Direction::right);
				break;
			case sf::Key::Down:
				_gameMechanics.ProcessMoveCommand_Release(game::Direction::bottom);
				break;
			case sf::Key::Up:
			case sf::Key::Z:
				_gameMechanics.ProcessRotationCommand_Release(game::Direction::left);
				break;
			case sf::Key::X:
				_gameMechanics.ProcessRotationCommand_Release(game::Direction::right);
				break;
			case sf::Key::Space:
				_gameMechanics.ProcessHardDropCommand_Release();
				break;
			case sf::Key::LShift:
			case sf::Key::RShift:
				_gameMechanics.ProcessHoldPieceSwapCommand_Release();
				break;
		}

	}

}

void GameScreen::update() {
	sf::Event e;
	while(nextEvent(e))
		handleEvent(e);
	
	if (!_gameMechanics.IsPaused())
		_gameMechanics.AdvanceGame(_activeScreenTime);

}


void GameScreen::present() {
	_app->Clear(sf::Color(0,0,0));

	_app->Draw(_gameMechanics.GetGrid());
	_app->Draw(_labelLevel);
	_app->Draw(_labelLevelDigits);
	_app->Draw(_labelScore);
	_app->Draw(_labelScoreDigits);
	_app->Draw(_labelNext);
	_app->Draw(_gameMechanics.GetPieceQueue());
	_app->Draw(_gameMechanics.GetHoldPieceQueue());


	if (_gameMechanics.IsPaused()) {
		_app->Draw(_mainMenu);
	}



}

int GameScreen::onInit() {
	Grid& grid = _gameMechanics.GetGrid();

	game::ScreenManager::GetLayout().AlignDrawable(grid, grid.GetSize(), game::Direction::center);
	alignLabels();

	PieceQueue& pieceQueue = _gameMechanics.GetPieceQueue();	
	float pieceQueueOffset_x = (_labelNext.GetSize().x - pieceQueue.GetSize().x) / 2;
	pieceQueue.SetPosition(_labelNext.GetPosition().x + pieceQueueOffset_x, _labelNext.GetPosition().y + 20);

	// align hold piece
	PieceQueue& holdPieceQueue = _gameMechanics.GetHoldPieceQueue();	
	holdPieceQueue.SetPosition(pieceQueue.GetPosition().x - holdPieceQueue.GetSize().x - 10, pieceQueue.GetPosition().y);


	_gameMechanics.StartNewGame(_activeScreenTime);

	return EXIT_SUCCESS;
}

void GameScreen::alignLabels() {
	Grid& grid = _gameMechanics.GetGrid();

	sf::Vector2f gridTopRight = sf::Vector2f(grid.GetPosition().x + grid.GetSize().x, grid.GetPosition().y);

	sf::FloatRect eastRect = sf::FloatRect(gridTopRight.x, gridTopRight.y, game::ScreenManager::GetLayout().GetRect().Right, grid.GetPosition().y + grid.GetSize().y);

	game::Layout eastSection = game::Layout(eastRect);

	_labelLevel = game::Label(sf::String("Voltage", game::ResourceManager::GetFont(), 20));
	_labelLevel.SetPosition(grid.GetPosition().x + grid.GetSize().x + 10, grid.GetPosition().y);

	_labelLevelDigits = game::Label(sf::String("0", game::ResourceManager::GetFont(), 20));
	_labelLevelDigits.SetPosition(_labelLevel.GetPosition().x, _labelLevel.GetPosition().y + _labelLevel.GetSize().y);


	_labelScore = game::Label(sf::String("Score", game::ResourceManager::GetFont(), 20));
	_labelScore.SetPosition(_labelLevelDigits.GetPosition().x, _labelLevelDigits.GetPosition().y + _labelLevelDigits.GetSize().y + 20);

	_labelScoreDigits = game::Label(sf::String("0", game::ResourceManager::GetFont(), 20));
	_labelScoreDigits.SetPosition(_labelScore.GetPosition().x, _labelScore.GetPosition().y + _labelScore.GetSize().y);

	_labelNext = game::Label(sf::String("Next", game::ResourceManager::GetFont(), 20));
	_labelNext.SetPosition(grid.GetPosition().x - _labelNext.GetSize().x - 10, grid.GetPosition().y);
}
