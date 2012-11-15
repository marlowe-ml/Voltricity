#ifndef TimeAccumulator_h__
#define TimeAccumulator_h__

#include "Clock.h"

namespace game {

class TimeAccumulator {
	public:
		TimeAccumulator();
		void AccumulateElapsedTime(game::ClockTick currentTime);
		void Pause(game::ClockTick currentTime);
		void Reset();
		inline game::ClockTick GetAccumulatedTime() {return _totalAccumulatedTime;}

	private:
		game::ClockTick  _totalAccumulatedTime;
		game::ClockTick  _lastTrackedTime;
		bool _isPaused;
};

}

#endif // TimeAccumulator_h__
