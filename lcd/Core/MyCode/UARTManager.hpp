/*
 * uart.hpp
 *
 *  Created on: 29 Sept 2026
 *      Author: yuzek
 */
#include <stm32l4xx_hal.h>
#include <cstdarg>

#ifndef INC_UART_HPP_
#define INC_UART_HPP_

class UARTManager {
public:
	UARTManager() = delete;
	UARTManager(UART_HandleTypeDef*, std::size_t output_size = 100u);
	bool Good();
	bool Fail();
	void Print(const char*, ...);
	void PrintLn(const char*, ...);
	char GetChar();
	int GetDigit();
	char GetPreviousInput();
private:
	UART_HandleTypeDef* _p_output_huart = nullptr;
	std::size_t _output_size = 0u;
	bool _did_error_happen = false;
	char _p_last_input[2] = {'\0'};
	void _GetInput();
	void _Print(const char*);
	void _PrintVA(const char*, std::va_list);
};

#endif /* INC_UART_HPP_ */
