#include "IntervalMove.h"

using namespace volt;

IntervalMove::IntervalMove(game::Direction::e direction, game::ClockTick delayBetweenMoves) 
	: _direction(direction), _delayBetweenMoves(delayBetweenMoves), _lastMoveTime(0), _moving(false), _paused(false)
{};

unsigned int IntervalMove::DistanceUnitsSinceLastMove(game::ClockTick currentTicks) {

	if (!_moving || _paused)
		return 0;

	unsigned int distance = 0;
	while (currentTicks - _lastMoveTime >= _delayBetweenMoves) {
		_lastMoveTime += _delayBetweenMoves;
		distance++;
	}
	return distance;
}

void IntervalMove::Stop() {
	_moving = false;
	_paused = false;
	_lastMoveTime = 0;
}

void IntervalMove::Start(game::ClockTick currentTicks) {
	_lastMoveTime = currentTicks;
	_moving = true;
	_paused = false;
}

void IntervalMove::StartInDirection(game::ClockTick currentTicks, game::Direction::e direction) {
	_direction = direction;
	Start(currentTicks);
}

void IntervalMove::SetDelayBetweenMoves(game::ClockTick delayBetweenMoves) {
	_delayBetweenMoves = delayBetweenMoves;
}

game::ClockTick IntervalMove::GetDelayBetweenMoves() const {
	return _delayBetweenMoves;
}

bool IntervalMove::IsStarted() const {
	return _moving;
}

bool IntervalMove::IsPaused() const {
	return _paused;
}

void IntervalMove::Pause(game::ClockTick currentTicks) {
	if (!_paused) {
		_paused = true;
		_lastPausedTime = currentTicks;
	}
}

void IntervalMove::Resume(game::ClockTick currentTicks) {
	if (_paused) {
		_paused = false;
		_lastMoveTime = currentTicks - (_lastPausedTime - _lastMoveTime);
	}


}

game::Direction::e IntervalMove::GetDirection() const {
	return _direction;
}