#include "Piece.h"

using namespace volt;

Piece::Piece() : _currentFrameIndex(0) {
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
}

void Piece::AddFrame(PieceFrame frame) {
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