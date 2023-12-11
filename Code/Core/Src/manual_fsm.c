/*
 * manual_fsm.c
 *
 *  Created on: Dec 8, 2023
 *      Author: ASUS
 */

#include "manual_fsm.h"



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





