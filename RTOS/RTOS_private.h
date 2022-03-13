/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: RTOS stack           **********/
/**********      SWC: RTOS    			     **********/
/**********      Date: 20-10-2020            **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/


#ifndef RTOS_PRIVATE_H_
#define RTOS_PRIVATE_H_

static void voidScheduler(void);

typedef struct {

	u16 Periodicity;
	void(*TaskFunction)(void)
	u8 State;
	u8 FirstDelay;

}Task_t;

#define TASK_SUSPENDED		1
#define TASK_RESUMED		2

#endif
