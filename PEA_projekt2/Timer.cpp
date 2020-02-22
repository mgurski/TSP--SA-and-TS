#include "Timer.h"

void Timer::time_start()
{
	t1 = high_resolution_clock::now();
}

void Timer::time_stop()
{
	t2 = high_resolution_clock::now();
}

double Timer::get_time()
{
	return duration_cast<milliseconds>(Timer::t2 - Timer::t1).count();
}
