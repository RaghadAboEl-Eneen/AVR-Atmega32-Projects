/*
 * main.c
 *
 *  Created on: 23 Oct 2020
 *      Author: es-RaghadAly2023
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "PORT_interface.h"

#include"FreeRTOS.h"
#include "semphr.h"
#include"task.h"

#include "CLCD_interface.h"

void LCD1(void * pv);
void LCD2(void * pv);

xSemaphoreHandle LCDSem;

void main(void) {

	PORT_voidInit();
	CLCD_voidInit();

	xTaskCreate(&LCD1, NULL, 250, NULL, 0, NULL);
	xTaskCreate(&LCD2, NULL, 250, NULL, 0, NULL);

	LCDSem = xSemaphoreCreateCounting(1, 1);

	vTaskStartScheduler();

	while (1) {

	}

}

void LCD1(void * pv) {

	u8 Local_u8SemaphoreState;

	while (1) {

		/*Try to take the semaphore*/
		Local_u8SemaphoreState = xSemaphoreTake(LCDSem, 0);

		if (Local_u8SemaphoreState == pdPASS) {
			CLCD_voidWriteString("IAMTASK1");
			/*Access is finished , give the semaphore*/
			xSemaphoreGive(LCDSem);
		} else {

		}

		vTaskDelay(1000);
	}
}
void LCD2(void * pv) {

	u8 Local_u8SemaphoreState;

	while (1) {

		/*Try to take the semaphore*/
		Local_u8SemaphoreState = xSemaphoreTake(LCDSem, 0);

		if (Local_u8SemaphoreState == pdPASS) {
			CLCD_voidWriteString("IAMTASK2");
			/*Access is finished , give the semaphore*/
			xSemaphoreGive(LCDSem);
		} else {

		}

		vTaskDelay(1000);
	}
}

