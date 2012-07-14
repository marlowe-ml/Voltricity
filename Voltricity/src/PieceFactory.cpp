#include "PieceFactory.h"
#include "GameSettings.h"

using namespace volt;

PieceFactory::PieceFactory() {}

Piece PieceFactory::CreatePiece(PieceType::e piecetype, sf::Vector2f blockSize) const {
	
	Piece piece = Piece(blockSize);

	PieceFrame frame = PieceFrame(3,3);

	switch (piecetype) {

	case PieceType::I:
		frame = PieceFrame(4, 4);
		frame.SetBlockAt(0, 1);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(2, 1);
		frame.SetBlockAt(3, 1);
		piece.AddFrame(frame);

		frame = PieceFrame(4, 4);
		frame.SetBlockAt(2, 0);
		frame.SetBlockAt(2, 1);
		frame.SetBlockAt(2, 2);
		frame.SetBlockAt(2, 3);
		piece.AddFrame(frame);

		frame = PieceFrame(4, 4);
		frame.SetBlockAt(0, 2);
		frame.SetBlockAt(1, 2);
		frame.SetBlockAt(2, 2);
		frame.SetBlockAt(3, 2);
		piece.AddFrame(frame);

		frame = PieceFrame(4, 4);
		frame.SetBlockAt(1, 0);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(1, 2);
		frame.SetBlockAt(1, 3);
		piece.AddFrame(frame);

		break;

	case PieceType::J:
		frame = PieceFrame(3, 3);
		frame.SetBlockAt(0, 0);
		frame.SetBlockAt(0, 1);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(2, 1);
		piece.AddFrame(frame);

		frame = PieceFrame(3, 3);
		frame.SetBlockAt(1, 0);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(1, 2);
		frame.SetBlockAt(2, 0);
		piece.AddFrame(frame);

		frame = PieceFrame(3, 3);
		frame.SetBlockAt(0, 1);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(2, 1);
		frame.SetBlockAt(2, 2);
		piece.AddFrame(frame);

		frame = PieceFrame(3, 3);
		frame.SetBlockAt(0, 2);
		frame.SetBlockAt(1, 0);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(1, 2);
		piece.AddFrame(frame);

		break;

	case PieceType::L:
		frame = PieceFrame(3, 3);
		frame.SetBlockAt(0, 1);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(2, 0);
		frame.SetBlockAt(2, 1);
		piece.AddFrame(frame);

		frame = PieceFrame(3, 3);
		frame.SetBlockAt(1, 0);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(1, 2);
		frame.SetBlockAt(2, 2);
		piece.AddFrame(frame);

		frame = PieceFrame(3, 3);
		frame.SetBlockAt(0, 1);
		frame.SetBlockAt(0, 2);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(2, 1);
		piece.AddFrame(frame);

		frame = PieceFrame(3, 3);
		frame.SetBlockAt(0, 0);
		frame.SetBlockAt(1, 0);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(1, 2);
		piece.AddFrame(frame);

		break;

	case PieceType::O:
		frame = PieceFrame(2, 2);
		frame.SetBlockAt(0, 0);
		frame.SetBlockAt(0, 1);
		frame.SetBlockAt(1, 0);
		frame.SetBlockAt(1, 1);
		piece.AddFrame(frame);

		break;

	case PieceType::S:
		frame = PieceFrame(3, 3);
		frame.SetBlockAt(0, 1);
		frame.SetBlockAt(1, 0);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(2, 0);
		piece.AddFrame(frame);

		frame = PieceFrame(3, 3);
		frame.SetBlockAt(1, 0);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(2, 1);
		frame.SetBlockAt(2, 2);
		piece.AddFrame(frame);

		frame = PieceFrame(3, 3);
		frame.SetBlockAt(0, 2);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(1, 2);
		frame.SetBlockAt(2, 1);
		piece.AddFrame(frame);

		frame = PieceFrame(3, 3);
		frame.SetBlockAt(0, 0);
		frame.SetBlockAt(0, 1);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(1, 2);
		piece.AddFrame(frame);

		break;

	case PieceType::T:
		frame = PieceFrame(3, 3);
		frame.SetBlockAt(1, 0);
		frame.SetBlockAt(0, 1);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(2, 1);
		piece.AddFrame(frame);

		frame = PieceFrame(3, 3);
		frame.SetBlockAt(1, 0);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(2, 1);
		frame.SetBlockAt(1, 2);
		piece.AddFrame(frame);

		frame = PieceFrame(3, 3);
		frame.SetBlockAt(0, 1);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(2, 1);
		frame.SetBlockAt(1, 2);
		piece.AddFrame(frame);

		frame = PieceFrame(3, 3);
		frame.SetBlockAt(1, 0);
		frame.SetBlockAt(0, 1);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(1, 2);
		piece.AddFrame(frame);

		break;


	case PieceType::Z:
		frame = PieceFrame(3, 3);
		frame.SetBlockAt(0, 0);
		frame.SetBlockAt(1, 0);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(2, 1);
		piece.AddFrame(frame);

		frame = PieceFrame(3, 3);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(1, 2);
		frame.SetBlockAt(2, 0);
		frame.SetBlockAt(2, 1);
		piece.AddFrame(frame);

		frame = PieceFrame(3, 3);
		frame.SetBlockAt(0, 1);
		frame.SetBlockAt(1, 1);
		frame.SetBlockAt(1, 2);
		frame.SetBlockAt(2, 2);
		piece.AddFrame(frame);

		frame = PieceFrame(3, 3);
		frame.SetBlockAt(0, 1);
		frame.SetBlockAt(0, 2);
		frame.SetBlockAt(1, 0);
		frame.SetBlockAt(1, 1);
		piece.AddFrame(frame);

		break;

	}

	return piece;
}

Piece PieceFactory::CreatePiece(PieceType::e piecetype) const {
	return CreatePiece(piecetype, GameSettings::BlockSize);
}

Piece PieceFactory::CreateRandomPiece() const {
	return CreateRandomPiece(GameSettings::BlockSize);
}

Piece PieceFactory::CreateRandomPiece(sf::Vector2f blocksize) const {
	// todo: default random is imperfect, keep statistics and ensure normal distribution
	PieceType::e piecetype = static_cast<PieceType::e>(random.Next() % PieceType::count);
	return CreatePiece(piecetype, blocksize);

}