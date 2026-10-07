/*
 * PwmRgbLed.h
 *
 *  Created on: 7 Oct 2026
 */

#ifndef MYCODE_PWM_RGB_LED_H_
#define MYCODE_PWM_RGB_LED_H_

#include <stm32l4xx_hal.h>
#include <cstdint>

namespace PWM {

// TIM1: CH1 = red, CH2 = green, CH3 = blue. Configure PWM mode 1, counting up.
class RgbLed {
public:
	RgbLed() = delete;
	RgbLed(TIM_HandleTypeDef *p_htim);
	bool Start();
	void Set(float red, float green, float blue);
	void SetBalance(float red, float green, float blue);
private:
	TIM_HandleTypeDef *_p_htim;
	float _red_balance = 1.f;
	float _green_balance = 1.f;
	float _blue_balance = 1.f;
	static float _Clamp(float value);
	uint32_t _ToCompare(float brightness);
};

} /* namespace PWM */

#endif /* MYCODE_PWM_RGB_LED_H_ */
