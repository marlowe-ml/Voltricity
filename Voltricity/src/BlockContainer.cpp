#include "BlockContainer.h"
#include "GameSettings.h"

using namespace volt;


BlockContainer::BlockContainer(int columnCount, int rowCount) : _columnCount(columnCount), _rowCount(rowCount) {
	_blocks.reserve(_columnCount);

	_blockSize = GameSettings::BlockSize;
	_blockGap = GameSettings::BlockGap;

	for (int x=0; x < _columnCount; x++) {
		GridRow newRow;
		for (int y = 0; y < _rowCount; y++) {
			Block b(sf::Color::Green, _blockSize.x, _blockSize.y);
			b.SetEmpty(true);
			newRow.push_back(b);
		}
		_blocks.push_back(newRow);
	}

	positionBlocks();
}

void BlockContainer::positionBlocks() {
	for (int x=0; x < _columnCount; x++) {
		for (int y = 0; y < _rowCount; y++) {
			_blocks[x][y].SetPosition(cellToGridPosInPx(x, y));
		}
	}
}

bool BlockContainer::IsEmpty() const {
	for (GridBlocks::const_iterator it = _blocks.begin(); it != _blocks.end(); it++) {
		for (GridRow::const_iterator rit = (*it).begin(); rit != (*it).end(); rit++) {
			if ((*rit).IsEmpty() == false)
				return false;
		}
	}

	return true;
}

sf::Vector2f BlockContainer::GetSize() const {
	float width = _columnCount * (_blockSize.x + _blockGap);
	
	if (_columnCount > 0)
		width += _blockGap;

	float height = _rowCount * (_blockSize.y + _blockGap);
	
	if (_rowCount > 0) 
		height += _blockGap;

	return sf::Vector2f(width, height);
}

void BlockContainer::SetBlockSize(sf::Vector2f size) {
	_blockSize = size;
	for (int x=0; x < _columnCount; x++) {
		for (int y = 0; y < _rowCount; y++) {
			_blocks[x][y].SetSize(size);
		}
	}

	positionBlocks();
}

void BlockContainer::SetBlockGap(float gap) {
	_blockGap = gap;
	positionBlocks();
}

void BlockContainer::SetBlockAt(int cellX, int cellY) {
	if (isValidPosition(cellX, cellY)) {
		_blocks[cellX][cellY] = Block(sf::Color::Red, _blockSize.x, _blockSize.y);
		_blocks[cellX][cellY].SetPosition(cellToGridPosInPx(cellX, cellY));
	}
}

void BlockContainer::RemoveBlockAt(int cellX, int cellY) {
	if (isValidPosition(cellX, cellY)) {
		_blocks[cellX][cellY].SetEmpty(true);
	}
}

sf::Vector2f BlockContainer::cellToGridPosInPx(int cellX, int cellY) const {
	return sf::Vector2f(cellX * (_blockSize.x+_blockGap) + _blockGap, cellY * (_blockSize.y+_blockGap)  + _blockGap);
}

bool BlockContainer::HasBlockAt(int cellX, int cellY) const {
	if (isValidPosition(cellX, cellY))
		return _blocks[cellX][cellY].IsEmpty() == false;

	return false;
}

bool BlockContainer::isValidPosition(int cellX, int cellY) const {
	return (cellX >= 0 && cellY >= 0 && cellX < _columnCount && cellY < _rowCount);
}

void BlockContainer::Render(sf::RenderTarget& target) const {
	for (int x=0; x < _columnCount; x++) {
		for (int y = 0; y < _rowCount; y++) {

			if (_blocks[x][y].IsEmpty())
				continue;

			target.Draw(_blocks[x][y]);
		}
	}
}

