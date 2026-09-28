/*
 * uart.h
 *
 *  Created on: 22 Sept 2026
 *      Author: yuzek
 */
#include "main.h"

#ifndef INC_UART_H_
#define INC_UART_H_

void uart_set_handle(UART_HandleTypeDef* pointer);
void uart_print_menu();
int uart_get_menu_choice();
void uart_print_bad_choice();

#endif /* INC_UART_H_ */
