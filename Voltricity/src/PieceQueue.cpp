#include "PieceQueue.h"
#include "GameSettings.h"
#include "Layout.h"
#include "Direction.h"

using namespace volt;

PieceQueue::PieceQueue(unsigned int numPieces) : _maxPieces(numPieces)
{
	_width = 5 * (GameSettings::BlockSizeForQueue.x + GameSettings::BlockGap) + GameSettings::BlockGap;
	_heightPerPiece = 4 * (GameSettings::BlockSizeForQueue.y + GameSettings::BlockGap) + GameSettings::BlockGap;
	_height = _maxPieces * _heightPerPiece;
	
}

Piece PieceQueue::PushNewPiece(Piece piece) {
	Piece poppedPiece;

	if (_pieces.size() + 1 > _maxPieces) {
		poppedPiece = _pieces.front();
		_pieces.pop_front();
	}
	_pieces.push_back(piece);

	alignPieces();

	return poppedPiece;
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
	for (PieceQueueContainer::const_iterator it = _pieces.begin(); it!=_pieces.end(); it++) {
		target.Draw(*it);
	}

}

sf::Vector2f PieceQueue::GetSize() const {
	return sf::Vector2f(_width, _height);
}

unsigned int PieceQueue::GetMaxPieces() const {
	return _maxPieces;
}