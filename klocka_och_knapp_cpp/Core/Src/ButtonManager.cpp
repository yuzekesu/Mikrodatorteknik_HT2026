/*
 * ButtonManager.cpp
 *
 *  Created on: 29 Sept 2026
 *      Author: yuzek
 */

#include "ButtonManager.hpp"
#include <main.h>


ButtonManager::ButtonManager(GPIO_TypeDef *port, uint16_t pin, std::size_t debounce_interval_ms) {
	this->_button._pin = pin;
	this->_button._port = port;
	this->_debounce_interval_ms = debounce_interval_ms;
}

void ButtonManager::Set(bool observedPressingAction) {
	uint32_t currentTimeStamp = HAL_GetTick();
	this->_observed_button_state =  observedPressingAction ? this->_State::_PRESSING : this->_State::_IDLE;
	switch (this->_registered_button_state) {
	case this->_State::_IDLE:
		if (this->_observed_button_state == this->_State::_IDLE)
			break;
		++this->_observed_press_count;
		if (currentTimeStamp - this->_last_registered_press_time_stamp
				>= this->_debounce_interval_ms) {
			++this->_registered_press_count;
			this->_last_registered_press_time_stamp = currentTimeStamp;
			this->_registered_button_state = this->_State::_PRESSING;
		}
		break;
	case this->_State::_PRESSING:
		if (this->_observed_button_state == this->_State::_PRESSING) {
			++this->_observed_press_count;
			break;
		}
		if (currentTimeStamp - this->_last_registered_press_time_stamp
				>= this->_debounce_interval_ms) {
			this->_last_registered_press_time_stamp = currentTimeStamp;
			this->_registered_button_state = this->_State::_IDLE;
		}
		break;
	default:
		break;
	}
}

bool ButtonManager::IsPressing() {
	return this->_registered_button_state == this->_State::_PRESSING;
}
std::size_t ButtonManager::GetCounter() {
	return this->_registered_press_count;
}
std::size_t ButtonManager::GetObservedCounter() {
	return this->_observed_press_count;
}

