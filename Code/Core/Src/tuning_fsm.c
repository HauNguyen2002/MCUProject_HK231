
/*
 * manual_fsm.c
 *
 *  Created on: Dec 4, 2023
 *      Author: ASUS
 */


#include <tuning_fsm.h>

uint8_t temp_lightdisplay=0;
void tuning_fsm(){
	switch(tunlightstate){
	case T_INIT:
		adjTuningLight();
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
			adjTuningLight();
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
			adjTuningLight();
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
			adjTuningLight();
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




