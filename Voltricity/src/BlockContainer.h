#ifndef BlockContainer_h__
#define BlockContainer_h__

#include <vector>
#include "SFML/Graphics.hpp"
#include "Block.h"

namespace volt {

typedef std::vector<Block> GridRow;
typedef std::vector< GridRow > GridBlocks;

class BlockContainer : public sf::Drawable {

public:
	BlockContainer(int columnCount, int rowCount);

	bool IsEmpty() const;
	void SetBlockAt(int cellX, int cellY);
	void RemoveBlockAt(int cellX, int cellY);
	bool HasBlockAt(int cellX, int cellY) const;

	virtual void Render(sf::RenderTarget& target) const;

	sf::Vector2f GetSize() const;
	void SetBlockSize(sf::Vector2f size);
	void SetBlockGap(float gap);

	void positionBlocks();

	void SetAlpha(float alpha);

	inline int ColumnCount() const {return _columnCount;}
	inline int RowCount() const {return _rowCount;}

protected:
	GridBlocks _blocks;

	int _columnCount;
	int _rowCount;

	sf::Vector2f _blockSize;
	float _blockGap;

	bool isValidPosition(int x, int y) const;
	sf::Vector2f cellToGridPosInPx(int cellX, int cellY) const;
};

}

#endif // BlockContainer_h__
