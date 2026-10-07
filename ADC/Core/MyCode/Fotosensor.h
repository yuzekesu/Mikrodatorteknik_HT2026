/*
 * Fotosensor.h
 *
 *  Created on: Oct 7, 2026
 *      Author: yuzek
 */
#include <stm32l4xx_hal.h>
#include <cstdint>

#ifndef MYCODE_FOTOSENSOR_H_
#define MYCODE_FOTOSENSOR_H_

namespace BFSSensorSeries {

class Fotosensor {
public:
	Fotosensor() = delete;
	Fotosensor(ADC_HandleTypeDef* p_hadc);
	void Update();
	void UpdateViaInterrupt();
	float Normalize();
private:
	ADC_HandleTypeDef* _p_hadc;
	uint32_t _raw_value = 0u;
};

} /* namespace BFSSensorSeries */

#endif /* MYCODE_FOTOSENSOR_H_ */
