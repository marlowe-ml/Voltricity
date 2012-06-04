#include <UnitTest++.h>

#include "Piece.h"

using namespace volt;

class PieceFixture {

public:
	PieceFixture() {}

	PieceFrame Frame_T(int index) {
		PieceFrame frame = PieceFrame(3,3);
		switch (index) {
			case 0:
				frame.SetBlockAt(1, 0);
				frame.SetBlockAt(0, 1);
				frame.SetBlockAt(1, 1);
				frame.SetBlockAt(2, 1);
				break;
			case 1:
				frame.SetBlockAt(1, 0);
				frame.SetBlockAt(1, 1);
				frame.SetBlockAt(2, 1);
				frame.SetBlockAt(1, 2);
				break;
			case 2:
				frame.SetBlockAt(0, 1);
				frame.SetBlockAt(1, 1);
				frame.SetBlockAt(2, 1);
				frame.SetBlockAt(1, 2);
				break;
			case 3:
				frame.SetBlockAt(1, 0);
				frame.SetBlockAt(0, 1);
				frame.SetBlockAt(1, 1);
				frame.SetBlockAt(1, 2);
				break;

		}
		
		return frame;
	}

	Piece CreatePiece_T() {
		Piece piece = Piece();

		piece.AddFrame(Frame_T(0));
		piece.AddFrame(Frame_T(1));
		piece.AddFrame(Frame_T(2));
		piece.AddFrame(Frame_T(3));

		return piece;
	}



};


TEST(AddsFrame) {
	Piece piece = Piece();

	PieceFrame frame1 = PieceFrame(3,3);
	frame1.SetBlockAt(1, 0);
	frame1.SetBlockAt(0, 1);
	frame1.SetBlockAt(1, 1);
	frame1.SetBlockAt(2, 1);

	piece.AddFrame(frame1);

	PieceFrame curFrame = piece.GetCurrentFrame();

	CHECK(curFrame.HasBlockAt(1, 0));
	CHECK(curFrame.HasBlockAt(0, 1));
	CHECK(curFrame.HasBlockAt(1, 1));
	CHECK(curFrame.HasBlockAt(2, 1));

}

TEST_FIXTURE(PieceFixture, RotatesClockWise) {
	Piece piece = CreatePiece_T();
	CHECK(piece.GetCurrentFrame() == Frame_T(0));

	piece.Rotate(game::Direction::right);
	CHECK(piece.GetCurrentFrame() == Frame_T(1));

	piece.Rotate(game::Direction::right);
	CHECK(piece.GetCurrentFrame() == Frame_T(2));

	piece.Rotate(game::Direction::right);
	CHECK(piece.GetCurrentFrame() == Frame_T(3));

	// test wrap around
	piece.Rotate(game::Direction::right);
	CHECK(piece.GetCurrentFrame() == Frame_T(0));
}


TEST_FIXTURE(PieceFixture, RotatesCounterClockWise) {
	Piece piece = CreatePiece_T();
	CHECK(piece.GetCurrentFrame() == Frame_T(0));

	// test wrap around
	piece.Rotate(game::Direction::left);
	CHECK(piece.GetCurrentFrame() == Frame_T(3));

	piece.Rotate(game::Direction::left);
	CHECK(piece.GetCurrentFrame() == Frame_T(2));

	piece.Rotate(game::Direction::left);
	CHECK(piece.GetCurrentFrame() == Frame_T(1));

	piece.Rotate(game::Direction::left);
	CHECK(piece.GetCurrentFrame() == Frame_T(0));
}