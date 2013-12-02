#include "HighscoreScreen.h"
#include "ScreenManager.h"
#include "GlobalState.h"

using namespace volt;

HighscoreScreen::HighscoreScreen() : _isEnteringScore(false), _highscoreInputField(10) {

}

void HighscoreScreen::handleEvent(const sf::Event& e) {
	if (_isEnteringScore || true) {
		_highscoreInputField.HandleEvent(e);
	}
}


void HighscoreScreen::update() {

}


void HighscoreScreen::present() {
	_app->Clear(sf::Color(0,0,0));
	if (_isEnteringScore)
		_app->Draw(_highscoreInputField);
	else
		_app->Draw(_buttonList);
	// show highscore entry if new high score
}

int HighscoreScreen::onInit() {
	// todo: read scores

	if (GlobalState::HighscoreEntryPending) {
		// todo: check if an actual highscore was reached --> maybe store the score in global state
		_isEnteringScore = true;
		GlobalState::HighscoreEntryPending = false;
	}

	//_highscoreInputField.SetText("TEST");
	_highscoreInputField.SetBorder(1.0f, sf::Color::Red);
	_buttonList.addButton("Marlowe - 10000", 0);
	_buttonList.addButton("Paulchen - 5000", 0);
	_buttonList.addButton("Lisbet - 3000", 0);		
	
	
	game::ScreenManager::GetLayout().AlignDrawable(_highscoreInputField, _highscoreInputField.GetSize(), game::Direction::center);

	return EXIT_SUCCESS;
}

// todo: if set, display score and name entry
/*
void HighscoreScreen::setHighscoreEntry(int score) {
	
}*/