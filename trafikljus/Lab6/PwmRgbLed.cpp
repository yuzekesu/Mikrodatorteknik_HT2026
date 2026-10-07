/*
 * PwmRgbLed.cpp
 *
 *  Created on: 7 Oct 2026
 */

#include "PwmRgbLed.h"

namespace PWM {

RgbLed::RgbLed(TIM_HandleTypeDef *p_htim) : _p_htim(p_htim) {
}

bool RgbLed::Start() {
	// TIM1 is 16-bit. Reserve ARR + 1 as a representable 100% duty value.
	if (nullptr == this->_p_htim || this->_p_htim->Instance != TIM1)
		return false;
	if (__HAL_TIM_GET_AUTORELOAD(this->_p_htim) >= 65535u)
		return false;
	if ((this->_p_htim->Instance->CR1 & (TIM_CR1_DIR | TIM_CR1_CMS)) != 0u)
		return false;

	// Load the zero-duty preloads before enabling the outputs.
	this->Set(0.f, 0.f, 0.f);
	if (HAL_TIM_GenerateEvent(this->_p_htim, TIM_EVENTSOURCE_UPDATE) != HAL_OK)
		return false;
	__HAL_TIM_CLEAR_FLAG(this->_p_htim, TIM_FLAG_UPDATE);
	if (HAL_TIM_PWM_Start(this->_p_htim, TIM_CHANNEL_1) != HAL_OK)
		return false;
	if (HAL_TIM_PWM_Start(this->_p_htim, TIM_CHANNEL_2) != HAL_OK)
		return false;
	if (HAL_TIM_PWM_Start(this->_p_htim, TIM_CHANNEL_3) != HAL_OK)
		return false;
	return true;
}

void RgbLed::Set(float red, float green, float blue) {
	if (nullptr == this->_p_htim || this->_p_htim->Instance != TIM1)
		return;
	__HAL_TIM_SET_COMPARE(this->_p_htim, TIM_CHANNEL_1,
			this->_ToCompare(this->_Clamp(red) * this->_red_balance));
	__HAL_TIM_SET_COMPARE(this->_p_htim, TIM_CHANNEL_2,
			this->_ToCompare(this->_Clamp(green) * this->_green_balance));
	__HAL_TIM_SET_COMPARE(this->_p_htim, TIM_CHANNEL_3,
			this->_ToCompare(this->_Clamp(blue) * this->_blue_balance));
}

void RgbLed::SetBalance(float red, float green, float blue) {
	// Attenuate the stronger colours; no gain may request more than 100% duty.
	this->_red_balance = this->_Clamp(red);
	this->_green_balance = this->_Clamp(green);
	this->_blue_balance = this->_Clamp(blue);
}

float RgbLed::_Clamp(float value) {
	if (!(value > 0.f)) // also treats NaN as off.
		return 0.f;
	if (value >= 1.f)
		return 1.f;
	return value;
}

uint32_t RgbLed::_ToCompare(float brightness) {
	const uint32_t steps = __HAL_TIM_GET_AUTORELOAD(this->_p_htim) + 1u;
	return static_cast<uint32_t>(this->_Clamp(brightness) * static_cast<float>(steps) + 0.5f);
}

} /* namespace PWM */
