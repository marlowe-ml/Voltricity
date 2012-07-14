#ifndef Block_h__
#define Block_h__

#include "SFML/Graphics.hpp"

namespace volt {

class Block : public sf::Drawable {

public:
	Block(const sf::Color color, float width, float height);
	virtual void Render(sf::RenderTarget& target) const;

	bool IsEmpty() const;
	void SetEmpty(bool val);

	void SetSize(sf::Vector2f size);

private:
	float _width;
	float _height;
	bool _empty;

	// todo: color / sprite

};

}


#endif // Block_h__
