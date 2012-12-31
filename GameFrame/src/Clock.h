#ifndef Clock_h__
#define Clock_h__

/* 
Some parts of the implementation are taken from the SFML clock implementation 
http://www.sfml-dev.org
*/

#ifdef WIN32
	#include <windows.h>
	#include <time.h>
#else
	#ifdef MACOS
	    #include <mach/mach_time.h>
	#else
	    #include <time.h>
	#endif
#endif

namespace game {

	typedef unsigned long long ClockTick;

	class Clock {
	public:
		static const unsigned long TICKS_PER_SECOND;

		Clock();
		ClockTick  Restart();
		ClockTick GetElapsedMicroSeconds() const;
		ClockTick GetSystemMicroSeconds() const;

	private:
		ClockTick _startValue;
		#ifdef WIN32
		LARGE_INTEGER Clock::getFrequency() const;
		#endif
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
