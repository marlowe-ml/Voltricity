#ifndef GameMechanics_h__
#define GameMechanics_h__

#include "Grid.h"
#include "PieceFactory.h"
#include "IntervalMove.h"

namespace volt {

class GameMechanics {

public:
	GameMechanics(Grid& grid);
	void AdvanceGame(game::ClockTick activeScreenTime);
	void StartNewGame(game::ClockTick activeScreenTime);
	void ProcessMoveCommand(game::Direction::e direction);
	void ProcessRotationCommand(game::Direction::e direction);
	void ProcessHardDropCommand();
	void ProcessMoveCommand_Release(game::Direction::e direction);
	void ProcessRotationCommand_Release(game::Direction::e direction);
	void ProcessHardDropCommand_Release();


private:
	void spawnNewPiece();

	void movePiece(game::Direction::e direction, int units);
	void hardDrop();
	void onPieceDropBottom();

	static const game::ClockTick FULL_DROP_INTERVAL;

	Grid& _grid;
	PieceFactory _pieceFactory;
	bool _allowHardDrop;
	game::ClockTick _activeScreenTime;

	IntervalMove _automaticDropMove;
	IntervalMove _manualDropMove;
	IntervalMove _horizontalMove;
	IntervalMove _rotationMove;

	

};

}

#endif // GameMechanics_h__
