/*
 * trafikljus.h
 *
 *  Created on: 15 Sept 2026
 *      Author: yuzek
 */
#include "main.h"
#include <stdint.h>
#include "eventState.h"

#ifndef INC_TRAFIKLJUS_H_
#define INC_TRAFIKLJUS_H_

void set_traffic_lights(enum state s);
void set_push_button_light(int isOn, GPIO_TypeDef* port, uint16_t pin);


#endif /* INC_TRAFIKLJUS_H_ */
