/*
 * software_timer.c
 *
 *  Created on: Nov 15, 2023
 *      Author: ASUS
 */

#include "software_timer.h"

#define MAX_SOFTWARE_TIMER	10
#define TIMER_CYCLE	1

uint8_t flag[MAX_SOFTWARE_TIMER];
uint8_t counter[MAX_SOFTWARE_TIMER];

void timerRun(){
	for(int i=0;i<MAX_SOFTWARE_TIMER;i++){
		if(counter[i]>0) counter[i]--;
		if(counter[i]==0) flag[i]=1;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	timerRun();
}

