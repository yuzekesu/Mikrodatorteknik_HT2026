/*
 * tarning.h
 *
 *  Created on: 5 Sept 2026
 *      Author: yuzek
 */

#include <stdbool.h>
#ifndef INC_TARNING_H_
#define INC_TARNING_H_
#define MAX_TARNING_HISTORY_TABLE 6
uint8_t _tarning_history = 0;

void _tarning_set(uint8_t number);
void tarning_roll();

#endif /* INC_TARNING_H_ */
