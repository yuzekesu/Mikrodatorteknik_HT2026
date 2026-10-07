/*
 * ColorCycle.h
 *
 *  Created on: 7 Oct 2026
 */

#ifndef MYCODE_COLOR_CYCLE_H_
#define MYCODE_COLOR_CYCLE_H_

#include "PwmRgbLed.h"
#include <cstdint>

namespace PWM {

class ColorCycle {
public:
	ColorCycle(RgbLed &led, float update_frequency_hz);
	// Call only from the TIM1 period-elapsed callback: integer work only.
	void UpdateViaInterrupt();
	// Call from the main loop. Returns false if no new period has elapsed.
	bool Update(float frequency_hz);
private:
	RgbLed &_led;
	float _update_frequency_hz;
	volatile uint32_t _interrupt_count = 0u;
	uint32_t _last_interrupt_count = 0u;
	float _phase = 0.f;
};

} /* namespace PWM */

#endif /* MYCODE_COLOR_CYCLE_H_ */
