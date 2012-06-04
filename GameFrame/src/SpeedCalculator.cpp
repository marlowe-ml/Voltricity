#include "SpeedCalculator.h"

using namespace game;

SpeedCalculator::SpeedCalculator() : _speedX(0), _speedY(0) {}

void SpeedCalculator::SetSpeedX(float pixelsPerSecond)  {
	_speedX = pixelsPerSecond;
}

void SpeedCalculator::SetSpeedY(float pixelsPerSecond) {
	_speedY = pixelsPerSecond;
}

sf::Vector2f SpeedCalculator::GetDistanceOverTime(float deltaTime) const {
	return sf::Vector2f(_speedX*deltaTime, _speedY*deltaTime);
}
