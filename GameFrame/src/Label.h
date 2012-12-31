#ifndef Label_h__
#define Label_h__

#include <SFML/Graphics.hpp>
#include "Direction.h"

namespace game {

class Label : public sf::Drawable {

public: 
	Label();
	Label(const sf::String& text);
	void Render(sf::RenderTarget& target) const;
	const sf::Vector2f GetSize() const;
	void SetText(const std::string& text);


private:
	sf::String _text;
	float _width;
	float _height;

};

}

#endif // Label_h__
