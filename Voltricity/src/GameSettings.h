#ifndef GameSettings_h__
#define GameSettings_h__

#include <SFML/Graphics.hpp>

namespace volt {

class GameSettings {
public:
	static sf::Vector2f BlockSize;
	static sf::Vector2f BlockSizeForQueue;
	static float BlockGap;

};


}
#endif // GameSettings_h__
