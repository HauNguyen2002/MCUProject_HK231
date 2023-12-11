/*
 * global.h
 *
 *  Created on: Dec 4, 2023
 *      Author: ASUS
 */

/* D3=RED1
 * D4=YELLOW1
 * D5=GREEN1
 *
 * D6=P_RED
 * D7=P_GREEN
 *
 * D8=RED2
 * D9=YELLOW2
 * D10=GREEN2
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_
#include "main.h"
#include "button.h"
#include "software_timer.h"
#include "buzzer.h"
#include "light_traffic.h"






#define AUTO_M		0
#define	TUNING_M	1
#define MANUAL_M	2

#define FLAG_AUTO		flag[0]
#define FLAG_TUN		flag[1]
#define FLAG_BUT_CD		flag[2]
#define FLAG_AUTO_INC	flag[3]
#define FLAG_BUZZER		flag[4]

#define CHANGE_AUTOLIGHT

//uint8_t flag[10];
uint8_t flag_mode_press,flag_inc_press, flag_set_press, flag_hold,flag_man_press,flag_ped_press;
uint8_t mode;
uint8_t lightDuration[3];
uint8_t lightdisplay[2];
uint8_t buzzstate;


enum AUTOLIGHT{INIT,HOLD,RG,RY,GR,YR};
enum AUTOLIGHT autolightstate;

enum TUNINGLIGHT{T_RED,T_YELLOW,T_GREEN,T_INIT,T_HOLD};
enum TUNINGLIGHT tunlightstate;

enum MANLIGHTSTATE{M_INIT,M_HOLD,M_RG,M_RY,M_GR,M_YR};
enum MANLIGHTSTATE manlightstate;

enum PEDESTRIANSTATE {OFF,ON};
enum PEDESTRIANSTATE pedstate;

enum MAIN_FSM {AUTO	,MANUAL, TUNING, PEDESTRIAN};
enum MAIN_FSM MODE;


TIM_HandleTypeDef htim3;



//void* setAutoLightFlag();
//void* set7SEGFlag();
//void* setButtonCooldownFlag();
//void* setManualLightFlag();
//void* setAutoIncFlag();
#endif /* INC_GLOBAL_H_ */
