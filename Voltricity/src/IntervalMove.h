#ifndef IntervalMove_h__
#define IntervalMove_h__

#include "Clock.h"
#include "Direction.h"

namespace volt {

class IntervalMove {

public:
	IntervalMove(game::Direction::e direction, game::ClockTick delayBetweenMoves);
	unsigned int DistanceUnitsSinceLastMove(game::ClockTick currentTicks);

	void Stop();
	void Start(game::ClockTick currentTicks);
	void StartInDirection(game::ClockTick currentTicks, game::Direction::e direction);
	bool IsStarted() const;
	bool IsPaused() const;

	void Pause(game::ClockTick currentTicks);
	void Resume(game::ClockTick currentTicks);

	game::Direction::e GetDirection() const;

private:	
	game::Direction::e _direction;
	game::ClockTick _lastMoveTime;
	game::ClockTick _lastPausedTime;
	game::ClockTick _delayBetweenMoves;
	bool _moving;
	bool _paused;
};

}

#endif // IntervalMove_h__
