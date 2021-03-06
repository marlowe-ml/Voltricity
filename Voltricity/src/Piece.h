#ifndef Piece_h__
#define Piece_h__

#include <SFML/Graphics.hpp>
#include <vector>
#include "Direction.h"
#include "PieceFrame.h"

namespace volt {

class PieceType {
public:
	enum e {I=0,J=1,L=2,O=3,S=4,T=5,Z=6,count=7,none=8};
};

class Piece : public sf::Drawable {

public:
	Piece();
	Piece(sf::Vector2f blockSize);

	virtual ~Piece();

	void Render(sf::RenderTarget& target) const;
	const PieceFrame& GetCurrentFrame() const;
	void SetPosition(const sf::Vector2f& pixelPos);
	void AddFrame(PieceFrame frame);
	void Rotate(game::Direction::e dir);
	void SetBlockSize(sf::Vector2f size);
	void SetAlpha(float alpha);

	PieceType::e GetPieceType() const;
	void SetPieceType(PieceType::e newType);

private:
	std::vector<PieceFrame> _frames;
	int _currentFrameIndex;
	sf::Vector2f _blockSize;

	void keepValidFrameIndex();

	PieceType::e _pieceType;

};

}

#endif // Piece_h__
