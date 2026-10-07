/*
 * Fotosensor.cpp
 *
 *  Created on: Oct 7, 2026
 *      Author: yuzek
 */

#include "Fotosensor.h"

namespace BFSSensorSeries {

Fotosensor::Fotosensor(ADC_HandleTypeDef* p_hadc) : _p_hadc(p_hadc) {
}

void Fotosensor::Update(){
	HAL_ADC_Start(this->_p_hadc);
	HAL_ADC_PollForConversion(this->_p_hadc, 100);
	this->_raw_value = HAL_ADC_GetValue(this->_p_hadc);
	HAL_ADC_Stop(this->_p_hadc);
}

void Fotosensor::UpdateViaInterrupt(){
	this->_raw_value = HAL_ADC_GetValue(this->_p_hadc);
}

float Fotosensor::Normalize(){
	return static_cast<float>(this->_raw_value) / 4095.f;
}

} /* namespace BFSSensorSeries */
