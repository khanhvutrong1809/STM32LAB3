/*
 * scheduler.c
 *
 *  Created on: Nov 27, 2024
 *      Author: Admin
 */

#include "scheduler.h"

sTask SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;

void SCH_Init(void){
	current_index_task = 0;
//	for(int i = 0; i < SCH_MAX_TASKS; i++){
//		SCH_tasks_G[current_index_task].pTask = 0;
//		SCH_tasks_G[current_index_task].Delay = 0;
//		SCH_tasks_G[current_index_task].Period = 0;
//		SCH_tasks_G[current_index_task].RunMe = 0;
//		SCH_tasks_G[current_index_task].TaskID = 0;
//	}
}

void SCH_Add_Task(void (* pFunction) () , uint32_t DELAY, uint32_t PERIOD){
	if(current_index_task < SCH_MAX_TASKS){
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY;
		SCH_tasks_G[current_index_task].Period = PERIOD;
		SCH_tasks_G[current_index_task].RunMe = 0;

		SCH_tasks_G[current_index_task].TaskID = current_index_task;
		current_index_task++;
	}
}

void SCH_Update(void){
	for(int i = 0; i < current_index_task; i++){
		if(SCH_tasks_G[i].Delay > 0){
			SCH_tasks_G[i].Delay --;
		}
		else{
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe += 1;
		}
	}
}
void SCH_Dispatch_Tasks(void){

	for(int i = 0; i < current_index_task; i++){
		if(SCH_tasks_G[i].RunMe > 0){
			SCH_tasks_G[i].RunMe --;
			(*SCH_tasks_G[i].pTask)();

		}
	}
}
void SCH_Delete_Task(uint32_t TaskID) {
    if (TaskID >= current_index_task || SCH_tasks_G[TaskID].pTask == 0) return;
    SCH_tasks_G[TaskID].pTask = 0x0000;
    SCH_tasks_G[TaskID].Delay = 0;
    SCH_tasks_G[TaskID].Period = 0;
    SCH_tasks_G[TaskID].RunMe = 0;

    for (int i = TaskID; i < current_index_task - 1; i++) {
        SCH_tasks_G[i] = SCH_tasks_G[i + 1];
    }

    current_index_task--;
}


