/*
 * button.h
 *
 *  Created on: 25 Sept 2026
 *      Author: yuzek
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

uint16_t button_get_registered_press_count();
uint16_t button_get_debounce_count();
int button_is_pressing();
void button_initialize();

#endif /* INC_BUTTON_H_ */
