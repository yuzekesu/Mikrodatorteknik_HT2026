/*
 * uart.c
 *
 *  Created on: 22 Sept 2026
 *      Author: yuzek
 */
#include "uart.h"
#include "main.h"
#include <stdio.h>
#include <stdarg.h>

char _lastInput = '\0';
UART_HandleTypeDef* _p_huart = 0;

void uart_set_handle(UART_HandleTypeDef* pointer) {
	_p_huart = pointer;
}
void uart_print(char* str, ...) {
	if (_p_huart == 0) return;
	const int OUTPUT_SIZE = 100;
	char output[OUTPUT_SIZE];
	for (int i = 0; i < OUTPUT_SIZE; ++i) {
		output[i] = '\0';
	}
	va_list valist;
	va_start(valist, str);
	vsnprintf(output, OUTPUT_SIZE, str, valist);
	va_end(valist);
	HAL_UART_Transmit(_p_huart, (uint8_t*)output, OUTPUT_SIZE, HAL_MAX_DELAY);
}
void uart_print_menu(){
	uart_print("This is very nice menu, yes?\r\n");
	uart_print("Choose your density:\r\n");
	uart_print("\r\n");
	uart_print("\t\t1. Clock mode.\r\n");
	uart_print("\t\t2. Button mode.\r\n");
	uart_print("\r\n");
}
int uart_get_menu_choice(){
	if (_p_huart == 0) return -2;
	char str[5] = "12345";
	uint16_t str_len = 1;
	HAL_UART_Receive(_p_huart, (uint8_t *) str, str_len, HAL_MAX_DELAY);
	int ret = -1;
	str[1] = 0;
	sscanf(str, "%d", &ret);
	_lastInput = str[0];
	return ret;
}
void uart_print_bad_choice(){
	uart_print("The input \"%c\" is not valid, please try again... \r\n", _lastInput);
}
