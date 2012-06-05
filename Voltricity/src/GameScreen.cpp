#include "ScreenManager.h"
#include "GameScreen.h"
#include "Layout.h"

using namespace volt;

GameScreen::GameScreen() 
: _grid(10, 22), _gameMechanics(_grid)
{}

void GameScreen::handleEvent(const sf::Event& e) {
	if (e.Type == sf::Event::KeyPressed) {
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
		}

	}

}

void GameScreen::update() {
	sf::Event e;
	while(nextEvent(e))
		handleEvent(e);
	
	_gameMechanics.AdvanceGame(_activeScreenTime);

}


void GameScreen::present() {
	_app->Clear(sf::Color(0,0,0));
	_app->Draw(_grid);
}

int GameScreen::onInit() {
	game::Layout layout = game::ScreenManager::GetLayout();
	layout.AlignDrawable(_grid, _grid.GetSize(), game::Direction::center, game::Direction::center);

	// todo: align labels for score, level, nect piece(s), hold piece, etc.

	_gameMechanics.StartNewGame(_activeScreenTime);

	return EXIT_SUCCESS;
}
