/*
 * eventQueue.h
 *
 *  Created on: 16 Sept 2026
 *      Author: yuzek
 */
#include "eventState.h"
#ifndef INC_EVENTQUEUE_H_
#define INC_EVENTQUEUE_H_

void evq_push_back(enum event e);
enum event evq_pop_front();

#endif /* INC_EVENTQUEUE_H_ */
