/*
 * print.h
 *
 *  Created on: 2 Sept 2026
 *      Author: yuzek
 */
#include <stdio.h>
#include <stdarg.h>

#ifndef INC_PRINT_H_
#define INC_PRINT_H_


void print(UART_HandleTypeDef* hUart, const char* str, ...) {
	const size_t bufferSize = 100;
	char outputBuffer[bufferSize];
	va_list variable_list;
	va_start(variable_list, str);
	uint16_t sizeOfStr = vsnprintf(outputBuffer, bufferSize, str, variable_list);
	va_end(variable_list);
	HAL_UART_Transmit(hUart, (uint8_t*)outputBuffer, sizeOfStr, HAL_MAX_DELAY);
}


#endif /* INC_PRINT_H_ */
