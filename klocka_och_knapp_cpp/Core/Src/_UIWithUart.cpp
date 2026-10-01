/*
 * UIWithUart.cpp
 *
 *  Created on: 29 Sept 2026
 *      Author: yuzek
 */

#include <_UIWithUart.hpp>

UIWithUart::UIWithUart(UART_HandleTypeDef *p_huart) :
		_uart(p_huart) {
}

void UIWithUart::PrintMenu() {
	this->_uart.PrintLn("This is very nice menu, yes?");
	this->_uart.PrintLn("Choose your density:");
	this->_uart.PrintLn("");
	this->_uart.PrintLn("\t\t1. Clock mode.");
	this->_uart.PrintLn("\t\t2. Button mode.");
	this->_uart.PrintLn("");
}

void UIWithUart::PrintError() {
	// reserved.
	this->_uart.PrintLn("The input was \"%c\".", this->_uart.GetPreviousInput());
	this->_uart.PrintLn("");
	this->_uart.PrintLn("");
	this->_uart.PrintLn("");
	this->_uart.PrintLn("");
}

int UIWithUart::GetInput() {
	return this->_uart.GetDigit();
}

