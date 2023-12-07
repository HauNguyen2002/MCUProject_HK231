/*
 * Scheduler.h
 *
 *  Created on: Oct 9, 2023
 *      Author: ASUS
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "main.h"
#include "stdio.h"

#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0


typedef struct tNode{
	uint32_t waitTime;
	uint32_t period;
	uint32_t delay;
	uint32_t tId;
	void(*ptask)(void);
	struct tNode* nextT;
	struct tNode* prevT;
}tNode;

typedef struct tList{
	struct tNode* head;
	struct tNode* tail;
	uint32_t row_cml;
}tList;

tList* SCH_tlist;

void SCH_Init(void);
unsigned char SCH_Add_Task (unsigned int TID, void (*pFunction)(void), unsigned int DELAY, unsigned int PERIOD);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
unsigned char SCH_Delete_Tasks();


#endif /* INC_SCHEDULER_H_ */
