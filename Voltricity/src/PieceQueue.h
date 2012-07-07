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
		void PushNewPiece(Piece piece, Piece* poppedPieceByRef=NULL);

		virtual void Render(sf::RenderTarget& target) const;

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
