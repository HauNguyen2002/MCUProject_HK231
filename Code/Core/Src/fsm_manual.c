/*
 * manual.fsm.c
 *
 *  Created on: Nov 22, 2023
 *      Author: ASUS
 */
#include "fsm_manual.h"
#include "global.h"


enum ManualLight{INIT,HOLD,RED,YELLOW,GREEN};
enum ManualLight manlight=HOLD;

uint8_t addDuration=0;
uint8_t have_pressed_mode=0;
uint8_t have_pressed_inc=0;
void fsm_manual(){
	switch(manlight){
	case INIT:
		manual_control_light();
		break;
	case HOLD:
		if(is_button_pressed(1) && back_to_auto_flag==0){
			manlight=INIT;
		}
		break;
	case RED:
		if(BUTTON_COOLDOWN_FLAG==1){
			if(is_button_pressed(1)){
				manlight=YELLOW;
				addDuration=0;
				setButtonCooldown(100);
			}
			incDuration();
			if(is_button_pressed(3)){
				lightduration[0]+=addDuration;
				addDuration=0;
				setButtonCooldown(100);
			}

		}
		if(BLINK_LIGHT_FLAG==1){
			manual_control_light();
			setManualLightBlink(250);
		}
		break;
	case YELLOW:
		if(BUTTON_COOLDOWN_FLAG==1){
			if(is_button_pressed(1)){
				manlight=GREEN;
				addDuration=0;
				setButtonCooldown(100);
			}
			incDuration();
			if(is_button_pressed(3)){
				lightduration[1]+=addDuration;
				addDuration=0;
				setButtonCooldown(100);
			}
		}
		break;
	case GREEN:
		if(BUTTON_COOLDOWN_FLAG==1){
			if(is_button_pressed(1)){
				manlight=HOLD;
				addDuration=0;
				setButtonCooldown(100);
				back_to_auto_flag=1;
			}
			if(is_button_pressed(3)){
				lightduration[2]+=addDuration;
				addDuration=0;
				setButtonCooldown(100);
			}
			incDuration();
		}
		break;
	}
}
void manual_control_light(){
	switch(manlight){
	case INIT:
		break;
	case HOLD:
		break;
	case RED:
		break;
	case YELLOW:
		break;
	case GREEN:
		break;
	}
}

void incDuration(){
	if(is_button_pressed(2)){
		have_pressed_inc=1;
	}
	if(!is_button_pressed(2)&& have_pressed_inc==1){
		have_pressed_inc=0;
		addDuration++;
		setButtonCooldown(100);
	}
	if(AUTO_INCREASE_FLAG==1){
		if(is_button_pressed_1s(2)){
			addDuration++;
			setAutoIncreaseTime(500);
		}
	}
}


