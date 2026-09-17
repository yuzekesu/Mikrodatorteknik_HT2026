/*
 * eventState.h
 *
 *  Created on: 15 Sept 2026
 *      Author: yuzek
 */

#ifndef INC_EVENTSTATE_H_
#define INC_EVENTSTATE_H_
enum event
 {
	 ev_none,
	 ev_button_push,
	 ev_state_timeout
 };

enum state
 {
	 s_init,
	 s_car_go,
	 s_pushed_wait,
	 s_car_is_stopping,
	 s_car_stop,
	 s_people_walk,
	 s_car_standing_by,
	 s_people_stop
	 /* others go here */
 };


#endif /* INC_EVENTSTATE_H_ */
