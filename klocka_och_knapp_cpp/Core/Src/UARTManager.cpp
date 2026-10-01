/*
 * uart.cpp
 *
 *  Created on: 29 Sept 2026
 *      Author: yuzek
 */
#include <UARTManager.hpp>
#include <cstdarg>
#include <cstdio>
#include <cstring>

UARTManager::UARTManager(UART_HandleTypeDef *p_huart, std::size_t output_size) :
		_p_output_huart(p_huart), _output_size(output_size) {
}

bool UARTManager::Good() {
	return !this->_did_error_happen;
}

bool UARTManager::Fail() {
	return this->_did_error_happen;
}

void UARTManager::Print(const char *str, ...) {
	std::va_list valist;
	va_start(valist, str);
	this->_PrintVA(str, valist);
	va_end(valist);
}

void UARTManager::PrintLn(const char *str, ...) {
	std::va_list valist;
	va_start(valist, str);
	this->_PrintVA(str, valist);
	va_end(valist);
	this->_Print("\r\n");
}

char UARTManager::GetChar() {
	this->_GetInput();
	this->_did_error_happen = false;
	return this->_p_last_input[0];
}

int UARTManager::GetDigit() {
	this->_GetInput();
	int result = -1;
	int input_cnt = sscanf(this->_p_last_input, "%d", &result);
	this->_did_error_happen = input_cnt == 0 ? true : false;
	return result;
}

void UARTManager::_GetInput() {
	HAL_UART_Receive(this->_p_output_huart, (uint8_t*) this->_p_last_input, 1,
	HAL_MAX_DELAY);
}

void UARTManager::_Print(const char* str) {
	HAL_UART_Transmit(this->_p_output_huart, (uint8_t*) str, std::strlen(str),
			HAL_MAX_DELAY);
}

void UARTManager::_PrintVA(const char *str, std::va_list valist) {
	char output[this->_output_size];
	std::size_t size = vsnprintf(output, this->_output_size, str, valist);
	HAL_UART_Transmit(this->_p_output_huart, (uint8_t*) output, size,
	HAL_MAX_DELAY);
}

char UARTManager::GetPreviousInput() {
	return this->_p_last_input[0];
}
