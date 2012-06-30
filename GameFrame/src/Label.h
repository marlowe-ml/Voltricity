#ifndef Label_h__
#define Label_h__

#include <SFMl/Graphics.hpp>
#include "Direction.h"

namespace game {

class Label : public sf::Drawable {

public: 
	Label();
	Label(const sf::String& text);
	//void Align(Direction::e orientation, sf::Vector2f offset);
	void Render(sf::RenderTarget& target) const;

	const sf::Vector2f GetSize() const;

private:
	sf::String _text;
	float _width;
	float _height;

};

}

#endif // Label_h__
