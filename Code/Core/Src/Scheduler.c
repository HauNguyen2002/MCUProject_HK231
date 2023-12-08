/*
 * Scheduler.c
 *
 *  Created on: Oct 9, 2023
 *      Author: ASUS
 */
#include "Scheduler.h"
//UART_HandleTypeDef huart1;

char str[200];
int giveBackCursum=0;
void newTail(tNode* nTail, tNode* oldTail) {

	nTail->waitTime-=SCH_tlist->row_cml;
	SCH_tlist->row_cml+=nTail->waitTime;

	SCH_tlist->tail=nTail;
	oldTail->nextT=nTail;
	nTail->prevT=oldTail;
	nTail->nextT=NULL;
}
void newHead(tNode* nHead, tNode* oldHead) {

	SCH_tlist->row_cml+=nHead->waitTime;
	oldHead->waitTime-=nHead->waitTime;
	SCH_tlist->row_cml+=oldHead->waitTime;

	SCH_tlist->head = nHead;
	oldHead->prevT=nHead;
	nHead->nextT=oldHead;
	nHead->prevT=NULL;

}
void newNorm(tNode* nNorm, tNode* prev, tNode* next){

	nNorm->waitTime-=SCH_tlist->row_cml;
	SCH_tlist->row_cml+=nNorm->waitTime;
	next->waitTime-=nNorm->waitTime;
	SCH_tlist->row_cml+=next->waitTime;

	nNorm->nextT=prev->nextT;
	nNorm->prevT=prev;
	prev->nextT=nNorm;
	next->prevT=nNorm;
}

void SCH_Arrange_Head(){
	if(SCH_tlist->head==SCH_tlist->tail){
		SCH_tlist->head=SCH_tlist->tail=NULL;
		SCH_tlist->head->nextT=NULL;
		SCH_tlist->head->prevT=NULL;
	}
	if(SCH_tlist->head!=SCH_tlist->tail){
		SCH_tlist->head=SCH_tlist->head->nextT;
		SCH_tlist->head->prevT=NULL;
	}
}

void SCH_Arrange_List(tNode* cur_node,unsigned int DURATION){
	cur_node->waitTime=DURATION;
	if(SCH_tlist->head!=NULL && SCH_tlist->tail!=NULL){
		tNode* walker=SCH_tlist->tail;
		while(walker!=NULL){
			if(cur_node->waitTime>=SCH_tlist->row_cml) break;
			if(walker->nextT!=NULL){
				giveBackCursum+=walker->nextT->waitTime;
			}
			SCH_tlist->row_cml-= walker->waitTime;
			walker=walker->prevT;
		}

		if(walker==NULL) newHead(cur_node, SCH_tlist->head);
		else if(walker==SCH_tlist->tail) newTail(cur_node, walker);
		else newNorm(cur_node, walker, walker->nextT);

		SCH_tlist->row_cml+=giveBackCursum;
		giveBackCursum=0;
	}
	if(SCH_tlist->head==NULL && SCH_tlist->tail==NULL){
			SCH_tlist->head=SCH_tlist->tail=cur_node;
			cur_node->nextT=cur_node->prevT=NULL;
			SCH_tlist->row_cml+=cur_node->waitTime;
	}
}
void SCH_Init(void){
	tList* SCH_tlist=(tList*)malloc(10*sizeof(tList));
	SCH_tlist->head=SCH_tlist->tail=NULL;
	SCH_tlist->row_cml=0;
}
void SCH_Update(void)
{
	if(SCH_tlist->head!=NULL){

		if(SCH_tlist->head->waitTime>0){
				SCH_tlist->head->waitTime-=1;
				SCH_tlist->row_cml-=1;
			giveBackCursum++;
		}
	}
}

unsigned char SCH_Add_Task (unsigned int TID, void (*pFunction)(void), unsigned int DELAY, unsigned int PERIOD)
{
	tNode* new_task=(tNode*)malloc(sizeof(tNode));
	new_task->delay=DELAY;
	new_task->period=PERIOD;
	new_task->ptask=pFunction;
	new_task->tId=TID;
	new_task->nextT=new_task->prevT=NULL;
	SCH_Arrange_List(new_task,new_task->delay);
//	tNode* temp= SCH_tlist->head;
//	sprintf(str,"r_cml: %d\r\n",SCH_tlist->row_cml);
//	HAL_UART_Transmit(&huart1, str, sizeof(str), 50);
//	while(temp!=NULL){
//		sprintf(str,"tid: %d  waittime: %d\r\n",temp->tId,temp->waitTime);
//		HAL_UART_Transmit(&huart1, str, sizeof(str), 50);
//		temp=temp->nextT;
//	}
}


void SCH_Dispatch_Tasks(void)
{
//	tNode* temp= SCH_tlist->head;
//	sprintf(str,"r_cml: %d\r\n",SCH_tlist->row_cml);
//	HAL_UART_Transmit(&huart1, str, sizeof(str), 50);
//	while(temp!=NULL){
//		sprintf(str,"tid: %d  waittime: %d\r\n",temp->tId,temp->waitTime);
//		HAL_UART_Transmit(&huart1, str, sizeof(str), 50);
//		temp=temp->nextT;
//	}
	if(SCH_tlist->head->waitTime==0){
//		sprintf(str,"---------\r\n");
//		HAL_UART_Transmit(&huart1, str, sizeof(str), 50);
		(*SCH_tlist->head->ptask)();
		tNode* currenthead=SCH_tlist->head;
		SCH_Arrange_Head();
		if(currenthead->period==0){
			SCH_Delete_Tasks(currenthead);
		}
		if(currenthead->period!=0){
			SCH_Arrange_List(currenthead,currenthead->period);
		}
	}
}


unsigned char SCH_Delete_Tasks(tNode* deltask){
deltask->prevT=deltask->nextT=NULL;
deltask->waitTime=deltask->period=0;
deltask->ptask=0x0000;
}




