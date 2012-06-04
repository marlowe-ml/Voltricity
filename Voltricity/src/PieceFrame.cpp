#include "PieceFrame.h"

using namespace volt;

PieceFrame::PieceFrame(int columnCount, int rowCount) : BlockContainer(columnCount, rowCount) {
}

void PieceFrame::Render(sf::RenderTarget& target) const {
	sf::Vector2f size = GetSize();

	BlockContainer::Render(target);
}

bool PieceFrame::operator==(const PieceFrame& other) const {
	if (this->_columnCount != other._columnCount || this->_rowCount != other._rowCount)
		return false;

	for(int col=0; col < this->_columnCount; col++) {
		for(int row=0; row < this->_rowCount; row++) {
			if (this->HasBlockAt(col, row) != other.HasBlockAt(col, row))
				return false;
		}
	}

	return true;

}
