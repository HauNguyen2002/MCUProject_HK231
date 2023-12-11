/*
 * manual_fsm.c
 *
 *  Created on: Dec 8, 2023
 *      Author: ASUS
 */

#include "manual_fsm.h"

enum MANLIGHTSTATE{M_INIT,M_HOLD,M_RG,M_RY,M_GR,M_YR};
enum MANLIGHTSTATE manlightstate=M_HOLD;

void manual_fsm(){
	switch(manlightstate){
	case M_INIT:
		manLightHandler();
		manlightstate=RG;
		break;
	case M_HOLD:
		if(mode==MANUAL_M) manlightstate=INIT;
		break;
	case M_RG:
		if(FLAG_BUT_CD==1){
			manButtonHandler(RY);
			setButtonCooldownTimer(100);
		}
		break;
	case M_RY:
		if(FLAG_BUT_CD==1){
			manButtonHandler(GR);
			setButtonCooldownTimer(100);
		}
		break;
	case M_GR:
		if(FLAG_BUT_CD==1){
			manButtonHandler(YR);
			setButtonCooldownTimer(100);
		}
		break;
	case M_YR:
		if(FLAG_BUT_CD==1){
			manButtonHandler(RG);
			setButtonCooldownTimer(100);
		}
		break;
	}
}

void manLightHandler(){
	switch(manlightstate){
	case M_INIT:
		HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, 1);
		HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 0);
		HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 0);
		HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 1);
		break;
	case M_HOLD:
		break;
	case M_RG:
		HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 1);
		HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 1);
		break;
	case M_RY:
		HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, 0);
		HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 1);
		HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 1);
		HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 0);
		break;
	case M_GR:
		HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, 1);
		HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 1);
		HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 1);
		break;
	case M_YR:
		HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 0);
		HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 0);
		HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 1);
		break;
	}
}
void manButtonHandler(enum MANLIGHTSTATE nextState){
	if(is_button_pressed(1)){
			flag_man_press=1;
	}
	else if (!is_button_pressed(1) && flag_man_press==1){
		flag_man_press=0;
		manlightstate=nextState;
		manLightHandler();
	}
	if(is_button_pressed(0)){
		flag_mode_press=1;
	}
	else if(!is_button_pressed(0) && flag_mode_press==1){
		flag_mode_press=0;
		mode=AUTO_M;
		manlightstate=HOLD;
	}
}


