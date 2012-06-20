#ifndef Label_h__
#define Label_h__

#include <SFMl/Graphics.hpp>
#include "Direction.h"

namespace game {

class Label : public sf::Drawable {

public: 
	Label();
	Label(const std::string& text);
	//void Align(Direction::e orientation, sf::Vector2f offset);
	void Render(sf::RenderTarget& target) const;


private:
	sf::String _text;

};

}

#endif // Label_h__
