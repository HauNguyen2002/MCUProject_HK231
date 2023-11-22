/*
 * auto_fsm.c
 *
 *  Created on: Nov 22, 2023
 *      Author: ASUS
 */

#include <fsm_auto.h>
#include "global.h"



enum AutoLight{INIT,HOLD,RG,RY,GR,YR};
enum AutoLight autolight=INIT;

uint8_t lightduration[3]={5,2,3};//initialize red: 5, yellow: 2, green: 3
uint8_t lightdisplay[2]={0,0};

uint8_t back_to_auto_flag=0;
void fsm_auto(){
	switch(autolight){
	case INIT:
		auto_light_control();
		lightdisplay[0]=lightduration[0]+1;
		lightdisplay[1]=lightduration[2]+1;
		back_to_auto_flag=0;
		autolight=RG;
	case HOLD:
		if(is_button_pressed(1) && back_to_auto_flag==1) autolight=INIT;
		break;
	case RG:
		if(BUTTON_COOLDOWN_FLAG==1){
			if(is_button_pressed(1)){
				autolight=HOLD;
				setButtonCooldown(100);
				break;
			}
		}
		if(COUNTDOWN_FLAG==1){
			if(lightdisplay[1]==0){
				lightdisplay[1]=lightduration[1]+1;
				autolight=RY;
				auto_light_control();
				break;
			}
			lightdisplay[0]--;
			lightdisplay[1]--;
			setAutolightTimer(1000);
		}
		break;
	case RY:
		if(BUTTON_COOLDOWN_FLAG==1){
			if(is_button_pressed(1)){
				autolight=HOLD;
				setButtonCooldown(100);
				break;
			}
		}
		if(COUNTDOWN_FLAG==1){
			if(lightdisplay[1]==0){
				lightdisplay[0]=lightduration[2]+1;
				lightdisplay[1]=lightduration[0]+1;
				autolight=GR;
				auto_light_control();
				break;
			}
			lightdisplay[0]--;
			lightdisplay[1]--;
			setAutolightTimer(1000);
		}
		break;
	case GR:
		if(BUTTON_COOLDOWN_FLAG==1){
			if(is_button_pressed(1)){
				autolight=HOLD;
				setButtonCooldown(100);
				break;
			}
		}
		if(COUNTDOWN_FLAG==1){
			if(lightdisplay[0]==0){
				lightdisplay[0]=lightduration[1]+1;
				autolight=YR;
				auto_light_control();
				break;
			}
			lightdisplay[0]--;
			lightdisplay[1]--;
			setAutolightTimer(1000);
		}
		break;
	case YR:
		if(BUTTON_COOLDOWN_FLAG==1){
			if(is_button_pressed(1)){
				autolight=HOLD;
				setButtonCooldown(100);
				break;
			}
		}
		if(COUNTDOWN_FLAG==1){
			if(lightdisplay[0]==0){
				lightdisplay[0]=lightduration[0]+1;
				lightdisplay[1]=lightduration[2]+1;
				autolight=RG;
				auto_light_control();
				break;
			}
			lightdisplay[0]--;
			lightdisplay[1]--;
			setAutolightTimer(1000);
		}
		break;
	}
}

void auto_light_control(){
	switch(autolight){
	case INIT:
		//Turn off all lights
		break;
	case HOLD:
		break;
	case RG:
		break;
	case RY:
		break;
	case GR:
		break;
	case YR:
		break;
	}
}

