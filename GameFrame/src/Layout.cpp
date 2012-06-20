#include "Layout.h"
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics/Drawable.hpp>

class x: public sf::Drawable {

};

using namespace game;

Layout::Layout()
	:_areaRect(sf::FloatRect(0,0,800,600)) 
{}


Layout::Layout(const sf::Drawable& drawable, const sf::Vector2f size) :
_areaRect(sf::FloatRect(drawable.GetPosition().x,drawable.GetPosition().y,size.x,size.y)) 
{}

Layout::Layout(sf::FloatRect areaRect)
	: _areaRect(areaRect)
{}

const sf::FloatRect Layout::GetRect() const {
	return _areaRect;
}

/*
void Layout::AlignString(sf::String& obj, Direction::e hSnap, Direction::e vSnap) const {
	sf::FloatRect rect = obj.GetRect();
	sf::Vector2f size = sf::Vector2f(rect.Right - rect.Left, rect.Bottom - rect.Top);
	AlignDrawable(obj, size, hSnap, vSnap);
}

void Layout::AlignSprite(sf::Sprite& obj, Direction::e hSnap, Direction::e vSnap) const {
	AlignDrawable(obj, obj.GetSize(), hSnap, vSnap);
}*/


void Layout::AlignDrawable(sf::Drawable& obj, sf::Vector2f size, Direction::e snapToEdge, sf::Vector2f offset /* = sf::Vector2f(0, 0) */) const {
	sf::Vector2f centerPos = GetAlignedPosition(size, snapToEdge, offset);
	obj.SetX(centerPos.x);
	obj.SetY(centerPos.y);
}

sf::Vector2f Layout::GetAlignedPosition(sf::Vector2f objSize, Direction::e snapToEdge, sf::Vector2f offset /* = sf::Vector2f(0, 0) */) const {
	sf::Vector2f newPos(0, 0);

	float objWidth = objSize.x;
	float objHeight = objSize.y;

	switch (Direction::hPart(snapToEdge)) {
	case Direction::left:
		newPos.x = _areaRect.Left;
		break;
	case Direction::right:
		newPos.x = _areaRect.Right - objWidth;
		break;
	case Direction::hcenter:
		newPos.x = (_areaRect.GetWidth() / 2) - (objWidth / 2);
		break;
	}

	switch (Direction::vPart(snapToEdge)) {
	case Direction::top:
		newPos.y = _areaRect.Top;
		break;
	case Direction::bottom:
		newPos.y = _areaRect.Bottom - objHeight;
		break;
	case Direction::vcenter:
		newPos.y = (_areaRect.GetHeight() / 2) - (objHeight / 2);
		break;
	}

	newPos.x += offset.x;
	newPos.y += offset.y;

	return newPos;

}
