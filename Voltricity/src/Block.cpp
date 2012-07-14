#include "Block.h"

using namespace volt;

Block::Block(const sf::Color color, float width, float height) 
: _width(width), _height(height), _empty(false)
{
	SetPosition(0,0);
	SetColor(color);
}

void Block::SetSize(sf::Vector2f size) {
	_width = size.x;
	_height = size.y;
}

bool Block::IsEmpty() const {
	return _empty;
}

void Block::SetEmpty(bool val) {
	_empty = val;
}

void Block::Render(sf::RenderTarget& target) const {
	sf::Vector2f pos = GetPosition();
	
	float x1 = 0;
	float y1 = 0;
	float x2 = x1 + _width;
	float y2 = y1 + _height;

	sf::Shape blockRect = sf::Shape::Rectangle(x1, y1, x2, y2, GetColor());
	target.Draw(blockRect);

	/*
	sf::Shape point = sf::Shape::Circle(sf::Vector2f(0,0), 1.0, sf::Color::White);
	target.Draw(point);*/
	
}