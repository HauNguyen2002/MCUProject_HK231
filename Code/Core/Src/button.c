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

int Buttons[NO_OF_BUTTONS]={A0_Pin,A1_Pin,A2_Pin,A3_Pin};
int GPIO_Buttons[NO_OF_BUTTONS]={GPIOA,GPIOA,GPIOA,GPIOB};
static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer1 [ NO_OF_BUTTONS ];
static GPIO_PinState debounceButtonBuffer2 [ NO_OF_BUTTONS ];

static uint8_t flagForButtonPress1s [ NO_OF_BUTTONS ];

static uint16_t counterForButtonPress1s [ NO_OF_BUTTONS ];


void button_reading(void){
	for(char i=0;i< NO_OF_BUTTONS;i++){
		debounceButtonBuffer2[i]=debounceButtonBuffer1[i];
		debounceButtonBuffer1[i]= HAL_GPIO_ReadPin(GPIO_Buttons[i], Buttons[i]);
		if(debounceButtonBuffer1[i]==debounceButtonBuffer2[i]) buttonBuffer[i]= debounceButtonBuffer1[i];

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



