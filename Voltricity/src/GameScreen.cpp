#include "ScreenManager.h"
#include "ResourceManager.h"
#include "GameScreen.h"
#include "GameSettings.h"
#include "Layout.h"
#include "Utils.h"

using namespace volt;

GameScreen::GameScreen() 
	: _gameMechanics(), _showMenu(false)
{
	_gameMechanics.SetGameEventListener(this);
	_mainMenu.SetInGame(true);
}


void GameScreen::LevelChanged(int oldLevel, int newLevel) {
	_labelLevelDigits.SetText(game::Utils::IntToStr(newLevel));
}

void GameScreen::ScoreChanged(int oldScore, int newScore) {
	_labelScoreDigits.SetText(game::Utils::IntToStr(newScore));
}

void GameScreen::NextPieceSpawned(const Piece& nextPiece) {

}

void GameScreen::GameOver() {
	// get score
	// display score
	// read existing scores
	// is new high score (top 10)?
		// allow enter name (max 16 chars)
		// store score
}


void GameScreen::handleEvent(const sf::Event& e) {
	if (e.Type == sf::Event::KeyPressed) {
		
		if (_showMenu) {

			_mainMenu.HandleEvent(e);

			if (_mainMenu.CheckWasClosed()) {
				if (!_gameMechanics.IsGameOver())
					_gameMechanics.ResumeGame(_activeScreenTime);

				_showMenu = false;
				return;
			}

			switch (_mainMenu.CheckLastActivatedButton()) {
				case MainMenu::btnNewGame:
					_gameMechanics.StartNewGame(_activeScreenTime);
					_showMenu = false;
					break;
				case MainMenu::btnResumeGame:
					_gameMechanics.ResumeGame(_activeScreenTime);
					_showMenu = false;
					break;
				case MainMenu::btnAbout:
					game::ScreenManager::ActivateScreen("About");
					break;
				case MainMenu::btnExit:
					_showMenu = false;
					game::ResourceManager::GetApp()->Close();
					break;
			}


			return;
		}


		if (_gameMechanics.IsGameOver()) {
			// todo: move to enter high score
			
			game::ScreenManager::ActivateScreen("Highscore");

			/*
			switch(e.Key.Code) {
				case sf::Key::Escape:
					openMenu();
					break;

			}*/
			
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
				openMenu();
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
	if (_gameMechanics.IsRunning())
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


	if (_showMenu) {
		_app->Draw(_mainMenu);
	} else 	if (_gameMechanics.IsGameOver()) {
		_app->Draw(_labelGameOver);
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

	_labelGameOver = game::Label(sf::String("Game Over. Press Any Key.", game::ResourceManager::GetFont(), 20));
	_labelGameOver.SetBorder(1.0, sf::Color::Red);
	_labelGameOver.SetBackground(sf::Color::Black);
	game::ScreenManager::GetLayout().AlignDrawable(_labelGameOver, _labelGameOver.GetSize(), game::Direction::center);
}

void GameScreen::openMenu() {
	bool inGame = _gameMechanics.IsRunning();
	if (inGame)
		_gameMechanics.PauseGame(_activeScreenTime);
				
	_mainMenu.SelectFirst();
	_mainMenu.SetInGame(inGame);
	_showMenu = true;
}