/*
 * eventQueue.c
 *
 *  Created on: 16 Sept 2026
 *      Author: yuzek
 */
#include "eventQueue.h"

#define EVQ_SIZE 10
enum event evq[ EVQ_SIZE ];
int evq_count = 0;
int evq_front_ix = 0;
int evq_rear_ix = 0;

void evq_push_back(enum event e) {
	if (evq_front_ix == evq_rear_ix + 1) return;
	else if (evq_front_ix == 0 && evq_rear_ix == EVQ_SIZE - 1) return;
	evq[evq_front_ix] = e;
	if (evq_rear_ix == EVQ_SIZE - 1) evq_rear_ix = 0;
	else ++evq_rear_ix;
}
enum event evq_pop_front() {
	if (evq_front_ix == evq_rear_ix) return ev_none;
	enum event result = evq[evq_front_ix];
	if (evq_front_ix == EVQ_SIZE - 1) evq_front_ix = 0;
	else ++evq_front_ix;
	return result;
}

