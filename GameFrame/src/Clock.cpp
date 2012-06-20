#include "Clock.h"

using namespace game;

const unsigned long Clock::TICKS_PER_SECOND = 1000000;	// 1 tick = 1 Microsecond

Clock::Clock() : _startValue(GetSystemMicroSeconds()) {
}

ClockTick Clock::GetElapsedMicroSeconds() const {
	return GetSystemMicroSeconds() - _startValue;
}

ClockTick Clock::GetSystemMicroSeconds() const {
	HANDLE currentThread = GetCurrentThread();
	DWORD_PTR previousMask = SetThreadAffinityMask(currentThread, 1);

	static LARGE_INTEGER frequency = getFrequency();

	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	SetThreadAffinityMask(currentThread, previousMask);

	return static_cast<ClockTick>(TICKS_PER_SECOND * time.QuadPart / frequency.QuadPart);
}

ClockTick  Clock::Restart() {
	ClockTick currentTime = GetSystemMicroSeconds();
	ClockTick currentElapsed = currentTime - _startValue;
	_startValue = currentTime;
	return currentElapsed;
}

LARGE_INTEGER Clock::getFrequency() const {
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return frequency;
}


ClockSecond::ClockSecond() : _seconds(0)
{}

ClockSecond::ClockSecond(double seconds) : _seconds(seconds)
{}



ClockSecond::ClockSecond(ClockTick ticks) : _seconds(static_cast<double>(ticks) / static_cast<double>(Clock::TICKS_PER_SECOND))
{}

ClockSecond::operator double() const {
	return _seconds;
}

ClockSecond::operator ClockTick() const {
	return static_cast<ClockTick>(_seconds * Clock::TICKS_PER_SECOND);
}
