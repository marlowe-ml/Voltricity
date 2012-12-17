#include "Grid.h"

using namespace volt;


Grid::Grid(int columnCount, int rowCount) : BlockContainer(columnCount, rowCount), 
_currentPieceCellPosition(sf::Vector2i(0,0)) 
{

}

void Grid::HardDropCurrentPiece() {
	while (MoveCurrentPieceBy(0, 1))
		;

	AttachCurrentPieceBlocksToGrid(true);
}

std::vector<int> Grid::GetCompletedRows() const {
	return getRowsCompletedOrCleared(true);
}

std::vector<int> Grid::GetClearedRows() const {
	return getRowsCompletedOrCleared(false);
}

std::vector<int> Grid::getRowsCompletedOrCleared(bool checkCompleted) const {
	std::vector<int> matchingRows;

	// run from top of stack down to bottom of the grid
	for (int row=GetTopStackRow(); row < _rowCount; row++) {
		bool matching = true;

		for (int col=0; col<_columnCount; col++) {
			if (checkCompleted && !HasBlockAt(col, row)) {
				matching = false;
				break;
			} else if (!checkCompleted && HasBlockAt(col, row)) {
				matching = false;
				break;
			}
		}

		if (matching)
			matchingRows.push_back(row);
	}

	return matchingRows;
}

int Grid::GetBlockStackHeight() const {
	for (int row=0; row < _rowCount; row++) {
		for (int col=0; col<_columnCount; col++) {
			if (HasBlockAt(col, row))
				return _rowCount-row;
		}
	}

	return 0;
}

int Grid::GetTopStackRow() const {
	return _rowCount - GetBlockStackHeight();
}


void Grid::ClearRows(std::vector<int> rows) {
	for(std::vector<int>::iterator it = rows.begin(); it!= rows.end(); it++) {
		int row = (*it);
		for (int col = 0; col<_columnCount; col++) {
			RemoveBlockAt(col, row);
		}
	}
}

void Grid::Clear() {
	for(int row=0; row<_rowCount; row++) {
		for (int col = 0; col<_columnCount; col++) {
			RemoveBlockAt(col, row);
		}
	}
}


void Grid::moveRows(int rowsStart, int rowsEnd, int amountToMove) {
	// make sure rows to move don't overwrite each other
	if (
		(amountToMove > 0 && rowsStart < rowsEnd) ||
		(amountToMove < 0 && rowsStart > rowsEnd)
		)
	{
		int tmp = rowsStart;
		rowsStart = rowsEnd;
		rowsEnd = tmp;
	}

	int traversalIncrement = amountToMove > 0 ? -1 : +1;

	int row = rowsStart;

	do {
		for (int col=0; col<_columnCount; col++) {
			if (HasBlockAt(col, row)) {
				SetBlockAt(col, row+amountToMove);
				RemoveBlockAt(col, row);
			} else {
				RemoveBlockAt(col, row+amountToMove);
			}

		}
		row += traversalIncrement;
	} while(row != rowsEnd + traversalIncrement);

}

void Grid::CompactClearedRows() {
	std::vector<int> clearedRows = GetClearedRows();

	for (unsigned int i=0; i<clearedRows.size(); i++)
		moveRows(GetTopStackRow(), clearedRows[i]-1, 1);
}

void Grid::Render(sf::RenderTarget& target) const {
	// draw border
	sf::Vector2f size = GetSize();

	sf::Shape outlineRect = sf::Shape::Rectangle(0, 0, size.x, size.y, sf::Color::Red, 1.0, sf::Color::Green);
	outlineRect.EnableFill(false);
	target.Draw(outlineRect);

	target.Draw(_ghostPiece);
	
	target.Draw(_currentPiece);
	
	


	// draw blocks
	BlockContainer::Render(target);	
}


void Grid::SetCurrentPiece(const Piece piece) {	
	_currentPiece = piece;
	_ghostPiece = piece;
	_ghostPiece.SetAlpha(100);
}

Piece Grid::GetCurrentPiece() {
	return _currentPiece;
}

bool Grid::MoveCurrentPieceBy(int cellXDelta, int cellYDelta) {
	return MoveCurrentPieceTo(_currentPieceCellPosition.x + cellXDelta, _currentPieceCellPosition.y + cellYDelta);
}

bool Grid::MoveCurrentPieceTo(int cellX, int cellY) {	

	if (doMovePieceTo(cellX, cellY, _currentPiece)) {
		_currentPieceCellPosition = sf::Vector2i(cellX, cellY);
		onCurrentPiecePositionOrRotationChanged(_currentPieceCellPosition, game::Direction::none);
		return true;
	}

	return false;
}

void Grid::onCurrentPiecePositionOrRotationChanged(const sf::Vector2i newPos, const game::Direction::e rotationDir) {
	if (rotationDir != game::Direction::none)
		_ghostPiece.Rotate(rotationDir);

	doMovePieceTo(newPos.x, newPos.y, _ghostPiece);

	// soft drop simulation for ghost piece to have it hover on the bottom
	int offset = 1;
	while (doMovePieceTo(newPos.x, newPos.y + offset, _ghostPiece))
		offset++;
}


bool Grid::doMovePieceTo(int cellX, int cellY, Piece& piece) {
	if (!isValidPositionForPiece(cellX, cellY, piece))
		return false;


	sf::Vector2f pixelPos = cellToGridPosInPx(cellX, cellY);
	// account for double block gap when positioning the piece
	pixelPos.x -= _blockGap;
	pixelPos.y -= _blockGap;
	piece.SetPosition(pixelPos);

	return true;

}


bool Grid::tryMoveCurrentPieceBy(int xOffset, int yOffset) {
	if (isValidPositionForPiece(_currentPieceCellPosition.x + xOffset, _currentPieceCellPosition.y + yOffset, _currentPiece)) {
		MoveCurrentPieceBy(xOffset, 0);
		return true;
	}
	return false;
}

bool Grid::findValidPositionAfterRotation(game::Direction::e dir) {

	int xOffset = dir == game::Direction::left ? -1 : 1;
	// todo: add unit tests for scenarios
	return 
		tryMoveCurrentPieceBy(0, 0) ||				// actual start position after rotation
		tryMoveCurrentPieceBy(xOffset, 0) ||		// horizontal in prioritized direction
		tryMoveCurrentPieceBy(xOffset*-1, 0) ||		// horizontal in opposite direction
		tryMoveCurrentPieceBy(0, 1) ||				// one down
		tryMoveCurrentPieceBy(xOffset, 1) ||		// horizontal in prioritized direction + down
		tryMoveCurrentPieceBy(xOffset*-1, 1) ||		// horizontal in opposite direction + down
		tryMoveCurrentPieceBy(0, -1);				// one up / floor kick
}

bool Grid::RotateCurrentPiece(game::Direction::e dir) {
	game::Direction::e inverseDir = (dir == game::Direction::left) ? game::Direction::right : game::Direction::left;
	sf::Vector2i originalPos = _currentPieceCellPosition;

	_currentPiece.Rotate(dir);

	if (!findValidPositionAfterRotation(dir)) {
		// rotate and move back to original rot/pos
		MoveCurrentPieceTo(originalPos.x, originalPos.y);
		_currentPiece.Rotate(inverseDir);
		return false;		
	}

	onCurrentPiecePositionOrRotationChanged(_currentPieceCellPosition, dir);

	return true;
}



void Grid::AttachCurrentPieceBlocksToGrid(bool switchOnOff) {
	int pieceCols = _currentPiece.GetCurrentFrame().ColumnCount();
	int pieceRows = _currentPiece.GetCurrentFrame().RowCount();

	for (int x=0; x<pieceCols; x++) {
		for (int y=0; y<pieceRows; y++) {
			if (_currentPiece.GetCurrentFrame().HasBlockAt(x,y)) {
				if (switchOnOff == true) 
					SetBlockAt(_currentPieceCellPosition.x + x, _currentPieceCellPosition.y + y);
				else
					RemoveBlockAt(_currentPieceCellPosition.x + x, _currentPieceCellPosition.y + y);
			}
		}
	}
}

bool Grid::isValidPositionForPiece(int cellX, int cellY, Piece& piece) const {
	int pieceCols = piece.GetCurrentFrame().ColumnCount();
	int pieceRows = piece.GetCurrentFrame().RowCount();

	for (int x=0; x<pieceCols; x++) {
		for (int y=0; y<pieceRows; y++) {
			if (piece.GetCurrentFrame().HasBlockAt(x,y)) {
				if (!isValidPosition(cellX + x, cellY + y) || HasBlockAt(cellX + x, cellY + y))
					return false;
			}
		}
	}
	return true;
}
