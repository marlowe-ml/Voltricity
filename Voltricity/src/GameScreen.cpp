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
	_app->Draw(_labelScore);
	_app->Draw(_labelScoreDigits);
	_app->Draw(_labelNext);

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
	_labelLevel.SetPosition(_grid.GetPosition().x + _grid.GetSize().x + 10, _grid.GetPosition().y);

	_labelLevelDigits = game::Label(sf::String("000", game::ResourceManager::GetFont(), 20));
	_labelLevelDigits.SetPosition(_labelLevel.GetPosition().x, _labelLevel.GetPosition().y + _labelLevel.GetSize().y);


	_labelScore = game::Label(sf::String("Score", game::ResourceManager::GetFont(), 20));
	_labelScore.SetPosition(_labelLevelDigits.GetPosition().x, _labelLevelDigits.GetPosition().y + _labelLevelDigits.GetSize().y + 20);

	_labelScoreDigits = game::Label(sf::String("000000", game::ResourceManager::GetFont(), 20));
	_labelScoreDigits.SetPosition(_labelScore.GetPosition().x, _labelScore.GetPosition().y + _labelScore.GetSize().y);

	_labelNext = game::Label(sf::String("Next", game::ResourceManager::GetFont(), 20));
	_labelNext.SetPosition(_grid.GetPosition().x - _labelNext.GetSize().x - 10, _grid.GetPosition().y);

	// next: update the labels according to gameMechanics state
}
