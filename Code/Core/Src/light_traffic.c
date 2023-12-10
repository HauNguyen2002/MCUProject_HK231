/*
 * light_traffic.c
 *
 *  Created on: Dec 10, 2023
 *      Author: Huy Minh
 */


#include "light_traffic.h"

// for mode lights


//turn off

void turnOffCurrentLight(){
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, 0);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 0);
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 0);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 0);
}



// AUTO

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


// MANUAL


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


//Tuning


void adjTuningLight(){
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



//Pedestrian


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
