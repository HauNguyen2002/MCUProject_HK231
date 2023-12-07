/*
 * auto_fsm.c
 *
 *  Created on: Dec 4, 2023
 *      Author: ASUS
 */
#include "auto_fsm.h"

enum AUTOLIGHT{INIT,HOLD,RG,RY,GR,YR};
enum AUTOLIGHT autolightstate=INIT;


uint8_t mode=AUTO_M;
void auto_fsm(){
	switch (autolightstate) {
	case INIT:
		adjAutoLight();
		lightdisplay[0]=lightDuration[0];
		lightdisplay[1]=lightDuration[2];
		autolightstate=RG;
		break;
	case HOLD:
		adjAutoLight();
		if(mode==AUTO_M){
			autolightstate=INIT;
		}
		break;
	case RG:
		if(FLAG_BUT_CD==1){
			FLAG_BUT_CD=0;
			autoButtonHandler();
		}
		if(FLAG_AUTO==1){
			FLAG_AUTO=0;
			if(lightdisplay[1]==0){
				lightdisplay[1]=lightDuration[1];
				autolightstate=RY;
			}
			adjAutoLight();
		}
		break;
	case RY:
		if(FLAG_BUT_CD==1){
			FLAG_BUT_CD=0;
			autoButtonHandler();
		}
		if(FLAG_AUTO==1){
			FLAG_AUTO=0;
			if(lightdisplay[1]==0){
				lightdisplay[0]=lightDuration[2];
				lightdisplay[1]=lightDuration[0];
				autolightstate=GR;
			}
			adjAutoLight();
		}
		break;
	case GR:
		if(FLAG_BUT_CD==1){
			FLAG_BUT_CD=0;
			autoButtonHandler();
		}
		if(FLAG_AUTO==1){
			FLAG_AUTO=0;
			if(lightdisplay[0]==0){
				lightdisplay[0]=lightDuration[1];
				autolightstate=YR;
			}
			adjAutoLight();
		}
		break;
	case YR:
		if(FLAG_BUT_CD==1){
			FLAG_BUT_CD=0;
			autoButtonHandler();
		}
		if(FLAG_AUTO==1){
			FLAG_AUTO=0;
			if(lightdisplay[0]==0){
				lightdisplay[0]=lightDuration[0];
				lightdisplay[1]=lightDuration[2];
				autolightstate=RG;
			}
			adjAutoLight();
		}
		break;
	}
}
void adjAutoLight(){
	switch (autolightstate) {
	case INIT:
//		HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 1);
//		HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 0);
//		HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, 0);
//		HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, 0);
//		HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, 0);
//		HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, 1);
		break;
	case HOLD:
		break;
	case RG:
//		HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, 0);
//		HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 0);
//		HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 1);
//		HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, 1);
		lightdisplay[0]--;
		lightdisplay[1]--;
		break;
	case RY:
//		HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, 0);
//		HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, 1);
		lightdisplay[0]--;
		lightdisplay[1]--;
		break;
	case GR:
//		HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 0);
//		HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, 0);
//		HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, 1);
//		HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 1);
		lightdisplay[0]--;
		lightdisplay[1]--;
		break;
	case YR:
//		HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, 0);
//		HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, 1);
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
		mode=MANUAL_M;
		autolightstate=HOLD;
	}
}



