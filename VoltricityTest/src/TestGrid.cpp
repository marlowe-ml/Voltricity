#include <UnitTest++.h>

#include "Grid.h"
#include "Piece.h"
#include <SFML/Graphics.hpp>

class GridFixture {
	
public:
	GridFixture() : grid(10,10) {}
	volt::Grid grid;
	
};

TEST_FIXTURE(GridFixture, GridIsEmptyOnCreation)
{
	CHECK(grid.IsEmpty());
}

TEST_FIXTURE(GridFixture, GridEmptyAtPositionOnCreation) {
	CHECK(grid.HasBlockAt(1,3) == false);
}


TEST_FIXTURE(GridFixture, GridSetBlockAtPosition)
{
	grid.SetBlockAt(0,0);
	CHECK(grid.HasBlockAt(0,0));

}

TEST_FIXTURE(GridFixture, GridSetMultipleBlocksAtPosition)
{
	grid.SetBlockAt(1,3);
	grid.SetBlockAt(7,4);
	grid.SetBlockAt(4,5);

	CHECK(grid.HasBlockAt(1,3));
	CHECK(grid.HasBlockAt(7,4));
	CHECK(grid.HasBlockAt(4,5));
}


TEST_FIXTURE(GridFixture, GridSetBlockAtInvalidPosition) {
	grid.SetBlockAt(100, 100);
	CHECK(grid.HasBlockAt(100, 100) == false);

	grid.SetBlockAt(-1, -1);
	CHECK(grid.HasBlockAt(-1, -1) == false);

}

TEST_FIXTURE(GridFixture, GridRemoveBlockAtPosition) {
	grid.SetBlockAt(2, 1);
	grid.SetBlockAt(5, 5);
	grid.SetBlockAt(3, 7);
	
	grid.RemoveBlockAt(3, 7);
	CHECK(grid.HasBlockAt(2, 1) == true);
	CHECK(grid.HasBlockAt(5, 5) == true);
	CHECK(grid.HasBlockAt(3, 7) == false);

	grid.RemoveBlockAt(2, 1);
	CHECK(grid.HasBlockAt(2, 1) == false);
	CHECK(grid.HasBlockAt(5, 5) == true);
	CHECK(grid.HasBlockAt(3, 7) == false);
}


TEST_FIXTURE(GridFixture, GridSetPieceAtPosition) {
	volt::Piece piece;

	volt::PieceFrame frame = volt::PieceFrame(3,3);
	frame.SetBlockAt(0, 1);
	frame.SetBlockAt(1, 0);
	frame.SetBlockAt(1, 1);
	frame.SetBlockAt(1, 2);

	piece.AddFrame(frame);


	grid.SetCurrentPiece(piece);
	grid.MoveCurrentPieceTo(0, 0);

	// todo: error reported here because piece is not dropped at bottom which will effectively compact all lines below the piece
	// hard drop does too many things and is misnamed
	grid.AttachCurrentPieceBlocksToGrid(true);

	CHECK(grid.HasBlockAt(0,1));
	CHECK(grid.HasBlockAt(1,0));
	CHECK(grid.HasBlockAt(1,1));
	CHECK(grid.HasBlockAt(1,2));

	grid.MoveCurrentPieceTo(2, 4);
	grid.AttachCurrentPieceBlocksToGrid(true);

	// previous blocks have to be there ..
	CHECK(grid.HasBlockAt(0,1));
	CHECK(grid.HasBlockAt(1,0));
	CHECK(grid.HasBlockAt(1,1));
	CHECK(grid.HasBlockAt(1,2));

	// .. and the new ones
	CHECK(grid.HasBlockAt(2,5));
	CHECK(grid.HasBlockAt(3,4));
	CHECK(grid.HasBlockAt(3,5));
	CHECK(grid.HasBlockAt(3,6));
}


TEST_FIXTURE(GridFixture, GridStopPieceAtBlocks) {
	volt::Piece piece;
	volt::PieceFrame frame = volt::PieceFrame(2,2);
	frame.SetBlockAt(0, 0);
	frame.SetBlockAt(0, 1);
	frame.SetBlockAt(1, 0);
	frame.SetBlockAt(1, 1);

	piece.AddFrame(frame);

	grid.SetCurrentPiece(piece);

	grid.SetBlockAt(10,10);

	CHECK(!grid.MoveCurrentPieceTo(9,9));
	
	grid.MoveCurrentPieceTo(8,8);
	CHECK(!grid.MoveCurrentPieceBy(1,0));
}

TEST(GridDetectCompletedLines) {
	volt::Grid grid(3,5);
	
	// line 0 incomplete
	grid.SetBlockAt(0, 0);
	grid.SetBlockAt(1, 0);

	// line 1 complete
	grid.SetBlockAt(0, 1);
	grid.SetBlockAt(1, 1);
	grid.SetBlockAt(2, 1);

	// line 3 complete
	grid.SetBlockAt(0, 3);
	grid.SetBlockAt(1, 3);
	grid.SetBlockAt(2, 3);

	// line 4 incomplete
	grid.SetBlockAt(2, 4);

	std::vector<int> completedRows = grid.GetCompletedRows();

	CHECK(completedRows.size() == 2);
	CHECK(completedRows[0] == 1);
	CHECK(completedRows[1] == 3);

}

TEST(GridClearLines) {
	volt::Grid grid(3,5);

	// line 1 complete
	grid.SetBlockAt(0, 1);
	grid.SetBlockAt(1, 1);
	grid.SetBlockAt(2, 1);

	std::vector<int> rowsToClear;
	rowsToClear.push_back(1);
	grid.ClearRows(rowsToClear);

	CHECK(grid.IsEmpty());

}

TEST(ClearedRowsAreCompacted) {
	volt::Grid grid(3,5);

	// line 4
	grid.SetBlockAt(0, 4);
	grid.SetBlockAt(2, 4);

	// line 3 cleared

	// line 2
	grid.SetBlockAt(0, 2);
	grid.SetBlockAt(1, 2);

	// line 1
	grid.SetBlockAt(0, 1);

	// line 0
	grid.SetBlockAt(0, 0);
	grid.SetBlockAt(2, 0);

	grid.CompactClearedRows();
	
	CHECK(grid.HasBlockAt(0,1));
	CHECK(!grid.HasBlockAt(1,1));
	CHECK(grid.HasBlockAt(2,1));
	
	CHECK(grid.HasBlockAt(0,2));
	CHECK(!grid.HasBlockAt(1,2));
	CHECK(!grid.HasBlockAt(2,2));

	CHECK(grid.HasBlockAt(0,3));
	CHECK(grid.HasBlockAt(1,3));
	CHECK(!grid.HasBlockAt(2,3));

	CHECK(grid.HasBlockAt(0,4));
	CHECK(!grid.HasBlockAt(1,4));
	CHECK(grid.HasBlockAt(2,4));

}

TEST(GridSize) {
	volt::Grid grid(10,20);

	grid.SetBlockSize(sf::Vector2f(5,7));
	grid.SetBlockGap(2.0f);

	sf::Vector2f size = grid.GetSize();

	CHECK(size.x == (50 + 22));
	CHECK(size.y == (140 + 42));
}


