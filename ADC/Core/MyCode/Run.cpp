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
#include "Fotosensor.h"

void Helper_Test_ADC(ADC_HandleTypeDef*, HD44780U::Display&);
ADC_HandleTypeDef *_p_hadc = nullptr;
HW504::JoyStick* _p_joystick = nullptr;
BFSSensorSeries::Fotosensor* _p_fotosensor = nullptr;
bool _adc_update_standing_by = false;

void Run(struct RUN_DESC desc) {
	// initialization.
	_p_hadc = desc.p_hadc_joystick;
	HD44780U::Display display { desc.p_htim_display_delay_timer->Instance, desc.p_hi2c_display, 0x4E };
	HW504::JoyStick joystick { desc.p_hadc_joystick };
	_p_joystick = &joystick;
	BFSSensorSeries::Fotosensor fotosensor{desc.p_hadc_joystick};
	_p_fotosensor = &fotosensor;
	HAL_ADC_Start_IT(desc.p_hadc_joystick);
	// super loop.
	while (1) {
		// Helper_Test_ADC(desc.p_hadc_joystick, display);
		if (_adc_update_standing_by) {
			_adc_update_standing_by = false;
			display.Home();
			display.Clear();
			HW504::JoyStick::NormalizedVector joystick_vector = joystick.NormalizePosNeg();
			display.Printf("%+.2fx", joystick_vector.x);
			display.Position(0, 1);
			display.Printf("%+.2fy", joystick_vector.y);
			display.Position(10, 0);
			display.PutStr("Skip~!");
			display.Position(10, 1);
			display.Printf("%.3fL", fotosensor.Normalize());
		}
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
	if (hadc != _p_hadc || nullptr == _p_joystick || nullptr == _p_fotosensor)
		return;
	static int queue = 0;
	if (queue > 2) {
		queue = 0; // reaches value in my own "ARR" haha.
	}

	// joystick.
	if (queue < 2) {
		_p_joystick->UpdateViaInterrupt();
	}
	// foto sensor.
	else {
		_p_fotosensor->UpdateViaInterrupt();
		_adc_update_standing_by = true;
	}

	++queue;
}

