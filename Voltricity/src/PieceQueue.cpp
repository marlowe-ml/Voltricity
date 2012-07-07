#include "PieceQueue.h"
#include "GameSettings.h"
#include "Layout.h"
#include "Direction.h"

using namespace volt;

PieceQueue::PieceQueue(unsigned int numPieces) : _maxPieces(numPieces)
{
	_width = 5 * (GameSettings::BlockSize + GameSettings::BlockGap) + GameSettings::BlockGap;
	_heightPerPiece = 6 * (GameSettings::BlockSize + GameSettings::BlockGap) + GameSettings::BlockGap;
	_height = _maxPieces * _heightPerPiece;
	
}

void PieceQueue::PushNewPiece(Piece piece, Piece* poppedPieceByRef /* = NULL*/) {
	if (poppedPieceByRef!=NULL)
		poppedPieceByRef = NULL;

	if (_pieces.size() + 1 > _maxPieces) {
		*poppedPieceByRef = _pieces.front();
		_pieces.pop_front();
	}
	_pieces.push_back(piece);

	alignPieces();
}

void PieceQueue::alignPieces() {
	int pieceIndex = 0;

	for (PieceQueueContainer::iterator it = _pieces.begin(); it!=_pieces.end(); it++) {
		float y = pieceIndex*_heightPerPiece;
		game::Layout frameLayout = game::Layout(sf::FloatRect(0, y, _width, y + _heightPerPiece));
		sf::Vector2f pieceSize = it->GetCurrentFrame().GetSize();
		frameLayout.AlignDrawable(*it, pieceSize, game::Direction::center);

		pieceIndex++;
	}
}

void PieceQueue::Render(sf::RenderTarget& target) const {
	// todo: draw pieces stacked vertically, centered, 5x6 per piece
	for (PieceQueueContainer::const_iterator it = _pieces.begin(); it!=_pieces.end(); it++) {
		target.Draw(*it);
	}

}




