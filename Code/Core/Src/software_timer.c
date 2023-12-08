/*
 * software_timer.c
 *
 *  Created on: Dec 8, 2023
 *      Author: ASUS
 */


#include "software_timer.h"

#define MAX_SOFTWARE_TIMER		10
#define TIMER_CYCLE				1


uint8_t flag[MAX_SOFTWARE_TIMER];
uint32_t counter[MAX_SOFTWARE_TIMER];

void setAutoLightTimer(int duration){
	flag[0]=0;
	counter[0]=duration/TIMER_CYCLE;
}

void setTuningLightTimer(int duration){
	flag[1]=0;
	counter[1]=duration/TIMER_CYCLE;
}

void setButtonCooldownTimer(int duration){
	flag[2]=0;
	counter[2]=duration/TIMER_CYCLE;
}

void setAutoIncTimer(int duration){
	flag[3]=0;
	counter[3]=duration/TIMER_CYCLE;
}
void setBuzzerStateTimer(int duration){
	flag[4]=0;
	counter[4]=duration/TIMER_CYCLE;
}

void timerRun(){
	for(int i=0;i<MAX_SOFTWARE_TIMER;i++){
		if(counter[i]>0) counter[i]--;
		if(counter[i]==0) flag[i]=1;
	}
}

