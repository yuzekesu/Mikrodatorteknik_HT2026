/*
 * JoyStick.h
 *
 *  Created on: 7 Oct 2026
 *      Author: yuzek
 */
#include <stm32l4xx_hal.h>
#include <cstdint>
#include <string>

#ifndef MYCODE_JOYSTICK_H_
#define MYCODE_JOYSTICK_H_

namespace HW504 {

class JoyStick {
public:
	struct NormalizedVector {
		float x = 0.f, y = 0.f;
		explicit operator std::string();
	};
	JoyStick(ADC_HandleTypeDef *p_hadc);
	void Update();
	void UpdateViaInterrupt();
	JoyStick::NormalizedVector Normalize();
	JoyStick::NormalizedVector NormalizePosNeg();
private:
	bool _is_next_input_x_value = true;
	struct _Vector {
		uint32_t _x = 2047u, _y = 2047u;
	} _vector;
	ADC_HandleTypeDef *_p_hadc;

};

} /* namespace HW504 */

#endif /* MYCODE_JOYSTICK_H_ */
