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

void uart_print(char* str, ...) {
	const int OUTPUT_SIZE = 100;
	char output[OUTPUT_SIZE];
	va_list valist;
	va_start(valist, str);
	snprintf(output, OUTPUT_SIZE, valist);
	va_end(valist);
	HAL_UART_Transmit(&huart2, output, OUTPUT_SIZE, HAL_MAX_DELAY);
}
void uart_print_menu(){
	char a[];
}
int uart_get_menu_choice(){
	char str[1] = { '\0' };
	uint16_t str_len = 1;
	HAL_UART_Receive(&huart2,
	(uint8_t *) str,
	str_len,
	HAL_MAX_DELAY);
	int ret = -1;
	sscanf(str, "%d", &ret);
	return ret;
}
void uart_print_bad_choice(){

}
