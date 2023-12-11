/*
 * buzzer.c
 *
 *  Created on: Dec 11, 2023
 *      Author: Huy Minh
 */


#include "buzzer.h"

void buzzerChangeState(){
	switch(buzzstate){
	case 0:
		if(FLAG_BUZZER==1){
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,10);
			setBuzzerStateTimer(100);
			buzzstate=1;
		}
		break;
	case 1:
		if(FLAG_BUZZER==1){
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);
			setBuzzerStateTimer(100);
			buzzstate=0;
		}
		break;
	}
}



void pedBuzzHandler(){
	switch(autolightstate){
	case INIT:
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);
		break;
	case HOLD:
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);
		break;
	case RG:
		if(lightdisplay[1]<5)
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,10);
		break;
	case RY:
		buzzerChangeState();
		break;
	case GR:
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);
		break;
	case YR:
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);
		break;
	}
}

