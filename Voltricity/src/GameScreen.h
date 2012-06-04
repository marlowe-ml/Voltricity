#ifndef GameScreen_h__
#define GameScreen_h__

#include "Screen.h"
#include "Grid.h"
#include "PieceFactory.h"
#include "Clock.h"
#include "IntervalMove.h"

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

	void spawnNewPiece();
	void processMoveCommand(game::Direction::e direction);
	void processRotationCommand(game::Direction::e direction);

	void movePiece(game::Direction::e direction, int units);
	void hardDrop();
	void onPieceDropBottom();

	static const game::ClockTick FULL_DROP_INTERVAL;

	Grid _grid;
	PieceFactory _pieceFactory;
	bool _allowHardDrop;

	IntervalMove _automaticDropMove;
	IntervalMove _manualDropMove;
	IntervalMove _horizontalMove;
	IntervalMove _rotationMove;

};


}





#endif // GameScreen_h__