#ifndef GameMechanics_h__
#define GameMechanics_h__

#include "Grid.h"
#include "PieceFactory.h"
#include "IntervalMove.h"
#include "IGameEventListener.h"

namespace volt {


class GameMechanics {

public:
	GameMechanics(Grid& grid);
	void SetGameEventListener(IGameEventListener* listener);
	void AdvanceGame(game::ClockTick activeScreenTime);
	void StartNewGame(game::ClockTick activeScreenTime);
	void ProcessMoveCommand(game::Direction::e direction);
	void ProcessRotationCommand(game::Direction::e direction);
	void ProcessHardDropCommand();
	void ProcessMoveCommand_Release(game::Direction::e direction);
	void ProcessRotationCommand_Release(game::Direction::e direction);
	void ProcessHardDropCommand_Release();
	int GetLevel() const;

private:
	void spawnNewPiece();

	void movePiece(game::Direction::e direction, int units);
	void hardDrop();
	void onPieceDropBottom();
	void onRowsCompleted(int numRows);
	void increaseLevel();

	static const game::ClockSecond FULL_DROP_INTERVAL;
	static const int ROWS_PER_LEVEL;

	Grid& _grid;
	PieceFactory _pieceFactory;
	bool _allowHardDrop;
	game::ClockTick _activeScreenTime;

	IntervalMove _automaticDropMove;
	IntervalMove _manualDropMove;
	IntervalMove _horizontalMove;
	IntervalMove _rotationMove;

	int _level;
	int _rowsToNextLevel;
	int _score;

	IGameEventListener* _gameEventListener;
	

};

}

#endif // GameMechanics_h__
