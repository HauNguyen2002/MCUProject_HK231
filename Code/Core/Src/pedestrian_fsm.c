/*
 * pedestrian_fsm.c
 *
 *  Created on: Dec 8, 2023
 *      Author: ASUS
 */

#include "pedestrian_fsm.h"






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


