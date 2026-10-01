/*
 * main.cpp
 *
 *  Created on: 29 Sept 2026
 *      Author: yuzek
 */
#include <_run.hpp>
#include <_UIWithUart.hpp>
#include "stm32l4xx_hal.h"
#include "button.h"
#include "mode.h"
#include <_ButtonCallback.hpp>
#include <_TimeCallback.hpp>
#include <quad_sseg.h>

extern "C" void run(struct RUN_DESC desc) {
	TimeCallback::Initialize(); // initialize the vector with resize.
	UIWithUart ui(desc.p_huart);
	TimeCallback::SetTimHandle(desc.p_htim, 1);
	while (1) {
		ui.PrintMenu();
		int menu_choice = ui.GetInput();
		ButtonManager& button = ButtonCallBack::GetButton();
		switch (menu_choice) {
		case 1:
			HAL_TIM_Base_Start_IT(desc.p_htim);
			while (1)
				;
			break;
		case 2:
			while(1)
			{
				/* deal with debouncing the button... */
				// check b1 button (on board, active low)
				qs_put_big_num(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET ? button.GetObservedCounter() : button.GetCounter());
			}
			break;
		default:
			ui.PrintError();
			break;
		}
	}
}
