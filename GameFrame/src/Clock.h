#ifndef Clock_h__
#define Clock_h__

/* 
Some parts of the implementation are taken from the SFML clock implementation 
http://www.sfml-dev.org
*/


#include <windows.h>

namespace game {

	typedef unsigned long long ClockTick;

	class Clock {
	public:
		static const unsigned long TICKS_PER_SECOND;

		Clock();
		ClockTick  Restart();
		ClockTick GetElapsedMicroSeconds() const;
		ClockTick Clock::GetSystemMicroSeconds() const;

	private:
		ClockTick _startValue;

		LARGE_INTEGER Clock::getFrequency() const;
	};


	class ClockSecond {
	public:
		ClockSecond();
		ClockSecond(double seconds);
		ClockSecond(ClockTick ticks);

		operator double() const;
		operator ClockTick() const;

	private:
		double _seconds;
	};

}


#endif // Clock_h__
