/*
 * Run.hpp
 *
 *  Created on: 30 Sept 2026
 *      Author: yuzek
 */
#include <stm32l4xx_hal.h>
#include "lcd.h"

#ifndef MYCODE_RUN_HPP_
#define MYCODE_RUN_HPP_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus.

struct RUN_DESC {
	TIM_HandleTypeDef *p_htim_1MHz_lcd;
	UART_HandleTypeDef *p_huart;
	TIM_HandleTypeDef *p_htim_timer;
	TextLCDType* p_hlcd;
};
void Run(struct RUN_DESC);


#ifdef __cplusplus
}
#endif // __cplusplus.
#endif /* MYCODE_RUN_HPP_ */
