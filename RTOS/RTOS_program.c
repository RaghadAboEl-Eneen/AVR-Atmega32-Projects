/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: RTOS stack           **********/
/**********      SWC: RTOS    			     **********/
/**********      Date: 20-10-2020            **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#include "STD_TYPES.h"

#include "TIMER_interface.h"

#include "RTOS_private.h"
#include "RTOS_interface.h"
#include "RTOS_config.h"

Task_t SystemTasks[TASK_NUMBER] = { { NULL } };

u8 RTOS_u8CreateTask(u8 Copy_u8Priority, u16 Copy_u16Periodicity, void (*Copy_pvTaskFunction)(void), u8 Copy_u8FirstDelay) {

	u8 Local_u8ErrorState = OK;

	if(SystemTasks[Copy_u8Priority].TaskFunction == NULL) {

	SystemTasks[Copy_u8Priority].Periodicity = Copy_u16Periodicity;
	SystemTasks[Copy_u8Priority].TaskFunction = Copy_pvTaskFunction;
	SystemTasks[Copy_u8Priority].State = TASK_RESUMED;
	SystemTasks[Copy_u8Priority].FirstDelay = Copy_u8FirstDelay;

	} else {
		//Required priority is reserved for another function
		Local_u8ErrorState = NOOK;
	}

	return Local_u8ErrorState;

}

void RTOS_voidStart(void) {

	Timer0_u8CompareMatchSetCallBack(&voidScheduler);
	Timer0_voidInit();

}

void RTOS_voidSuspendTask(u8 Copy_u8Priority) {

	SystemTasks[Copy_u8Priority].State = TASK_SUSPENDED;


}

void RTOS_voidResumeTask(u8 Copy_u8Priority) {

	SystemTasks[Copy_u8Priority].State = TASK_RESUMED;


}


void RTOS_voidDeleteTask(u8 Copy_u8Priority) {

	SystemTasks[Copy_u8Priority].TaskFunction =  NULL;
}



static void voidScheduler(void) {

	static u16 Local_u16Counter = 0;
	u8 Local_u8TaskCounter;
	Local_u16Counter++;

	//Loop on the tasks to check everyone's periodicity
	for (Local_u8TaskCounter = 0; Local_u8TaskCounter < TASK_NUMBER; Local_u8TaskCounter++) {

	if(SystemTasks[Local_u8TaskCounter] == TASK_RESUMED) {
		if(SystemTasks[Local_u8TaskCounter].FirstDelay == 0) {
		if (SystemTasks[Local_u8TaskCounter].TaskFunction != NULL) {
				/*invoke the task function*/
				SystemTasks[Local_u8TaskCounter].TaskFunction();
				SystemTasks[Local_u8TaskCounter].FirstDelay = SystemTasks[Local_u8TaskCounter].Periodicity -1;
			}
		} else {
			//Decrement the first delay
			SystemTasks[Local_u8TaskCounter].FirstDelay--;
		}

		}

	}x	 else {

		/*Task suspended , do nothing*/
	}

}
