/*
 * _TimeCallback.cpp
 *
 *  Created on: 29 Sept 2026
 *      Author: yuzek
 */
#include <main.h>
#include <_TimeCallback.hpp>
#include <_ButtonCallback.hpp>
#include <Timer.hpp>
#include <quad_sseg.h>
#include <cstdint>
#include <vector>

std::vector<TIM_HandleTypeDef*> TimeCallback::_vector;

Timer _timer;

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	TimeCallback::HandleTIM1(htim);
}

void TimeCallback::Initialize() {
	TimeCallback::_vector.resize(17, nullptr);
}

Timer& TimeCallback::GetTimer() {
	return _timer;
}

void TimeCallback::SetTimHandle(TIM_HandleTypeDef *p_htim, std::size_t number_tag) {
	if (number_tag >= TimeCallback::_vector.size())
		return;
	TimeCallback::_vector[number_tag] = p_htim;
}

void TimeCallback::HandleTIM1(TIM_HandleTypeDef *p_unknown_htim) {
	if (p_unknown_htim != TimeCallback::_vector[1])
		return;
	static bool flag_2hz = true;
	flag_2hz = !flag_2hz;
	if (flag_2hz) {
		_timer.Add(1);
	}
	uint32_t big_num = (uint32_t) _timer.GetAll();
	uint8_t ones = (uint8_t)((big_num / 1) % 10);
	uint8_t tens = (uint8_t)((big_num / 10) % 10);
	uint8_t huns = (uint8_t)((big_num / 100) % 10);
	uint8_t thus = (uint8_t)((big_num / 1000) % 10);
	uint8_t tthu = (uint8_t)((big_num / 10000) % 10);
	uint8_t ttth = (uint8_t)((big_num / 100000) % 10);
	if (!ButtonCallBack::GetButton().IsPressing() && HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET) {

		qs_put_digits(thus, huns, tens, ones, flag_2hz);
	}
	else {
		qs_put_digits(ttth, tthu, thus, huns, flag_2hz);
	}
}

