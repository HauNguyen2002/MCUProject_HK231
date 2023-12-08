/*
 * pedestrian_fsm.c
 *
 *  Created on: Dec 8, 2023
 *      Author: ASUS
 */

#include "pedestrian_fsm.h"



TIM_HandleTypeDef htim3;
uint8_t buzzstate=0;
void pedestrian_fsm(){
	switch(pedstate){
	case OFF:
		if(FLAG_BUT_CD==1){
			pedButtonHandler(ON);
			setButtonCooldownTimer(100);
		}
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);
		HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 0);
		HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, 0);
		break;
	case ON:
		if(FLAG_BUT_CD==1){
			pedButtonHandler(OFF);
			setButtonCooldownTimer(100);
		}
		pedLightHandler();
		pedBuzzHandler();
		break;
	}
}
void pedLightHandler(){
	switch(autolightstate){
	case INIT:
		HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 0);
		HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, 1);
		break;
	case HOLD:
		HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 0);
		HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, 0);
		break;
	case RG:
		HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 0);
		HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, 1);
		break;
	case RY:
		HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 0);
		HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, 1);
		break;
	case GR:
		HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 1);
		HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, 0);
		break;
	case YR:
		HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 1);
		HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, 0);
		break;
	}
}
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
void pedButtonHandler(enum PEDESTRIANSTATE nextState){
	if(is_button_pressed(3)){
		flag_ped_press=1;
	}
	else if(!is_button_pressed(3) && flag_ped_press==1){
		flag_ped_press=0;
		pedstate=nextState;
#ifdef CHANGE_AUTOLIGHT
		if(nextState==ON){
			autolightstate=INIT;
			FLAG_AUTO=1;
		}
#endif
	}
}


