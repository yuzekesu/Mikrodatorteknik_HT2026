/*
 * Clock.cpp
 *
 *  Created on: 29 Sept 2026
 *      Author: yuzek
 */

#include "Timer.hpp"
#include <stdio.h>

Timer::Timer(unsigned counter_period_per_tick_ms) : _counter_period_per_tick_ms(counter_period_per_tick_ms) {
}

Timer::operator std::string() {
	std::string result;
	result.resize(9); // i would use ostream if ram is enough, std::string handle \0 internt, but snprintf adds \0.
	snprintf(&(result[0]), result.size(), "%d%d:%d%d:%d%d", this->_hours / 10, this->_hours % 10, this->_minutes / 10, this->_minutes % 10, this->_seconds / 10, this->_seconds % 10);
	return result;
}

void Timer::_AddSec(unsigned seconds) {
	unsigned isOver = (this->_seconds + seconds) / 60u;
	this->_seconds = (this->_seconds + seconds) % 60u;
	if (isOver) {
		unsigned isOverAgain = (this->_minutes + isOver) / 60u;
		this->_minutes = (this->_minutes + isOver) % 60u;
		if (isOverAgain) {
			this->_hours = (this->_hours + isOverAgain) % 24u;
		}
	}
}

void Timer::IncTick(unsigned ms) {
	unsigned& counter = this->_counter;
	unsigned& tick = this->_ticks;
	counter += ms;
	if (counter >= this->_counter_period_per_tick_ms) {
		const unsigned multiplier = counter / this->_counter_period_per_tick_ms;
		counter %= this->_counter_period_per_tick_ms;
		// update ticks.
		tick += multiplier;
	}

	unsigned& milli = this->_milli_seconds;
	milli += ms;
	if (milli >= 1000) {
		const unsigned seconds = milli / 1000;
		milli %= 1000;
		// update clocks
		this->_AddSec(seconds);
	}
}

unsigned Timer::GetTick() {
	unsigned result = this->_ticks;
	this->_ticks = 0u;
	return result;
}

void Timer::Set(unsigned h, unsigned m, unsigned s) {
	this->_hours = h % 24;
	this->_minutes = m % 60;
	this->_seconds = s % 60;
}

unsigned Timer::GetHours() {
	return this->_hours;
}

unsigned Timer::GetMinutes() {
	return this->_minutes;
}

unsigned Timer::GetSeconds() {
	return this->_seconds;
}

unsigned Timer::GetAll() {
	return this->_hours * 10000 + this->_minutes * 100 + this->_seconds;
}

