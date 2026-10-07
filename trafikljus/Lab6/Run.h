/*
 * Run.h
 *
 *  Created on: 7 Oct 2026
 */

#ifndef MYCODE_LAB6_RUN_H_
#define MYCODE_LAB6_RUN_H_

#include <stm32l4xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

struct RUN_DESC {
	TIM_HandleTypeDef *p_htim_pwm;
};

void Run(struct RUN_DESC desc);

#ifdef __cplusplus
}
#endif

#endif /* MYCODE_LAB6_RUN_H_ */
