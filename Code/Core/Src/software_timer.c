/*
 * software_timer.c
 *
 *  Created on: Nov 15, 2023
 *      Author: ASUS
 */

#include "software_timer.h"
#include "button.h"

#define MAX_SOFTWARE_TIMER	10
#define TIMER_CYCLE	1
// timer flags, maximum is 10 (adjustable), add more setTimer functions,
// DO NOT add more timerRun functions
uint8_t flag[MAX_SOFTWARE_TIMER];
uint8_t counter[MAX_SOFTWARE_TIMER];

//Flag and counter indexes already in use: 0->3 (See details in global.h)
void setAutolightTimer(uint8_t duration){
	flag[0]=0;
	counter[0]=duration/TIMER_CYCLE;
}
void setButtonCooldown(uint8_t duration){
	flag[1]=0;
	counter[1]=duration/TIMER_CYCLE;
}
void setManualLightBlink(uint8_t duration){
	flag[2]=0;
	counter[2]=duration/TIMER_CYCLE;
}
void setAutoIncreaseTime(uint8_t duration){
	flag[3]=0;
	counter[3]=duration/TIMER_CYCLE;
}
void timerRun(){
	for(int i=0;i<MAX_SOFTWARE_TIMER;i++){
		if(counter[i]>0) counter[i]--;
		if(counter[i]==0) flag[i]=1;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	timerRun();
	button_reading();
}

