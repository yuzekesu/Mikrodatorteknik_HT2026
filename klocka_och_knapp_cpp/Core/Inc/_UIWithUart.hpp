/*
 * UIWithUart.hpp
 *
 *  Created on: 29 Sept 2026
 *      Author: yuzek
 */

#include <UARTManager.hpp>
#include <main.h>

#ifndef INC_UIWITHUART_HPP_
#define INC_UIWITHUART_HPP_

class UIWithUart {
public:
	UIWithUart() = delete;
	UIWithUart(UART_HandleTypeDef*);
	void PrintMenu();
	void PrintError();
	int GetInput();
private:
	UARTManager _uart;
};

#endif /* INC_UIWITHUART_HPP_ */
