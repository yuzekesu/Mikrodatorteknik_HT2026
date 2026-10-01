/*
 * .ButtonCallback.cpp
 *
 *  Created on: 29 Sept 2026
 *      Author: yuzek
 */
#include <main.h>
#include <ButtonManager.hpp>
#include <_ButtonCallback.hpp>

ButtonManager _button(MY_BTN_GPIO_Port, MY_BTN_Pin);

ButtonManager& ButtonCallBack::GetButton() {
	return _button;
}

extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin != MY_BTN_Pin && GPIO_Pin != B1_Pin) return;
	_button.Set(GPIO_PIN_RESET == HAL_GPIO_ReadPin(MY_BTN_GPIO_Port, MY_BTN_Pin));
}


