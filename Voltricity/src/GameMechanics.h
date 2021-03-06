#ifndef GameMechanics_h__
#define GameMechanics_h__

#include "Grid.h"
#include "PieceFactory.h"
#include "IntervalMove.h"
#include "IGameEventListener.h"
#include "PieceQueue.h"
#include "TimeAccumulator.h"

namespace volt {


class GameMechanics {

public:
	GameMechanics();
	void SetGameEventListener(IGameEventListener* listener);
	void AdvanceGame(game::ClockTick activeScreenTime);
	void StartNewGame(game::ClockTick activeScreenTime);
	void PauseGame(game::ClockTick activeScreenTime);
	void ResumeGame(game::ClockTick activeScreenTime);


	void ProcessMoveCommand(game::Direction::e direction);
	void ProcessRotationCommand(game::Direction::e direction);
	void ProcessHardDropCommand();
	void ProcessMoveCommand_Release(game::Direction::e direction);
	void ProcessRotationCommand_Release(game::Direction::e direction);
	void ProcessHardDropCommand_Release();
	void ProcessHoldPieceSwapCommand_Release();

	int GetLevel() const;
	int GetScore() const;
	Grid& GetGrid();
	PieceQueue& GetPieceQueue();
	PieceQueue& GetHoldPieceQueue();

	bool IsPaused() const;
	bool IsGameOver() const;
	bool IsRunning() const;

private:
	void spawnSpecificPiece(PieceType::e pieceType);
	void spawnNextPieceFromQueue();

	void movePiece(game::Direction::e direction, int units);
	void hardDrop();
	void onPieceDropBottom();
	void onRowsCompleted(int numRows);
	void increaseLevel();

	static const game::ClockSecond FULL_DROP_INTERVAL;
	static const int ROWS_PER_LEVEL;

	Grid _grid;
	PieceQueue _pieceQueue;
	PieceQueue _holdPieceQueue;

	PieceFactory _pieceFactory;
	bool _allowHardDrop;
	bool _holdPieceInUse;
	game::ClockTick _activeGameTime;
	game::TimeAccumulator _timeAccumultor;

	IntervalMove _automaticDropMove;
	IntervalMove _manualDropMove;
	IntervalMove _horizontalMove;
	IntervalMove _rotationMove;

	int _level;
	int _rowsToNextLevel;
	int _score;

	bool _isPaused;
	bool _isGameOver;

	IGameEventListener* _gameEventListener;
	

};

}

#endif // GameMechanics_h__
