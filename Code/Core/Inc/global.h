/*
 * global.h
 *
 *  Created on: Dec 4, 2023
 *      Author: ASUS
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_
#include "main.h"
#include "button.h"

#define AUTO_M		0
#define	MANUAL_M	1

#define FLAG_7SEG	flag[0]
#define FLAG_AUTO	flag[1]
#define FLAG_BUT_CD	flag[2]
#define FLAG_MAN	flag[3]
#define FLAG_AUTO_INC	flag[4]


uint8_t flag[10];
uint8_t flag_mode_press,flag_inc_press, flag_set_press, flag_hold;
uint8_t mode;
uint8_t lightDuration[3];
uint8_t lightdisplay[2];

void* setAutoLightFlag();
void* set7SEGFlag();
void* setButtonCooldownFlag();
void* setManualLightFlag();
void* setAutoIncFlag();
#endif /* INC_GLOBAL_H_ */
