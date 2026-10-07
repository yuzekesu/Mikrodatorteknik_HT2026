/*
 * Run.cpp
 *
 *  Created on: 30 Sept 2026
 *      Author: yuzek
 */

#include <stm32l4xx_hal.h>
#include <string>
#include "Run.hpp"
#include "HD44780U.h"
#include "JoyStick.h"

void Helper_Test_ADC(ADC_HandleTypeDef*, HD44780U::Display&);
ADC_HandleTypeDef *_p_hadc = nullptr;
HW504::JoyStick* _p_joystick = nullptr;

void Run(struct RUN_DESC desc) {
	// initialization.
	_p_hadc = desc.p_hadc_joystick;
	HD44780U::Display display { desc.p_htim_display_delay_timer->Instance, desc.p_hi2c_display, 0x4E };
	HW504::JoyStick joystick { desc.p_hadc_joystick };
	_p_joystick = &joystick;
	HAL_ADC_Start_IT(desc.p_hadc_joystick);
	// super loop.
	while (1) {
		// Helper_Test_ADC(desc.p_hadc_joystick, display);
		display.Home();
		display.Clear();
		HW504::JoyStick::NormalizedVector joystick_vector = joystick.NormalizePosNeg();
		display.Printf("%+.2fx", joystick_vector.x);
		display.Position(0, 1);
		display.Printf("%+.2fy", joystick_vector.y);
		HAL_Delay(200);
	}
	return;
}

void Helper_Test_ADC(ADC_HandleTypeDef *p_hadc, HD44780U::Display &display) {
	HAL_ADC_Start(p_hadc);
	HAL_ADC_PollForConversion(p_hadc, 100);
	uint32_t reading = HAL_ADC_GetValue(p_hadc);
	HAL_ADC_Stop(p_hadc);
	display.Home();
	display.Clear();
	display.Printf("%d", reading);
	HAL_Delay(200);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	if (hadc != _p_hadc || nullptr == _p_joystick)
		return;
	static int queue = 0;
	if (queue > 1)
		queue = 0; // reaches value in my own "ARR" haha.

	// joystick.
	if (queue < 2) {
		_p_joystick->UpdateViaInterrupt();
	}
	// foto sensor.
	else {
		;
	}

	++queue;
}

