/*
 * trafikljus.c
 *
 *  Created on: 15 Sept 2026
 *      Author: yuzek
 */
#include "main.h"
#include "eventState.h"
#include "trafikljus.h"
#include <stdint.h>

#define D_GLOBAL_PORT GPIOC
#define D_C_RED D_7_Pin
#define D_C_YELLOW D_3_Pin
#define D_C_GREEN D_2_Pin
#define D_P_RED  D_1_Pin
#define D_P_GREEN  D_0_Pin



void _helper_traffic_lights(char* str)
{
	HAL_GPIO_WritePin(D_GLOBAL_PORT, D_C_RED, str[0] == '1' ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D_GLOBAL_PORT, D_C_YELLOW, str[1] == '1' ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D_GLOBAL_PORT, D_C_GREEN, str[2] == '1' ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D_GLOBAL_PORT, D_P_RED, str[3] == '1' ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D_GLOBAL_PORT, D_P_GREEN, str[4] == '1' ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void set_traffic_lights(enum state s)
{
	switch (s)
	{
	case s_init: _helper_traffic_lights("11111"); break;
	case s_people_walk: _helper_traffic_lights("10001"); break;
	case s_car_standing_by: _helper_traffic_lights("10010"); break;
	case s_people_stop: _helper_traffic_lights("11010"); break;
	case s_car_go: _helper_traffic_lights("00110"); break;
	case s_pushed_wait: _helper_traffic_lights("00110"); break;
	case s_car_is_stopping: _helper_traffic_lights("01010"); break;
	case s_car_stop: _helper_traffic_lights("10010"); break;
	default: break;
	}
}

void set_push_button_light(int isOn, GPIO_TypeDef* port, uint16_t pin)
{
	HAL_GPIO_WritePin(port, pin, isOn ? GPIO_PIN_SET : GPIO_PIN_RESET);
}



