/*
 * manual_fsm.h
 *
 *  Created on: Nov 22, 2023
 *      Author: ASUS
 */

#ifndef INC_FSM_MANUAL_H_
#define INC_FSM_MANUAL_H_

void fsm_manual();//adjusting light duration state machine
void manual_control_light();//state machine for blinking light, separate from fsm_manual for a cleaner state machine
void incDuration();//function for increasing additional duration ammount



#endif /* INC_FSM_MANUAL_H_ */
