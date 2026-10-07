/*
 * Run.cpp
 *
 *  Created on: 7 Oct 2026
 */

#include "Run.h"
#include "PwmRgbLed.h"
#include "ColorCycle.h"
#include "main.h"

// Task 1: false (empty loop, change CCR1/2/3 using the debugger).
// Task 2: true (enable TIM1 update interrupt in CubeMX first).
constexpr bool color_cycle_enabled = false;

// Colour cycle frequency, not the 1000 Hz PWM frequency. Editable in debugger.
volatile float freq = 0.2f;

namespace {

TIM_HandleTypeDef *_p_htim_pwm = nullptr;
PWM::ColorCycle *_p_color_cycle = nullptr;

float GetUpdateFrequency(TIM_HandleTypeDef *p_htim) {
	// On STM32L433, TIM1 uses APB2; a divided APB2 doubles the timer clock.
	uint32_t timer_clock = HAL_RCC_GetPCLK2Freq();
	if ((RCC->CFGR & RCC_CFGR_PPRE2) != 0u)
		timer_clock *= 2u;
	return static_cast<float>(timer_clock)
			/ static_cast<float>(p_htim->Instance->PSC + 1u)
			/ static_cast<float>(p_htim->Instance->ARR + 1u);
}

} /* namespace */

void Run(struct RUN_DESC desc) {
	if (nullptr == desc.p_htim_pwm || desc.p_htim_pwm->Instance != TIM1) {
		Error_Handler();
		return;
	}
	// One update per PWM period; this guide uses edge-aligned upcounting.
	if (desc.p_htim_pwm->Instance->RCR != 0u) {
		Error_Handler();
		return;
	}

	__HAL_DBGMCU_UNFREEZE_TIM1(); // Task 1 must keep PWM running while CPU is paused.
	PWM::RgbLed led { desc.p_htim_pwm };
	// Replace these neutral factors with your measured Task 1 balance factors.
	led.SetBalance(1.f, 1.f, 1.f);
	if (!led.Start()) {
		Error_Handler();
		return;
	}

	if (!color_cycle_enabled) {
		while (1) {
			// Task 1: hardware PWM continues; software does not overwrite CCRx.
		}
	}

	PWM::ColorCycle color_cycle { led, GetUpdateFrequency(desc.p_htim_pwm) };
	_p_htim_pwm = desc.p_htim_pwm;
	_p_color_cycle = &color_cycle;
	__HAL_TIM_CLEAR_FLAG(desc.p_htim_pwm, TIM_FLAG_UPDATE);
	if (HAL_TIM_Base_Start_IT(desc.p_htim_pwm) != HAL_OK) {
		Error_Handler();
		return;
	}

	while (1) {
		color_cycle.Update(freq);
	}
}

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim == _p_htim_pwm && nullptr != _p_color_cycle)
		_p_color_cycle->UpdateViaInterrupt();
}
