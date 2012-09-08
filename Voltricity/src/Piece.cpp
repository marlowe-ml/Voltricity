#include "Piece.h"
#include "GameSettings.h"

using namespace volt;

Piece::Piece(sf::Vector2f blockSize) : _currentFrameIndex(0), _blockSize(blockSize), _pieceType(PieceType::none) {
}

Piece::Piece() : _currentFrameIndex(0), _blockSize(GameSettings::BlockSize), _pieceType(PieceType::none) {
}

PieceType::e Piece::GetPieceType() const {
	return _pieceType;
}

void Piece::SetPieceType(PieceType::e newType) {
	_pieceType = newType;
}

Piece::~Piece() {}

void Piece::Render(sf::RenderTarget& target) const {
	target.Draw(_frames[_currentFrameIndex]);
}

const PieceFrame& Piece::GetCurrentFrame() const {
	return _frames[_currentFrameIndex];
}

void Piece::SetPosition(const sf::Vector2f& pixelPos) {	
	for (unsigned int i=0; i < _frames.size(); i++) {
		_frames[i].SetPosition(pixelPos);
	}
	//Drawable::SetPosition(pixelPos);
}

void Piece::SetBlockSize(sf::Vector2f size) {
	_blockSize = size;
	for (unsigned int i=0; i < _frames.size(); i++) {
		_frames[i].SetBlockSize(_blockSize);
	}
}

void Piece::SetAlpha(float alpha) {
	for (unsigned int i=0; i < _frames.size(); i++) {
		_frames[i].SetAlpha(alpha);
	}	
}

void Piece::AddFrame(PieceFrame frame) {
	frame.SetBlockSize(_blockSize);
	_frames.push_back(frame);
}

void Piece::Rotate(game::Direction::e dir) {
	if (dir == game::Direction::right)
		_currentFrameIndex++;
	else
		_currentFrameIndex--;

	keepValidFrameIndex();
}

void Piece::keepValidFrameIndex() {
	if (_frames.size() == 0) {
		_currentFrameIndex = 0;
		return;
	}

	if (_currentFrameIndex < 0) {
		_currentFrameIndex = _frames.size()-1;
	} else if ((unsigned int)_currentFrameIndex > _frames.size()-1) {
		_currentFrameIndex = 0;
	}
}