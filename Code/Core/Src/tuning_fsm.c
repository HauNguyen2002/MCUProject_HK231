
/*
 * manual_fsm.c
 *
 *  Created on: Dec 4, 2023
 *      Author: ASUS
 */
enum MANUALLIGHT{RED,YELLOW,GREEN,INIT,HOLD};
enum MANUALLIGHT manlightstate=HOLD;

#include <tuning_fsm.h>

uint8_t temp_lightdisplay=0;
void tuning_fsm(){
	switch(manlightstate){
	case INIT:
		adjTuningLight();
		manlightstate=RED;
		temp_lightdisplay=lightDuration[0];
		break;
	case HOLD:
		if(mode==MANUAL_M){
			manlightstate=INIT;
		}
		break;
	case RED:
		if(FLAG_BUT_CD==1){
			FLAG_BUT_CD=0;
			tunButtonHandler(0, YELLOW);
		}
		if(FLAG_MAN==1){
			FLAG_MAN=0;
			adjTuningLight();
		}
		break;
	case YELLOW:
		if(FLAG_BUT_CD==1){
			FLAG_BUT_CD=0;
			tunButtonHandler(1, GREEN);
		}
		if(FLAG_MAN==1){
			FLAG_MAN=0;
			adjTuningLight();
		}
		break;
	case GREEN:
		if(FLAG_BUT_CD==1){
			FLAG_BUT_CD=0;
			tunButtonHandler(2, HOLD);
		}
		if(FLAG_MAN==1){
			FLAG_MAN=0;
			adjTuningLight();
		}
		break;
	}
}

void adjTuningLight(){
	switch(manlightstate){
	case INIT:
//		HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 0);
//		HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 0);
//		HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, 0);
//		HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, 0);
//		HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, 0);
//		HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, 0);
		break;
	case HOLD:
		break;
	case RED:
//		HAL_GPIO_TogglePin(RED1_GPIO_Port, RED1_Pin);
//		HAL_GPIO_TogglePin(RED2_GPIO_Port, RED2_Pin);
		break;
	case YELLOW:
//		HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 0);
//		HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 0);
//		HAL_GPIO_TogglePin(YELLOW1_GPIO_Port, YELLOW1_Pin);
//		HAL_GPIO_TogglePin(YELLOW2_GPIO_Port, YELLOW2_Pin);
		break;
	case GREEN:
//		HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, 0);
//		HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, 0);
//		HAL_GPIO_TogglePin(GREEN1_GPIO_Port, GREEN1_Pin);
//		HAL_GPIO_TogglePin(GREEN2_GPIO_Port, GREEN2_Pin);
		break;
	}
}

void tunButtonHandler(enum MANUALLIGHT curLight,enum MANUALLIGHT nextLight){
	if(is_button_pressed(0)){
		flag_mode_press=1;
	}
	else if(!is_button_pressed(0) && flag_mode_press==1){
		flag_mode_press=0;
		if(nextLight==HOLD) mode=AUTO_M;
		else temp_lightdisplay=lightDuration[nextLight];
		manlightstate=nextLight;
	}

	if(is_button_pressed(1)){
		flag_inc_press=1;
		if(is_button_pressed_1s(1)){
			flag_hold=1;
			if(FLAG_AUTO_INC==1){
				FLAG_AUTO_INC=0;
				HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
				temp_lightdisplay++;
			}
		}
	}
	else if (!is_button_pressed(1) && flag_inc_press==1){
		flag_inc_press=0;
		(flag_hold==0)?(temp_lightdisplay++):(flag_hold=0);
	}

	if(is_button_pressed(2)){
		flag_set_press=1;
	}
	else if (!is_button_pressed(2) && flag_inc_press==1){
		flag_set_press=0;
		lightDuration[curLight]=temp_lightdisplay+1;
	}
}

