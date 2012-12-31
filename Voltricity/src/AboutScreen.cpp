#include "AboutScreen.h"
#include "ScreenManager.h"
#include "ResourceManager.h"

using namespace volt;

void AboutScreen::handleEvent(const sf::Event& e) {
	if (e.Type == sf::Event::KeyPressed) {
		game::ScreenManager::ActivateScreen("Game");
	}
}

void AboutScreen::update() {

}

void AboutScreen::present() {
	_app->Clear(sf::Color(0,0,0));
	_app->Draw(_labelAbout);
}

int AboutScreen::onInit() {
	std::string about = 
		"Puzzled - Copyright (c) 2011 by jvb\n\n"
		"Open source licensed under the MIT license\n"
		"Sources: https://github.com/marlowe-ml/Puzzled\n\n\n"
		"Using the SFML library by Laurent Gomila: http://www.sfml-dev.org\n\n\n"
		"Image by digitalART2: http://www.flickr.com/photos/digitalart\n\n\n\n\n"
		"- press a key to return to previous screen - ";
	_labelAbout = sf::String(about, game::ResourceManager::GetFont(), 20.0f);
	game::ScreenManager::GetLayout().AlignDrawable(_labelAbout, _labelAbout.GetSize(), game::Direction::center);
	return EXIT_SUCCESS;
}
