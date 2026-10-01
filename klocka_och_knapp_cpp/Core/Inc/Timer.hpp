/*
 * Clock.hpp
 *
 *  Created on: 29 Sept 2026
 *      Author: yuzek
 */

#ifndef INC_TIMER_HPP_
#define INC_TIMER_HPP_

class Timer {
public:
	void Add(unsigned seconds);
	unsigned GetHours();
	unsigned GetMinutes();
	unsigned GetSeconds();
	unsigned GetAll();
private:
	unsigned _hours = 23u;
	unsigned _minutes = 59u;
	unsigned _seconds = 45u;
};

#endif /* INC_TIMER_HPP_ */
