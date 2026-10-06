/*
 * Run.cpp
 *
 *  Created on: 30 Sept 2026
 *      Author: yuzek
 */

#include <stm32l4xx_hal.h>
#include <string>
#include <main.h>
// #include "../Inc/main.h"
#include "Run.hpp"
#include "UARTManager.hpp"
#include "Timer.hpp"
#include "ButtonManager.hpp"
// #include "lcd.h"
#include "HD44780U.h"

ButtonManager _button { }; // global button for callback.
bool _has_htim_exti_timer_handled = false;
TIM_HandleTypeDef *_p_htim_timer = nullptr;
UART_HandleTypeDef *_p_huart = nullptr;
void _Helper_Button_Wait();
void _Test_Display_Character_Output(HD44780U::Display&); // not calling by default, only for debugging the lcd.

void Run(struct RUN_DESC desc) {
	// initialization.
	// HAL_TIM_Base_Start_IT(_p_htim_1MHz_lcd);
	_p_htim_timer = desc.p_htim_timer;
	HAL_TIM_Base_Start_IT(_p_htim_timer);
	_p_huart = desc.p_huart;
	UARTManager uart { _p_huart };
	HD44780U::Display lcd {desc.p_htim_1MHz_lcd->Instance, desc.p_hlcd->hi2c, desc.p_hlcd->device_address };
	lcd.Clear();
	lcd.Home();
	Timer timer { 500 }; // 500 ms per tick.
	timer.Set(23, 59, 45); // heehee.

	// super loop.
	while (1) {
		// _Helper_Button_Wait();

		// bro, why.
		// I choose to lower coupling between interupt and the Timer class.
		// Thus I put the logic inside the super loop instead of having a Update() function.
		if (!_has_htim_exti_timer_handled) {
			timer.IncTick(500);
			_has_htim_exti_timer_handled = true;
		}

		// tick and the display.
		int ticks = timer.GetTick(); // 2 tick per second.
		if (ticks) {
			// uart.
			uart.PrintLn(static_cast<std::string>(timer).c_str());
			// lcd.
			lcd.Position(8, 1);
			// lcd, the blinky colons, ugly solution ;(.
			static bool shall_blink = false;
			std::string time_in_string = static_cast<std::string>(timer);
			if (shall_blink) {
				time_in_string[2] = ' ';
				time_in_string[5] = ' ';
			}
			shall_blink = !shall_blink;
			lcd.PutStr(time_in_string.c_str());
		}
	}
}

void _Helper_Button_Wait() {
	_button.WaitUntil(ButtonManager::WaitMode::SINGLE, false);
	HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
}

void _Test_Display_Character_Output(HD44780U::Display &lcd) {
	static char c = 0;
	const char ASCII_CAPITAL_OFFSET = 'A';
	const char LETTERS_TOTAL = 'Z' - 'A' + 1;

	static int column = 0;
	static int row = 0;
	row = row + column / 16;
	column %= 16;
	row %= 2;
	lcd.Position(column, row);
	//TextLCD_PutChar(desc.p_hlcd, c + ASCII_CAPITAL_OFFSET);
	lcd.PutChar(c + ASCII_CAPITAL_OFFSET);
	c = (c + 1) % LETTERS_TOTAL;
	++column;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *p_htim) {
	if (p_htim == _p_htim_timer) {
		_has_htim_exti_timer_handled = false;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin != B1_Pin)
		return;
	_button.Update(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET);
}

