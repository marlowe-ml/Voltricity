#ifndef HighscoreScreen_h__
#define HighscoreScreen_h__

#include "Screen.h"
#include "Label.h"
#include "InputField.h"
#include "ButtonList.h"

namespace volt {

class HighscoreScreen : public game::Screen {

public:
	HighscoreScreen();

protected:

	virtual void handleEvent(const sf::Event& e);
	virtual void update();
	virtual void present();

	virtual int onInit();

private:
	ButtonList _buttonList;
	game::InputField _highscoreInputField;
	game::Label _highscoreEntryLabel;
	bool _isEnteringScore;

};

}


#endif
