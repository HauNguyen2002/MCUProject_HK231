/*
 * auto_fsm.c
 *
 *  Created on: Dec 4, 2023
 *      Author: ASUS
 */
#include "auto_fsm.h"




uint8_t mode=AUTO_M;
void auto_fsm(){
	switch (autolightstate) {
	case INIT:
		if(FLAG_AUTO==1){
			autoLightHandler();
			lightdisplay[0]=lightDuration[0];
			lightdisplay[1]=lightDuration[2];
			autolightstate=RG;
			break;
		}
	case HOLD:
		if(mode==AUTO_M){
			autolightstate=INIT;
		}
		break;
	case RG:
		if(FLAG_BUT_CD==1){
//			FLAG_BUT_CD=0;
			autoButtonHandler();
			setButtonCooldownTimer(100);
		}
		if(FLAG_AUTO==1){
//			FLAG_AUTO=0;
			if(lightdisplay[1]==0){
				lightdisplay[1]=lightDuration[1];
				autolightstate=RY;
			}
			autoLightHandler();
			setAutoLightTimer(1000);
		}
		break;
	case RY:
		if(FLAG_BUT_CD==1){
//			FLAG_BUT_CD=0;
			autoButtonHandler();
			setButtonCooldownTimer(100);
		}
		if(FLAG_AUTO==1){
//			FLAG_AUTO=0;
			if(lightdisplay[1]==0){
				lightdisplay[0]=lightDuration[2];
				lightdisplay[1]=lightDuration[0];
				autolightstate=GR;
			}
			autoLightHandler();
			setAutoLightTimer(1000);
		}
		break;
	case GR:
		if(FLAG_BUT_CD==1){
//			FLAG_BUT_CD=0;
			autoButtonHandler();
			setButtonCooldownTimer(100);
		}
		if(FLAG_AUTO==1){
//			FLAG_AUTO=0;
			if(lightdisplay[0]==0){
				lightdisplay[0]=lightDuration[1];
				autolightstate=YR;
			}
			autoLightHandler();
			setAutoLightTimer(1000);
		}
		break;
	case YR:
		if(FLAG_BUT_CD==1){
//			FLAG_BUT_CD=0;
			autoButtonHandler();
			setButtonCooldownTimer(100);
		}
		if(FLAG_AUTO==1){
//			FLAG_AUTO=0;
			if(lightdisplay[0]==0){
				lightdisplay[0]=lightDuration[0];
				lightdisplay[1]=lightDuration[2];
				autolightstate=RG;
			}
			autoLightHandler();
			setAutoLightTimer(1000);
		}
		break;
	}
}
void autoLightHandler(){
	switch (autolightstate) {
	case INIT:
		HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, 1);
		HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 0);
		HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 0);
		HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 1);
		break;
	case HOLD:
		break;
	case RG:
		HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, 1);
		HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 0);
		HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 0);
		HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 1);
		lightdisplay[0]--;
		lightdisplay[1]--;
		break;
	case RY:
		HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 1);
		HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 1);
		lightdisplay[0]--;
		lightdisplay[1]--;
		break;
	case GR:
		HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, 0);
		HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 1);
		HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 1);
		HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 0);
		lightdisplay[0]--;
		lightdisplay[1]--;
		break;
	case YR:
		HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, 1);
		HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 1);
		lightdisplay[0]--;
		lightdisplay[1]--;
		break;
	}
}
void autoButtonHandler(){
	if(is_button_pressed(0)){
		flag_mode_press=1;
	}
	else if(!is_button_pressed(0) && flag_mode_press==1){
		flag_mode_press=0;
		mode=TUNING_M;
		autolightstate=HOLD;
	}
	if(is_button_pressed(1)){
		flag_man_press=1;
	}
	else if (!is_button_pressed(1) && flag_man_press==1){
		flag_man_press=0;
		mode=MANUAL_M;
		autolightstate=HOLD;
	}
}



