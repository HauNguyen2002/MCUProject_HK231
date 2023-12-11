/*
 * button.c
 *
 *  Created on: Nov 15, 2023
 *      Author: ASUS
 */
#include "main.h"


#define NO_OF_BUTTONS		4
#define DURATION_FOR_AUTO_INCREASING	1000
#define BUTTON_IS_PRESSED				GPIO_PIN_RESET
#define BUTTON_IS_RELEASED				GPIO_PIN_SET

int Buttons[NO_OF_BUTTONS]={A1_Pin,A2_Pin,A3_Pin,A0_Pin};
int GPIO_Buttons[NO_OF_BUTTONS]={A1_GPIO_Port,A2_GPIO_Port,A3_GPIO_Port,A0_GPIO_Port};
static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer1 [ NO_OF_BUTTONS ];
static GPIO_PinState debounceButtonBuffer2 [ NO_OF_BUTTONS ];
static GPIO_PinState debounceButtonBuffer3 [ NO_OF_BUTTONS ];

static uint8_t flagForButtonPress1s [ NO_OF_BUTTONS ];

static uint16_t counterForButtonPress1s [ NO_OF_BUTTONS ];


void button_reading(void){
	for(char i=0;i< NO_OF_BUTTONS;i++){
		debounceButtonBuffer3[i]=debounceButtonBuffer2[i];
		debounceButtonBuffer2[i]=debounceButtonBuffer1[i];
		debounceButtonBuffer1[i]= HAL_GPIO_ReadPin(GPIO_Buttons[i], Buttons[i]);
		if(debounceButtonBuffer2[i]==debounceButtonBuffer3[i] && debounceButtonBuffer1[i]==debounceButtonBuffer2[i])
			buttonBuffer[i]= debounceButtonBuffer1[i];

		if(buttonBuffer[i]==BUTTON_IS_PRESSED){
			if(counterForButtonPress1s[i]<DURATION_FOR_AUTO_INCREASING){
				counterForButtonPress1s[i]++;
				}
			else{
					flagForButtonPress1s[i]=1;
				}
		}
		else{
			counterForButtonPress1s[i]=0;
			flagForButtonPress1s[i]=0;
		}
	}
}

unsigned char is_button_pressed(uint8_t index){
	if(index>=NO_OF_BUTTONS) return 0;
	return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}

unsigned char is_button_pressed_1s(unsigned char index){
	if(index>= NO_OF_BUTTONS) return 0xff;
	return (flagForButtonPress1s[index] == 1);
}




void manButtonHandler(enum MANLIGHTSTATE nextState){
	if(is_button_pressed(1)){
			flag_man_press=1;
	}
	else if (!is_button_pressed(1) && flag_man_press==1){
		flag_man_press=0;
		manlightstate=nextState;
		manLightHandler();
	}
	if(is_button_pressed(0)){
		flag_mode_press=1;
	}
	else if(!is_button_pressed(0) && flag_mode_press==1){
		flag_mode_press=0;
		mode=AUTO_M;
		manlightstate=HOLD;
	}
}


void autoButtonHandler(){
	if(is_button_pressed(0)){
		flag_mode_press=1;
	}
	else if(!is_button_pressed(0) && flag_mode_press==1){
		flag_mode_press=0;
		mode=TUNING_M;
		autolightstate=HOLD;
	}
	if(is_button_pressed(1)){
		flag_man_press=1;
	}
	else if (!is_button_pressed(1) && flag_man_press==1){
		flag_man_press=0;
		mode=MANUAL_M;
		autolightstate=HOLD;
	}
}


void pedButtonHandler(enum PEDESTRIANSTATE nextState){
	if(is_button_pressed(3)){
		flag_ped_press=1;
	}
	else if(!is_button_pressed(3) && flag_ped_press==1){
		flag_ped_press=0;
		pedstate=nextState;
#ifdef CHANGE_AUTOLIGHT
		if(nextState==ON){
			autolightstate=INIT;
			FLAG_AUTO=1;
		}
#endif
	}
}


void tunButtonHandler(enum TUNINGLIGHT curLight,enum TUNINGLIGHT nextLight){
	if(is_button_pressed(0)){
		flag_mode_press=1;
	}
	else if(!is_button_pressed(0) && flag_mode_press==1){
		flag_mode_press=0;
		if(nextLight==T_HOLD) mode=AUTO_M;
		else temp_lightdisplay=lightDuration[nextLight];
		tunlightstate=nextLight;
		turnOffCurrentLight();
	}

	if(is_button_pressed(1)){
		flag_inc_press=1;
		if(is_button_pressed_1s(1)){
			flag_hold=1;
			if(FLAG_AUTO_INC==1){
//				FLAG_AUTO_INC=0;
				temp_lightdisplay++;
				setAutoIncTimer(500);
			}
		}
	}
	else if (!is_button_pressed(1) && flag_inc_press==1){
		flag_inc_press=0;
		(flag_hold==0)?(temp_lightdisplay++):(flag_hold=0);
	}

	if(is_button_pressed(2)){
		flag_set_press=1;
	}
	else if (!is_button_pressed(2) && flag_inc_press==1){
		flag_set_press=0;
		lightDuration[curLight]=temp_lightdisplay+1;
	}
}


void CheckButtonMode(){
	manButtonHandler(enum MANLIGHTSTATE nextState);
	autoButtonHandler();
	pedButtonHandler(enum PEDESTRIANSTATE nextState);
	tunButtonHandler(enum TUNINGLIGHT curLight,enum TUNINGLIGHT nextLight);
}








