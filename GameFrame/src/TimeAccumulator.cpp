#include "TimeAccumulator.h"

using namespace game;

TimeAccumulator::TimeAccumulator() 
{
	Reset();
}

void TimeAccumulator::AccumulateElapsedTime(game::ClockTick currentTime) {
	if (_isPaused) {
		_lastTrackedTime = currentTime;
		_isPaused = false;
		return;
	}

	_totalAccumulatedTime += currentTime - _lastTrackedTime;
	_lastTrackedTime = currentTime;
}

void TimeAccumulator::Pause(game::ClockTick currentTime) {
	// make sure time is accumulated up until this time
	AccumulateElapsedTime(currentTime);
	_isPaused = true;
}

void TimeAccumulator::Reset() {
	_totalAccumulatedTime = 0;
	_lastTrackedTime = 0;
	_isPaused = true;
}