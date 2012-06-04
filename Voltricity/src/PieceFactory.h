#ifndef PieceFactory_h__
#define PieceFactory_h__

#include "Piece.h"
#include "Random.h"

namespace volt {

class PieceFactory {
public:
	PieceFactory();
	Piece CreateRandomPiece() const;

private:
	game::Random random;

};

}

#endif // PieceFactory_h__
