/*
 * Run.hpp
 *
 *  Created on: 30 Sept 2026
 *      Author: yuzek
 */
#include <stm32l4xx_hal.h>

#ifndef MYCODE_RUN_HPP_
#define MYCODE_RUN_HPP_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus.

struct RUN_DESC {
	ADC_HandleTypeDef* p_hadc_joystick;
	I2C_HandleTypeDef* p_hi2c_display;
	TIM_HandleTypeDef* p_htim_display_delay_timer;
	UART_HandleTypeDef* p_huart_debug_putty;
};
void Run(struct RUN_DESC);


#ifdef __cplusplus
}
#endif // __cplusplus.
#endif /* MYCODE_RUN_HPP_ */
