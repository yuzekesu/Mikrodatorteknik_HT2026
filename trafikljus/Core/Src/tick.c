/*
 * tick.c
 *
 *  Created on: 23 Sept 2026
 *      Author: yuzek
 */
#include <stdint.h>
#include "main.h"
#include "eventState.h"
#include "eventQueue.h"

uint32_t countDown = 0;

uint32_t* tick_get_pCountDown() {
	return &countDown;
}

void tick_update() {
	if (countDown == 0) return;
	--countDown;
	if (countDown == 0) evq_push_back(ev_state_timeout);
}
