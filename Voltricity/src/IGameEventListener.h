#ifndef IGameEventListener_h__
#define IGameEventListener_h__

#include "Piece.h"

namespace volt {

class IGameEventListener {
public:
	virtual void LevelChanged(int oldLevel, int newLevel) = 0;
	virtual void ScoreChanged(int oldScore, int newScore) = 0;
	virtual void NextPieceSpawned(const Piece& nextPiece) = 0;
};

}

#endif // IGameEventListener_h__
