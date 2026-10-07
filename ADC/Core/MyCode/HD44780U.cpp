/*
 * HD44780U.cpp
 *
 *  Created on: 5 Oct 2026
 *      Author: yuzek
 */

#include "HD44780U.h"
#include <stm32l4xx_hal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

HD44780U::Display::Display(TIM_TypeDef* p_tim, I2C_HandleTypeDef *hi2c, uint8_t device_address) : _p_tim(p_tim){
	// TODO Auto-generated constructor stub
	this->_p_hi2c = hi2c;
	this->_device_address = device_address;

	uint8_t data = 0x30; // b# 0011 1000
	uint8_t ctrl = 0x08;

	this->_Delay(70000);

	this->_SendNibbleWithPulseOnE(data | ctrl);
	this->_SendNibbleWithPulseOnE(data | ctrl);
	this->_SendNibbleWithPulseOnE(data | ctrl);

	data = 0x20;
	this->_SendNibbleWithPulseOnE(data | ctrl);

	// Finished setting up 4-bit mode. Let's configure display

	// hlcd, data, rs, rw
	this->_SendByte(0x28, 0); //N=1 (2 line), F=0 (5x8)

	this->_SendByte(0x0F, 0); //Display off, Cursor Off, Blink off
	this->_SendByte(0x01, 0);
	this->_Delay(5000);

	this->_SendByte(0x06, 0);
	this->_SendByte(0x0C, 0);
}

// first:   D7 D6 D5 D4 this->_BT E  this->_RW RS
// second:  D3 D2 D1 D0 this->_BT E  this->_RW RS

/*
 * my = mu = micro
 * Holds for an amount of microseconds.
 */
void HD44780U::Display::_Delay(uint32_t micro_second) {
	// HAL_Delay(1 + (micro_second / 1000));
	// starta och nollställ TIM2.
	this->_p_tim->CNT = 0;
	this->_p_tim->CR1 |= (1 << 0); // control register 1, Bit 0 CEN: Counter enable.
	// vänta tills rätt antal mikrosekunder har gått.
	while (this->_p_tim->CNT < micro_second);
	// stoppa TIM2.
	this->_p_tim->CR1 &= ~(1 << 0);
}

#define BIT_BT   0x08
#define BIT_E    0x04    // 0000 0100 == 0x08
#define BIT_RW   0x02
#define BIT_RS   0x01

#define INV_BT  ~BIT_BT
#define INV_E   ~BIT_E   // 1111 1011 == 0xFB
#define INV_RW  ~BIT_RW
#define INV_RS  ~BIT_RS

/***************************************************************************
 *  Nibble should be in the MSB part as the lower four will be control.
 *
 * So the bits are
 *
 *  MSB b7   b6   b5   b4   b3   b2   b1   b0  LSB
 *
 *      D3   D2   D1   D0   this->_BT    E   this->_RW   RS
 *
 *  When sending a byte, use this twice, sending D7-D4 the first time
 *  and D3-D0 the second time.
 ****************************************************************************/
void HD44780U::Display::_SendNibbleWithPulseOnE(uint8_t data) {
	/***** Put nibble when E is low *****/
	data = data & INV_E;
	HAL_I2C_Master_Transmit(this->_p_hi2c, this->_device_address, &data, 1, 1000);
	this->_Delay(2000);

	/***** Now set E to high *****/
	data = data | BIT_E;
	HAL_I2C_Master_Transmit(this->_p_hi2c, this->_device_address, &data, 1, 1000);
	this->_Delay(2000);

	/***** Then go low again *****/
	data = data & INV_E;
	HAL_I2C_Master_Transmit(this->_p_hi2c, this->_device_address, &data, 1, 1000);
}

void HD44780U::Display::_SendByte(uint8_t data, bool isRS) {
	// Place the data bits in the top four bits. The lowest four will
	// be for control.
	uint8_t d_lo = (data & 0x0F) << 4;
	uint8_t d_hi = (data & 0xF0);

	// Set the control bits for the message.
	uint8_t ctrl = 0x00;
	ctrl = (this->_BT == true) ? (ctrl | BIT_BT) : (ctrl & INV_BT);
	ctrl = (isRS == true) ? (ctrl | BIT_RS) : (ctrl & INV_RS);
	ctrl = (this->_RW == true) ? (ctrl | BIT_RW) : (ctrl & INV_RW);

	this->_SendNibbleWithPulseOnE(d_hi | ctrl);
	this->_SendNibbleWithPulseOnE(d_lo | ctrl);
}

void HD44780U::Display::SetBacklightFlag(bool bt) {
	this->_BT = bt;
}

void HD44780U::Display::Home() {
	this->_SendByte(0x02, false);
	this->_Delay(1520);
}

void HD44780U::Display::Clear() {
	this->_SendByte(0x01, false);
	// delay ?
}

void HD44780U::Display::SetDDRAMAdr(uint8_t adr) {
	// 00 1000 0000, set ddram address.
	this->_SendByte(0x80 | adr, false);
	this->_Delay(37);
}

void HD44780U::Display::Position(int col, int row) {
	// hex: 00 01 02 ...
	// hex: 40 41 42 ...
	if (col >= 16 || col < 0)
		return;
	if (row >= 2 || row < 0)
		return;
	int address = col + 0x40 * row;
	this->SetDDRAMAdr(address);
	this->_Delay(37);
}

void HD44780U::Display::PutChar(char c) {
	this->_SendByte((uint8_t) c, true);
	this->_Delay(4);
}

void HD44780U::Display::PutStr(const char *str) {
	for (int i = 0; str[i] != '\0'; ++i) {
		this->PutChar(str[i]);
	}
}

void HD44780U::Display::Printf(const char *message, ...) {
	char buffer[100];
	va_list valist;
	va_start(valist, message);
	vsnprintf(buffer, sizeof(buffer), message, valist);
	va_end(valist);
	this->PutStr(buffer);
}
#if 0
#endif

