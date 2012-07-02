#ifndef GameScreen_h__
#define GameScreen_h__

#include "Screen.h"
#include "Label.h"
#include "Grid.h"
#include "GameMechanics.h"

namespace volt {

class GameScreen : public game::Screen {

public:
	GameScreen();

protected:

	virtual void handleEvent(const sf::Event& e);
	virtual void update();
	virtual void present();

	virtual int onInit();

private:
	GameMechanics _gameMechanics;
	Grid _grid;

	game::Label _labelLevel;
	game::Label _labelLevelDigits;

	game::Label _labelScore;
	game::Label _labelScoreDigits;

	game::Label _labelNext;

	void alignLabels();
};


}





#endif // GameScreen_h__