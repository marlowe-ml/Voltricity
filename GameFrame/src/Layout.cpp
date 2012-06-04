#include "Layout.h"
#include <stdio.h>
#include <iostream>

using namespace game;

Layout::Layout()
	:_areaRect(sf::FloatRect(0,0,800,600)) 
{}

Layout::Layout(sf::FloatRect areaRect)
	: _areaRect(areaRect)
{}

const sf::FloatRect Layout::GetRect() const {
	return _areaRect;
}

void Layout::AlignString(sf::String& obj, Direction::e hSnap, Direction::e vSnap) const {
	sf::FloatRect rect = obj.GetRect();
	sf::Vector2f size = sf::Vector2f(rect.Right - rect.Left, rect.Bottom - rect.Top);
	AlignDrawable(obj, size, hSnap, vSnap);
}

void Layout::AlignSprite(sf::Sprite& obj, Direction::e hSnap, Direction::e vSnap) const {
	AlignDrawable(obj, obj.GetSize(), hSnap, vSnap);
}


void Layout::AlignDrawable(sf::Drawable& obj, sf::Vector2f size, Direction::e hSnap, Direction::e vSnap) const {
	sf::Vector2f centerPos = GetAlignedPosition(size, hSnap, vSnap);
	obj.SetX(centerPos.x);
	obj.SetY(centerPos.y);
}

sf::Vector2f Layout::GetAlignedPosition(sf::Vector2f objSize, Direction::e hSnap, Direction::e vSnap) const {
	sf::Vector2f newPos(0, 0);

	float objWidth = objSize.x;
	float objHeight = objSize.y;

	switch (hSnap) {
	case Direction::left:
		newPos.x = _areaRect.Left;
		break;
	case Direction::right:
		newPos.x = _areaRect.Right - objWidth;
		break;
	case Direction::center:
		newPos.x = (_areaRect.GetWidth() / 2) - (objWidth / 2);
		break;
	}

	switch (vSnap) {
	case Direction::top:
		newPos.y = _areaRect.Top;
		break;
	case Direction::bottom:
		newPos.y = _areaRect.Bottom - objHeight;
		break;
	case Direction::center:
		newPos.y = (_areaRect.GetHeight() / 2) - (objHeight / 2);
		break;
	}


	return newPos;

}
