#ifndef PieceFactory_h__
#define PieceFactory_h__

#include "Piece.h"
#include "Random.h"

namespace volt {

class PieceFactory {
public:
	PieceFactory();
	Piece CreatePiece(PieceType::e piecetype) const;
	Piece CreatePiece(PieceType::e piecetype, sf::Vector2f blockSize) const;
	Piece CreateRandomPiece() const;
	Piece CreateRandomPiece(sf::Vector2f blockSize) const;
	
private:
	game::Random random;

};

}

#endif // PieceFactory_h__
