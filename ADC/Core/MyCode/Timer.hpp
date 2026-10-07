/*
 * Clock.hpp
 *
 *  Created on: 29 Sept 2026
 *      Author: yuzek
 */

#include <string>

#ifndef INC_TIMER_HPP_
#define INC_TIMER_HPP_

class Timer {
public:
	Timer(unsigned counter_period_per_tick_ms = 1000);
	explicit operator std::string();
	void IncTick(unsigned ms);
	unsigned GetTick();
	void Set(unsigned h, unsigned m, unsigned s);
	unsigned GetHours();
	unsigned GetMinutes();
	unsigned GetSeconds();
	unsigned GetAll();
private:
	unsigned _ticks = 0u;
	unsigned _counter = 0u;
	unsigned _counter_period_per_tick_ms = 1000u;
	unsigned _hours = 0u;
	unsigned _minutes = 0u;
	unsigned _seconds = 0u;
	unsigned _milli_seconds = 0u;
	void _AddSec(unsigned seconds);
};

#endif /* INC_TIMER_HPP_ */
