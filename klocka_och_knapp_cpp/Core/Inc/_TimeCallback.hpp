/*
 * _TimeCallback.hpp
 *
 *  Created on: 29 Sept 2026
 *      Author: yuzek
 */

#include <Timer.hpp>
#include <vector> // just want to test heap allocation.
#include <main.h>

#ifndef INC__TIMECALLBACK_HPP_
#define INC__TIMECALLBACK_HPP_

class TimeCallback {
public:
	static void Initialize(); // test heap only.
	static Timer& GetTimer();
	static void SetTimHandle(TIM_HandleTypeDef*, std::size_t number_tag);
	static void HandleTIM1(TIM_HandleTypeDef* );
private:
	// inline static std::vector<TIM_HandleTypeDef*> _vector; // hehe std17 needed.
	static std::vector<TIM_HandleTypeDef*> _vector;
};

#endif /* INC__TIMECALLBACK_HPP_ */
