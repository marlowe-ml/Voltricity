#ifndef Layout_h__
#define Layout_h__

#include "Direction.h"
#include <SFML/Graphics.hpp>

namespace game {

	class Layout {
	public:
		Layout();
		Layout(sf::FloatRect areaRect);
		Layout(const sf::Drawable&, const sf::Vector2f size);
		sf::Vector2f GetAlignedPosition(sf::Vector2f objSize, Direction::e snapToEdge, sf::Vector2f offset = sf::Vector2f(0, 0)) const;
		void AlignDrawable(sf::Drawable& obj, sf::Vector2f size, Direction::e snapToEdge, sf::Vector2f offset = sf::Vector2f(0, 0)) const;
		
		/*
		void AlignString(sf::String& obj, Direction::e hSnap, Direction::e vSnap) const;
		void AlignSprite(sf::Sprite& obj, Direction::e hSnap, Direction::e vSnap) const;		
		*/
		const sf::FloatRect GetRect() const;

	private:
		sf::FloatRect _areaRect;

	};

}

#endif // Layout_h__