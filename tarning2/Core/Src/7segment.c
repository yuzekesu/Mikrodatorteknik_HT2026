/*
 * 7segment.c
 *
 *  Created on: 9 Sept 2026
 *      Author: yuzek
 */
#include "7segment.h"
#include "main.h"
const uint16_t sseg[10] = {
    0x05F, // 0
    0x006, // 1
    0x09B, // 2
    0x08F, // 3
    0x0C6, // 4
    0x0CD, // 5
    0x0DD, // 6
    0x007, // 7
    0x0DF, // 8
    0x0CF  // 9
};
const uint16_t sseg_err = 0x1AC;

void seven_segment_display(uint8_t num){
	GPIOC->ODR = num > 6 || num < 1 ? sseg_err : sseg[num];
}


