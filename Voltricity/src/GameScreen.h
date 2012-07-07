#ifndef GameScreen_h__
#define GameScreen_h__

#include "Screen.h"
#include "IGameEventListener.h"
#include "GameMechanics.h"
#include "Grid.h"
#include "Label.h"
#include "PieceQueue.h"

namespace volt {

class GameScreen : public game::Screen, public IGameEventListener {

public:
	GameScreen();

	virtual void LevelChanged(int oldLevel, int newLevel);
	virtual void ScoreChanged(int oldScore, int newScore);
	virtual void NextPieceSpawned(const Piece& newPiece, const Piece& nextPiece);


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

	PieceQueue _pieceQueue;

	void alignLabels();
};


}





#endif // GameScreen_h__