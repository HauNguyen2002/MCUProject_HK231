/*
 * main_fsm.c
 *
 *  Created on: Dec 10, 2023
 *      Author: Huy Minh
 */


#include "main_fsm.h"



void main_fsm(){
	switch (MODE) {
		case AUTO:
			auto_fsm();
			CheckButtonMode(); // có j ông thêm hộ tui cái chuyển cách MODE vs setAutoModeReturnTimerDefault() cho Btn trong nút nha
			break;
		case MANUAL:
			manual_fsm();
			CheckButtonMode();
			break;

		case TUNING:
			tuning_fsm();
			CheckButtonMode();

			break;
		case PEDESTRIAN: //Only in AUTO MODE
			pedestrian_fsm();
			CheckButtonMode();
			break;
		default:
			break;
	}
}
