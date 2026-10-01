/*
 * ButtonManager.hpp
 *
 *  Created on: 29 Sept 2026
 *      Author: yuzek
 */
#include <cstdint>
#include <main.h>

#ifndef BUTTONMANAGER_HPP_
#define BUTTONMANAGER_HPP_

class ButtonManager {
public:
	ButtonManager() = delete;
	ButtonManager(GPIO_TypeDef* port, uint16_t pin, std::size_t debouce_interval_ms = 2);
	void Set(bool);
	bool IsPressing();
	std::size_t GetCounter();
	std::size_t GetObservedCounter();
private:
	struct _Button {
		GPIO_TypeDef* _port = nullptr;
		uint16_t _pin = 0;
	}_button;
	enum _State {
		_IDLE, _PRESSING
	} _registered_button_state = ButtonManager::_State::_IDLE, _observed_button_state;
	std::size_t _debounce_interval_ms = 0;
	std::size_t _observed_press_count = 0;
	std::size_t _registered_press_count = 0;
	uint32_t _last_registered_press_time_stamp = 0;
};

#endif /* BUTTONMANAGER_HPP_ */
