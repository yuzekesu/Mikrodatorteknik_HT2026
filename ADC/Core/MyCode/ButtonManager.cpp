/*
 * ButtonManager.cpp
 *
 *  Created on: 29 Sept 2026
 *      Author: yuzek
 */

#include "ButtonManager.hpp"
#include <main.h>

ButtonManager::ButtonManager(std::size_t debounce_interval_ms) {
	this->_debounce_interval_ms = debounce_interval_ms;
}

void ButtonManager::Update(bool observedPressingAction) {
	uint32_t currentTimeStamp = HAL_GetTick();
	this->_observed_button_state = observedPressingAction ? this->_State::_PRESSING : this->_State::_IDLE;
	switch (this->_registered_button_state) {
	case this->_State::_IDLE:
		if (this->_observed_button_state == this->_State::_IDLE)
			break;
		++this->_observed_press_count;
		if (currentTimeStamp - this->_last_registered_press_time_stamp >= this->_debounce_interval_ms) {
			++this->_registered_press_count;
			this->_last_registered_press_time_stamp = currentTimeStamp;
			this->_registered_button_state = this->_State::_PRESSING;
			this->_is_handled_wait_until = false;
		}
		break;
	case this->_State::_PRESSING:
		if (this->_observed_button_state == this->_State::_PRESSING) {
			++this->_observed_press_count;
			break;
		}
		if (currentTimeStamp - this->_last_registered_press_time_stamp >= this->_debounce_interval_ms) {
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

void ButtonManager::WaitUntil(ButtonManager::WaitMode mode, bool until_button_is_pressing) {
	const ButtonManager::_State desire_state = until_button_is_pressing ? ButtonManager::_State::_PRESSING : ButtonManager::_State::_IDLE;

	switch (mode) {
	case ButtonManager::WaitMode::SINGLE:
		if (this->_is_handled_wait_until || !(this->_registered_button_state == desire_state)) {
			while (this->_is_handled_wait_until || !(this->_registered_button_state == desire_state))
				;
		}
		this->_is_handled_wait_until = true;
		break;
	case ButtonManager::WaitMode::CONTINUOUS:
		while (!(this->_registered_button_state == desire_state)) {
		}
		break;
	default:
		break;
	}
}

std::size_t ButtonManager::GetCounter() {
	return this->_registered_press_count;
}

std::size_t ButtonManager::GetObservedCounter() {
	return this->_observed_press_count;
}

