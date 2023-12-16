
/*
 * manual_fsm.c
 *
 *  Created on: Dec 4, 2023
 *      Author: ASUS
 */
enum TUNINGLIGHT{T_RED,T_YELLOW,T_GREEN,T_INIT,T_HOLD};
enum TUNINGLIGHT tunlightstate=T_HOLD;

#include <tuning_fsm.h>
UART_HandleTypeDef huart2;
char message[20];
uint8_t temp_lightdisplay=0;
void tuning_fsm(){
	switch(tunlightstate){
	case T_INIT:
		tunLightHandler();
		tunlightstate=T_RED;
		temp_lightdisplay=lightDuration[0];
		break;
	case T_HOLD:
		if(mode==TUNING_M){
			tunlightstate=T_INIT;
		}
		break;
	case T_RED:
		if(FLAG_TUN==1){
//			FLAG_MAN=0;
			tunLightHandler();
			setTuningLightTimer(250);
		}
		if(FLAG_BUT_CD==1){
//			FLAG_BUT_CD=0;
			tunButtonHandler(0, T_YELLOW);
			setButtonCooldownTimer(100);
		}
		break;
	case T_YELLOW:
		if(FLAG_TUN==1){
//			FLAG_MAN=0;
			tunLightHandler();
			setTuningLightTimer(250);
		}
		if(FLAG_BUT_CD==1){
//			FLAG_BUT_CD=0;
			tunButtonHandler(1, T_GREEN);
			setButtonCooldownTimer(100);
		}
		break;
	case T_GREEN:
		if(FLAG_TUN==1){
//			FLAG_MAN=0;
			tunLightHandler();
			setTuningLightTimer(250);
		}
		if(FLAG_BUT_CD==1){
//			FLAG_BUT_CD=0;
			tunButtonHandler(2, T_HOLD);
			setButtonCooldownTimer(100);
		}
		break;
	}
}

void tunLightHandler(){
	switch(tunlightstate){
	case T_INIT:
		HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, 0);
		HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 0);
		HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 0);
		HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 0);
		break;
	case T_HOLD:
		break;
	case T_RED:
		HAL_GPIO_TogglePin(D2_GPIO_Port, D2_Pin);
		HAL_GPIO_TogglePin(D4_GPIO_Port, D4_Pin);
		break;
	case T_YELLOW:
		HAL_GPIO_TogglePin(D2_GPIO_Port, D2_Pin);
		HAL_GPIO_TogglePin(D3_GPIO_Port, D3_Pin);
		HAL_GPIO_TogglePin(D4_GPIO_Port, D4_Pin);
		HAL_GPIO_TogglePin(D5_GPIO_Port, D5_Pin);
		break;
	case T_GREEN:
		HAL_GPIO_TogglePin(D3_GPIO_Port, D3_Pin);
		HAL_GPIO_TogglePin(D5_GPIO_Port, D5_Pin);
		break;
	}
}

void turnOffCurrentLight(){
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, 0);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 0);
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 0);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 0);
}

void tunButtonHandler(enum TUNINGLIGHT curLight,enum TUNINGLIGHT nextLight){
	if(is_button_pressed(0)){
		flag_mode_press=1;
	}
	else if(!is_button_pressed(0) && flag_mode_press==1){
		flag_mode_press=0;
		if(nextLight==T_HOLD) mode=AUTO_M;
		else temp_lightdisplay=lightDuration[nextLight];
		tunlightstate=nextLight;
		turnOffCurrentLight();
	}

	if(is_button_pressed(1)){
		flag_inc_press=1;
		if(is_button_pressed_1s(1)){
			flag_hold=1;
			if(FLAG_AUTO_INC==1){
				temp_lightdisplay++;
				if(temp_lightdisplay>99) temp_lightdisplay=0;
				setAutoIncTimer(500);
			}
		}
	}
	else if (!is_button_pressed(1) && flag_inc_press==1){
		flag_inc_press=0;
		if(flag_hold==0){
			temp_lightdisplay++;
			if(temp_lightdisplay>99) temp_lightdisplay=0;
		}
		else flag_hold=0;
	}

	if(is_button_pressed(2)){
		flag_set_press=1;
	}
	else if (!is_button_pressed(2) && flag_inc_press==1){
		flag_set_press=0;
		lightDuration[curLight]=temp_lightdisplay+1;
	}
}

