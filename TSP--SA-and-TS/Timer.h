#ifndef TIMER_H
#define TIMER_H

#include <chrono>

using namespace std::chrono;

class Timer {

private:
	high_resolution_clock::time_point t1, t2;

public:
	void time_start();
	void time_stop();
	double get_time();

};

#endif 
