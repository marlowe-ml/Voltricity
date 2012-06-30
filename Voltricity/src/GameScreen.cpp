#include "ScreenManager.h"
#include "ResourceManager.h"
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
	_app->Draw(_labelLevel);
	_app->Draw(_labelLevelDigits);
}

int GameScreen::onInit() {
	game::ScreenManager::GetLayout().AlignDrawable(_grid, _grid.GetSize(), game::Direction::center);
	alignLabels();

	_gameMechanics.StartNewGame(_activeScreenTime);
	return EXIT_SUCCESS;
}

void GameScreen::alignLabels() {
	sf::Vector2f gridTopRight = sf::Vector2f(_grid.GetPosition().x + _grid.GetSize().x, _grid.GetPosition().y);

	sf::FloatRect eastRect = sf::FloatRect(gridTopRight.x, gridTopRight.y, game::ScreenManager::GetLayout().GetRect().Right, _grid.GetPosition().y + _grid.GetSize().y);

	game::Layout eastSection = game::Layout(eastRect);

	_labelLevel = game::Label(sf::String("Voltage", game::ResourceManager::GetFont(), 20));
	eastSection.AlignDrawable(_labelLevel, _labelLevel.GetSize(), game::Direction::topleft, sf::Vector2f(10,0));

	_labelLevelDigits = game::Label(sf::String("000", game::ResourceManager::GetFont(), 20));
	_labelLevelDigits.SetPosition(_labelLevel.GetPosition().x, _labelLevel.GetPosition().y + _labelLevel.GetSize().y);


}
