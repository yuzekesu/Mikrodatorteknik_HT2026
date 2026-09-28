/*
 * button.c
 *
 *  Created on: 24 Sept 2026
 *      Author: yuzek
 */
#include "main.h"
#define BOUNCE_DELAY_MS 2
#define PIN MY_BTN_Pin
#define PORT MY_BTN_GPIO_Port

enum _s_button_state {
	idle, pressing
} _registered_button_state = idle, _observed_button_state;
uint16_t _button_exti_count = 0;
uint16_t _button_debounced_count = 0;
uint32_t _lastRegistredPressTimeStamp = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin != PIN)
		return;

	// logic.
	uint32_t currentTimeStamp = HAL_GetTick();
	_observed_button_state =
			GPIO_PIN_RESET == HAL_GPIO_ReadPin(PORT, PIN) ? pressing : idle;
	switch (_registered_button_state) {
	case idle:
		if (_observed_button_state == idle)
			break;
		++_button_exti_count;
		if (currentTimeStamp - _lastRegistredPressTimeStamp >= BOUNCE_DELAY_MS) {
			++_button_debounced_count;
			_lastRegistredPressTimeStamp = currentTimeStamp;
			_registered_button_state = pressing;
		}
		break;
	case pressing:
		if (_observed_button_state == pressing) {
		    ++_button_exti_count;
			break;
		}
		if (currentTimeStamp - _lastRegistredPressTimeStamp >= BOUNCE_DELAY_MS) {
			_lastRegistredPressTimeStamp = currentTimeStamp;
			_registered_button_state = idle;
		}
		break;
	default:
		break;
	}
}

uint16_t button_get_registered_press_count() {
	return _button_exti_count;
}

uint16_t button_get_debounce_count() {
	return _button_debounced_count;
}

int button_is_pressing() {
	int state = 0;
	if (_registered_button_state == pressing)
		state = 1;
	return state;
}

void button_initialize() {
	_lastRegistredPressTimeStamp = HAL_GetTick();
}

