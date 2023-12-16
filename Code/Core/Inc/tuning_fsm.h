/*
 * manual_fsm.h
 *
 *  Created on: Dec 4, 2023
 *      Author: ASUS
 */

#ifndef INC_TUNING_FSM_H_
#define INC_TUNING_FSM_H_

#include "global.h"

void tuning_fsm();
void tunLightHandler();
void tunButtonHandler(enum TUNINGLIGHT curLight,enum TUNINGLIGHT nextLight);
#endif /* INC_TUNING_FSM_H_ */
