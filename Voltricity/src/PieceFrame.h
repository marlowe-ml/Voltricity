#ifndef PieceFrame_h__
#define PieceFrame_h__

#include "BlockContainer.h"

namespace volt {

class PieceFrame : public BlockContainer {
public:
	PieceFrame(int columnCount, int rowCount);
	void Render(sf::RenderTarget& target) const;

	bool operator==(const PieceFrame& other) const;

};


}

#endif // PieceFrame_h__
