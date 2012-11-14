#ifndef GameScreen_h__
#define GameScreen_h__

#include "Screen.h"
#include "IGameEventListener.h"
#include "GameMechanics.h"
#include "Grid.h"
#include "Label.h"
#include "PieceQueue.h"
#include "MainMenu.h"

namespace volt {

class GameScreen : public game::Screen, public IGameEventListener {

public:
	GameScreen();

	virtual void LevelChanged(int oldLevel, int newLevel);
	virtual void ScoreChanged(int oldScore, int newScore);
	virtual void NextPieceSpawned(const Piece& nextPiece);


protected:

	virtual void handleEvent(const sf::Event& e);
	virtual void update();
	virtual void present();

	virtual int onInit();

private:
	GameMechanics _gameMechanics;

	game::Label _labelLevel;
	game::Label _labelLevelDigits;

	game::Label _labelScore;
	game::Label _labelScoreDigits;

	game::Label _labelNext;

	sf::Vector2f _holdPiecePos;

	MainMenu _mainMenu;

	void alignLabels();
};


}





#endif // GameScreen_h__