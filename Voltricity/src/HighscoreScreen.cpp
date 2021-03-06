#include "HighscoreScreen.h"
#include "ScreenManager.h"
#include "ResourceManager.h"
#include "GlobalState.h"
#include "Highscore.h"
#include <sstream> 

using namespace volt;

HighscoreScreen::HighscoreScreen() : _isEnteringScore(false), _highscoreInputField(16) {
	_highscoreInputField.SetBorder(1.0f, sf::Color::Red);
}

void HighscoreScreen::handleEvent(const sf::Event& e) {
	if (_isEnteringScore) {
		_highscoreInputField.HandleEvent(e);
		if (_highscoreInputField.TextWasConfirmed())
		{
			std::string hsName = _highscoreInputField.GetText();
			Highscore hs = Highscore(GlobalState::PendingHighscoreForEntry, hsName);
			// todo: serialize, textual format?
			// .. hs.Serialize()
		}
	}
}


void HighscoreScreen::update() {

}


void HighscoreScreen::present() {
	_app->Clear(sf::Color(0,0,0));
	if (_isEnteringScore) {
		_app->Draw(_highscoreEntryLabel);
		_app->Draw(_highscoreInputField);
	}
	else
		_app->Draw(_buttonList);
	// show highscore entry if new high score
}


#include <stdio.h>  /* defines FILENAME_MAX */
    #include <direct.h>
    #define GetCurrentDir _getcwd



int HighscoreScreen::onInit() {
	// todo: read scores

 char cCurrentPath[FILENAME_MAX];

 if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
     {
     return errno;
     }

cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

printf ("The current working directory is %s", cCurrentPath);


	std::ifstream myfile ("Highscores.txt");

	bool isOpen = myfile.is_open();

	if (isOpen)
		std::cout << "file open" << std::endl;
	else
		std::cout << "file NOT open" << std::endl;

	Highscore hs(0, "");
	myfile >> hs;

	// todo: populate scores
	_buttonList.addButton("Marlowe - 10000", 0);
	_buttonList.addButton("Paulchen - 5000", 0);
	_buttonList.addButton("Lisbet - 3000", 0);
	
	game::ScreenManager::GetLayout().AlignDrawable(_highscoreInputField, _highscoreInputField.GetSize(), game::Direction::center);

	if (GlobalState::PendingHighscoreForEntry > 0) {
		// todo: check if an actual highscore was reached --> maybe store the score in global state
		std::stringstream sstm;
		sstm << "Congratulations! New Highscore: " << GlobalState::PendingHighscoreForEntry << "\n\nEnter Your Name:";
		_isEnteringScore = true;
		
		_highscoreEntryLabel.SetText(sf::String(sstm.str(), game::ResourceManager::GetFont(), 20));
		game::ScreenManager::GetLayout().AlignDrawable(_highscoreEntryLabel, _highscoreEntryLabel.GetSize(), game::Direction::center);
		_highscoreEntryLabel.SetY(_highscoreInputField.GetPosition().y - (_highscoreEntryLabel.GetSize().y * 1.5));
		

		// todo: remember to set pending score to 0 after entry has been completed
		// -- GlobalState::PendingHighscoreForEntry = 0;
	}

	return EXIT_SUCCESS;
}

// todo: if set, display score and name entry
/*
void HighscoreScreen::setHighscoreEntry(int score) {
	
}*/