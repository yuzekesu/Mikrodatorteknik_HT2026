/*
 * ColorCycle.cpp
 *
 *  Created on: 7 Oct 2026
 */

#include "ColorCycle.h"
#include <cmath>

namespace PWM {

ColorCycle::ColorCycle(RgbLed &led, float update_frequency_hz) :
		_led(led), _update_frequency_hz(update_frequency_hz) {
}

void ColorCycle::UpdateViaInterrupt() {
	++this->_interrupt_count;
}

bool ColorCycle::Update(float frequency_hz) {
	if (!(this->_update_frequency_hz > 0.f) || !std::isfinite(this->_update_frequency_hz))
		return false;
	if (!(frequency_hz >= 0.f) || !std::isfinite(frequency_hz))
		return false;

	// One aligned 32-bit load on Cortex-M4. Main never resets the ISR's counter.
	const uint32_t now = this->_interrupt_count;
	const uint32_t elapsed = now - this->_last_interrupt_count;
	if (elapsed == 0u)
		return false;
	this->_last_interrupt_count = now;

	// Count every elapsed timer period, even if main was temporarily busy.
	constexpr float two_pi = 6.2831853071795864769f;
	constexpr float offset = two_pi / 3.f;
	const float seconds = static_cast<float>(elapsed) / this->_update_frequency_hz;
	this->_phase = std::fmod(this->_phase + two_pi * frequency_hz * seconds, two_pi);

	const float red = (std::sin(this->_phase) + 1.f) * 0.5f;
	const float green = (std::sin(this->_phase + offset) + 1.f) * 0.5f;
	const float blue = (std::sin(this->_phase + 2.f * offset) + 1.f) * 0.5f;
	this->_led.Set(red, green, blue);
	return true;
}

} /* namespace PWM */
