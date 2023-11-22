/*
 * global.h
 *
 *  Created on: Nov 22, 2023
 *      Author: ASUS
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "button.h"
#include "software_timer.h"
#include "main.h"

#define COUNTDOWN_FLAG			flag[0]
#define BUTTON_COOLDOWN_FLAG	flag[1]
#define BLINK_LIGHT_FLAG		flag[2]
#define AUTO_INCREASE_FLAG		flag[3]

uint8_t back_to_auto_flag;//1: back to auto mode, 0: stay in manual mode

uint8_t lightduration[3];// light durations: red, yellow, green respectively
uint8_t lightdisplay[2];// get value from lightduration[] to display time



#endif /* INC_GLOBAL_H_ */
