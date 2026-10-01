/*
 * main.hpp
 *
 *  Created on: 29 Sept 2026
 *      Author: yuzek
 */
#include "stm32l4xx_hal.h"

#ifndef SRC_MAIN_HPP_
#define SRC_MAIN_HPP_
struct RUN_DESC {
	UART_HandleTypeDef* p_huart;
	TIM_HandleTypeDef* p_htim;
};

#ifdef __cplusplus
extern "C" {
#endif

void run(struct RUN_DESC desc);

#ifdef __cplusplus
}
#endif

#endif /* SRC_MAIN_HPP_ */
