/*
 * tarning.h
 *
 *  Created on: 9 Sept 2026
 *      Author: yuzek
 */
#include <stdbool.h>
#include <stdint.h>

#ifndef INC_TARNING_H_
#define INC_TARNING_H_

uint8_t tarning_history();
void tarning_idle();
void _tarning_set(uint8_t number, bool state);
void tarning_roll();

#endif /* INC_TARNING_H_ */
