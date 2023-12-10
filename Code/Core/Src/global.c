/*
 * global.c
 *
 *  Created on: Dec 4, 2023
 *      Author: ASUS
 */

#include "global.h"

uint8_t flag_mode_press=0;
uint8_t flag_inc_press=0;
uint8_t flag_set_press=0;
uint8_t flag_hold=0;

uint8_t lightDuration[3]={5,2,3};
uint8_t lightdisplay[2]={0,0};
uint8_t buzzstate=0;


enum AUTOLIGHT autolightstate=INIT;
enum MANLIGHTSTATE manlightstate=M_HOLD;
enum TUNINGLIGHT tunlightstate=T_HOLD;
enum PEDESTRIANSTATE pedstate=OFF;

