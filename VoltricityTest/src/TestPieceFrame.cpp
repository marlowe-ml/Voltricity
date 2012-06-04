#include <UnitTest++.h>

#include "PieceFrame.h"

using namespace volt;

TEST(PieceFrameSetsBlocksCorrectly) {
	PieceFrame pf = PieceFrame(3,3);
	pf.SetBlockAt(0,0);
	pf.SetBlockAt(2,1);

	CHECK(pf.HasBlockAt(0,0));
	CHECK(pf.HasBlockAt(2,1));
}

TEST(PieceFrameInvalidBlockPositionIsRejected) {
	PieceFrame pf = PieceFrame(3,3);
	pf.SetBlockAt(3,3);

	CHECK(pf.HasBlockAt(3,3) == false);
}