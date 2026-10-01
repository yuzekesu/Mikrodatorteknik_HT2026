/*
 * Clock.cpp
 *
 *  Created on: 29 Sept 2026
 *      Author: yuzek
 */

#include <Timer.hpp>

void Timer::Add(unsigned seconds) {
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

