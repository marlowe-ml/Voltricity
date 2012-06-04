#ifndef SpeedCalculator_h__
#define SpeedCalculator_h__

#include <SFML/Graphics.hpp>

namespace game {

class SpeedCalculator {

public:
	SpeedCalculator();
	void SetSpeedX(float pixelsPerSecond);
	void SetSpeedY(float pixelsPerSecond);
	sf::Vector2f GetDistanceOverTime(float deltaTime) const;

private:
	float _speedX;
	float _speedY;
};

}

#endif // SpeedCalculator_h__
