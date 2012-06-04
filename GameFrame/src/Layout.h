#ifndef Layout_h__
#define Layout_h__

#include "Direction.h"
#include <SFML/Graphics.hpp>

namespace game {

	class Layout {
	public:
		Layout();
		Layout(sf::FloatRect areaRect);
		sf::Vector2f GetAlignedPosition(sf::Vector2f objSize, Direction::e horizontalSnap, Direction::e verticalSnap) const;
		void AlignDrawable(sf::Drawable& obj, sf::Vector2f size, Direction::e hSnap, Direction::e vSnap) const;
		void AlignString(sf::String& obj, Direction::e hSnap, Direction::e vSnap) const;
		void AlignSprite(sf::Sprite& obj, Direction::e hSnap, Direction::e vSnap) const;		
		const sf::FloatRect GetRect() const;

	private:
		sf::FloatRect _areaRect;

	};

}

#endif // Layout_h__