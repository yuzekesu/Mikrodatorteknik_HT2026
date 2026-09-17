/*
 * tarning.c
 *
 *  Created on: 9 Sept 2026
 *      Author: yuzek
 */
#include "tarning.h"
#include <stdbool.h>
#include "main.h"

#define LEFT_PORT DI_LEFT_GPIO_Port
#define LEFT_PIN DI_LEFT_Pin
#define MIDDLE_PORT DI_MIDDLE_GPIO_Port
#define MIDDLE_PIN DI_MIDDLE_Pin
#define RIGHT_PORT DI_RIGHT_GPIO_Port
#define RIGHT_PIN DI_RIGHT_Pin
#define LEFTTOP_PORT DI_LEFTTOP_GPIO_Port
#define LEFTTOP_PIN DI_LEFTTOP_Pin
#define LEFTBOTTOM_PORT DI_LEFTBOTTOM_GPIO_Port
#define LEFTBOTTOM_PIN DI_LEFTBOTTOM_Pin
#define RIGHTTOP_PORT DI_RIGHTTOP_GPIO_Port
#define RIGHTTOP_PIN DI_RIGHTTOP_Pin
#define RIGHTBOTTOM_PORT DI_RIGHTBOTTOM_GPIO_Port
#define RIGHTBOTTOM_PIN DI_RIGHTBOTTOM_Pin

uint8_t _tarning_history = 1;

uint8_t tarning_history(){
	return _tarning_history;
}

void tarning_idle(){
	_tarning_set(_tarning_history, true);
}

void _tarning_set(uint8_t number, bool state) {
	const GPIO_PinState desireState = state ? GPIO_PIN_SET : GPIO_PIN_RESET;
	switch (number) {
	case 1:
		HAL_GPIO_WritePin(MIDDLE_PORT, MIDDLE_PIN, desireState);
		break;
	case 2:
		HAL_GPIO_WritePin(LEFTTOP_PORT, LEFTTOP_PIN, desireState);
		HAL_GPIO_WritePin(RIGHTBOTTOM_PORT, RIGHTBOTTOM_PIN, desireState);
		break;
	case 3:
		HAL_GPIO_WritePin(LEFT_PORT, LEFT_PIN, desireState);
		HAL_GPIO_WritePin(MIDDLE_PORT, MIDDLE_PIN, desireState);
		HAL_GPIO_WritePin(RIGHT_PORT, RIGHT_PIN, desireState);
		break;
	case 4:
		HAL_GPIO_WritePin(LEFTTOP_PORT, LEFTTOP_PIN, desireState);
		HAL_GPIO_WritePin(RIGHTBOTTOM_PORT, RIGHTBOTTOM_PIN, desireState);
		HAL_GPIO_WritePin(LEFTBOTTOM_PORT, LEFTBOTTOM_PIN, desireState);
		HAL_GPIO_WritePin(RIGHTTOP_PORT, RIGHTTOP_PIN, desireState);
		break;
	case 5:
		HAL_GPIO_WritePin(MIDDLE_PORT, MIDDLE_PIN, desireState);
		HAL_GPIO_WritePin(LEFTTOP_PORT, LEFTTOP_PIN, desireState);
		HAL_GPIO_WritePin(RIGHTBOTTOM_PORT, RIGHTBOTTOM_PIN, desireState);
		HAL_GPIO_WritePin(LEFTBOTTOM_PORT, LEFTBOTTOM_PIN, desireState);
		HAL_GPIO_WritePin(RIGHTTOP_PORT, RIGHTTOP_PIN, desireState);
		break;
	case 6:
		HAL_GPIO_WritePin(LEFT_PORT, LEFT_PIN, desireState);
		HAL_GPIO_WritePin(RIGHT_PORT, RIGHT_PIN, desireState);
		HAL_GPIO_WritePin(LEFTTOP_PORT, LEFTTOP_PIN, desireState);
		HAL_GPIO_WritePin(RIGHTBOTTOM_PORT, RIGHTBOTTOM_PIN, desireState);
		HAL_GPIO_WritePin(LEFTBOTTOM_PORT, LEFTBOTTOM_PIN, desireState);
		HAL_GPIO_WritePin(RIGHTTOP_PORT, RIGHTTOP_PIN, desireState);
		break;
	default:
		HAL_GPIO_WritePin(LEFT_PORT, LEFT_PIN, desireState);
		HAL_GPIO_WritePin(MIDDLE_PORT, MIDDLE_PIN, desireState);
		HAL_GPIO_WritePin(RIGHT_PORT, RIGHT_PIN, desireState);
		HAL_GPIO_WritePin(LEFTTOP_PORT, LEFTTOP_PIN, desireState);
		HAL_GPIO_WritePin(RIGHTBOTTOM_PORT, RIGHTBOTTOM_PIN, desireState);
		HAL_GPIO_WritePin(LEFTBOTTOM_PORT, LEFTBOTTOM_PIN, desireState);
		HAL_GPIO_WritePin(RIGHTTOP_PORT, RIGHTTOP_PIN, desireState);
		break;
	}
}

void tarning_roll() {
	_tarning_set(_tarning_history, false);
	int randomNumber = _tarning_history % 6 + 1;
	_tarning_history = randomNumber;
	tarning_idle();
}


