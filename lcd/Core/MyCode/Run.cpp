/*
 * Run.cpp
 *
 *  Created on: 30 Sept 2026
 *      Author: yuzek
 */

#include <stm32l4xx_hal.h>
#include <string>
#include "Run.hpp"
#include "UARTManager.hpp"
#include "Timer.hpp"

Timer _timer{};
TIM_HandleTypeDef* _p_htim_timer = nullptr;
UART_HandleTypeDef* _p_huart = nullptr;

void Run(struct RUN_DESC desc) {
	// initialization.
	_p_htim_timer = desc.p_htim_timer;
	_p_huart = desc.p_huart;
	UARTManager uart{_p_huart};
	HAL_TIM_Base_Start_IT(_p_htim_timer);

	// super loop.
	while(1) {
		int ticks = _timer.GetTick();
		if (ticks) {
			uart.PrintLn(static_cast<std::string>(_timer).c_str());
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* p_htim) {
	if (p_htim == _p_htim_timer) {
		_timer.IncTick(500); // 2 hz clock for blink the colon.
	}
}

