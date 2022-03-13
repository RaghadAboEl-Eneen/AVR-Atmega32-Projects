/*
 * main.c
 *
 *  Created on: Oct 1, 2020
 *      Author: es-RaghadAly2023
 */

#include "STD_TYPES.h"

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"
#include "TIMER_interface.h"

#include "CLCD_interface.h"

void ICU_SW(void);

static volatile u16 Period_Ticks = 0;
static volatile u16 On_Ticks = 0;

void main(void) {

	PORT_voidInit();
	EXTI_voidINT0Init();
	EXTI_u8INTSetCallBack(&ICU_SW, EXTI_INT0);
	Timer0_voidInit();
	Timer1_voidInit();
	GIE_voidEnableGlobal();

	CLCD_voidInit();

	while (1) {

		//busy waiting until the ICU measures the period ticks and the on ticks
		while( (Period_Ticks == 0) && (On_Ticks == 0));
		CLCD_voidGotoXY(0,0);
		CLCD_voidWriteString("PeriodTicks= ");
		CLCD_voidSendNumber(Period_Ticks);
		CLCD_voidGotoXY(0,1);
		CLCD_voidWriteString("On ticks = ");
		CLCD_voidSendNumber(On_Ticks);


	}

}

void ICU_SW(void) {

	static volatile u8 Local_u8Counter = 0;
	Local_u8Counter++;

	if (Local_u8Counter == 1) {
		//Timer starts counting
		Timer1_voidSetPreload(0);

	} else if (Local_u8Counter == 2) {
		//Second rising edge
		//Read the timer to get number of ticks of period time
		Period_Ticks = Timer1_u16ReadTimerValue();

		//Change INT0 trigger to falling edge
		EXTI_u8INTSetSenseControl(FALLING_EDGE, EXTI_INT0);

	} else if (Local_u8Counter == 3) {
		//Third rising edge
		//Falling edge to get the on time
		On_Ticks = Timer1_u16ReadTimerValue();
		On_Ticks-= Period_Ticks;

		EXTI_u8DisableInterrupt(EXTI_INT0);
	}

}

