/*
 * JoyStick.cpp
 *
 *  Created on: 7 Oct 2026
 *      Author: yuzek
 */
#include <stm32l4xx_hal.h>
#include "JoyStick.h"

namespace HW504 {

JoyStick::JoyStick(ADC_HandleTypeDef *p_hadc) : _p_hadc(p_hadc) {
}

// always starts with the x value, next time Update() calls it updates y value.
void JoyStick::Update() {
	// queue.
	uint32_t &value = this->_is_next_input_x_value ? this->_vector._x : this->_vector._y;
	this->_is_next_input_x_value = !this->_is_next_input_x_value;
	// read value from adc.
	HAL_ADC_Start(this->_p_hadc);
	HAL_ADC_PollForConversion(this->_p_hadc, 100);
	value = HAL_ADC_GetValue(this->_p_hadc);
	HAL_ADC_Stop(this->_p_hadc);
}

// always starts with the x value, next time Update() calls it updates y value.
void JoyStick::UpdateViaInterrupt() {
	// queue.
	uint32_t &value = this->_is_next_input_x_value ? this->_vector._x : this->_vector._y;
	this->_is_next_input_x_value = !this->_is_next_input_x_value;
	// read value from adc.
	value = HAL_ADC_GetValue(this->_p_hadc);
}

JoyStick::NormalizedVector JoyStick::Normalize() {
	JoyStick::NormalizedVector result { };
	result.x = static_cast<float>(this->_vector._x) / 4095.f;
	result.y = static_cast<float>(this->_vector._y) / 4095.f;
	return result;
}

JoyStick::NormalizedVector JoyStick::NormalizePosNeg() {
	JoyStick::NormalizedVector result { };
	result.x = static_cast<float>(this->_vector._x) / (4095.f / 2.f) - 1.f;
	result.y = static_cast<float>(this->_vector._y) / (4095.f / 2.f) - 1.f;
	return result;
}

} /* namespace HW504 */
