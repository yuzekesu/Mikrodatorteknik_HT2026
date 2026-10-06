/*
 * HD44780U.h
 *
 *  Created on: 5 Oct 2026
 *      Author: yuzek
 */
#include <cstdint>
#include <stm32l4xx_hal.h>

#ifndef MYCODE_HD44780U_H_
#define MYCODE_HD44780U_H_

namespace HD44780U {

class Display {
public:
	Display() = delete;
	Display(TIM_TypeDef* p_tim, I2C_HandleTypeDef *hi2c, uint8_t device_address);
	void SetBacklightFlag(bool bt);
	void Home();
	void Clear();
	void SetDDRAMAdr(uint8_t adr);
	void Position(int col, int row);
	void PutChar(char c);
	void PutStr(const char *str); // changed to const char for support c_str() from std::string.
	void Printf(const char *message, ...);
private:
	TIM_TypeDef* _p_tim;
	uint32_t _counter_micro_seconds = 0;
	I2C_HandleTypeDef* _p_hi2c;
	uint8_t _device_address;
	void _SendNibbleWithPulseOnE(uint8_t data);
	void _SendByte(uint8_t data, bool isRS);
	void _Delay(uint32_t micro_second);
private:
	// Back light flag, is sent every command
	bool _BT = true;

	// Always be writing! (can't really read from the device)
	bool _RW = false;
};

} /* namespace HD44780U */

#endif /* MYCODE_HD44780U_H_ */
