#ifndef Grid_h__
#define Grid_h__

#include <vector>
#include "Direction.h"
#include "BlockContainer.h"
#include "Piece.h"


namespace volt {

class Grid : public BlockContainer {
public:
	
	Grid(int columnCount, int rowCount);
	virtual void Render(sf::RenderTarget& target) const;

	void SetCurrentPiece(const Piece piece);
	Piece GetCurrentPiece();

	bool MoveCurrentPieceTo(int cellX, int cellY);
	bool MoveCurrentPieceBy(int cellXDelta, int cellYDelta);

	bool Grid::RotateCurrentPiece(game::Direction::e dir);

	void AttachCurrentPieceBlocksToGrid(bool switchOnOff);
	void HardDropCurrentPiece();

	std::vector<int> GetCompletedRows() const;
	std::vector<int> GetClearedRows() const;
	std::vector<int> getRowsCompletedOrCleared(bool checkCompleted) const;
	
	void ClearRows(std::vector<int> rows);
	void CompactClearedRows();
	void moveRows(int rowsStart, int rowsEnd, int amountToMove);

	int GetBlockStackHeight() const;
	int GetTopStackRow() const;
	

private:
	Piece _currentPiece;
	Piece _ghostPiece;
	sf::Vector2i _currentPieceCellPosition;

	bool isValidPositionForPiece(int cellX, int cellY, Piece& piece) const;
	bool doMovePieceTo(int cellX, int cellY, Piece& piece);
	void onCurrentPiecePositionOrRotationChanged(const sf::Vector2i newPos, const game::Direction::e rotationDir);
	bool Grid::findValidPositionAfterRotation(game::Direction::e dir);
	bool Grid::tryMoveCurrentPieceBy(int xOffset, int yOffset);
};

}

#endif // Grid_h__