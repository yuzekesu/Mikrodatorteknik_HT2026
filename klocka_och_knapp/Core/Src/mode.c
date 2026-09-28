/*
 * mode.c
 *
 *  Created on: 23 Sept 2026
 *      Author: yuzek
 */
#include "main.h"
#include "button.h"
#include "quad_sseg.h"

void clock_mode() {
	/*** init segment ***/
	/*** main loop ***/
	while (1) {
		break;
	}
}
void button_mode() {
	/*** init segment ***/
	/*** main loop ***/
	int b1_pressed;
	while (1) {
		/* deal with debouncing the button... */
		// check b1 button (on board, active low)
		b1_pressed = GPIO_PIN_RESET == HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);
		qs_put_big_num(b1_pressed ? button_get_registered_press_count() : button_get_debounce_count());
	}
}
