#ifndef PieceQueue_h__
#define PieceQueue_h__

#include <SFML/Graphics.hpp>
#include <deque>
#include "Piece.h"

namespace volt {

	typedef std::deque<Piece> PieceQueueContainer;

	class PieceQueue : public sf::Drawable {
	public:
		PieceQueue(unsigned int numPieces);
		Piece PushNewPiece(Piece piece);

		virtual void Render(sf::RenderTarget& target) const;
		sf::Vector2f GetSize() const;
		unsigned int GetMaxPieces() const;

	private:
		PieceQueueContainer _pieces;
		unsigned int _maxPieces;
		float _width;
		float _height;
		float _heightPerPiece;

		void alignPieces();
	};

}

#endif // PieceQueue_h__
