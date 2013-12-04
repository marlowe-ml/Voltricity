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
	void SetText(const sf::String& text);
	void SetTextWithoutFit(const std::string& text);
	void SetBorder(float borderSize, sf::Color color);
	void SetBackground(sf::Color color);

protected:
	sf::String _text;
	float _width;
	float _height;
	sf::Color _borderColor;
	float _borderSize;
	sf::Color _bgColor;

	void fitText();


};

}

#endif // Label_h__
