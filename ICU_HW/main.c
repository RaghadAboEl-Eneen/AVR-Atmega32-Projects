/*
 * main.c
 *
 *  Created on: Oct 1, 2020
 *      Author: es-RaghadAly2023
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "GIE_interface.h"
#include "TIMER_interface.h"
#include "TIMER_register.h"

#include "CLCD_interface.h"

void ICU_ISR(void);

static volatile u16 Period_Ticks = 0;
static volatile u16 On_Ticks = 0;
static u16 Local_u16Reading1 = 0;
static u16 Local_u16Reading2 = 0;
static u16 Local_u16Reading3 = 0;

void main(void) {

	PORT_voidInit();
	CLCD_voidInit();

	ICU_u8SetCallBack(&ICU_ISR);
	Timer0_voidInit();
	Timer1_voidInit();
	ICU_voidInit();

	GIE_voidEnableGlobal();

	while (1) {

		while (Period_Ticks == 0 || On_Ticks == 0 )
			;

		CLCD_voidGotoXY(0, 0);
		CLCD_voidWriteString("PeriodTicks= ");
		//CLCD_voidSendNumber(Local_u16Reading1);
		//CLCD_voidSendData(' ');
		//CLCD_voidSendNumber(Local_u16Reading2);
		//CLCD_voidSendData(' ');
		//CLCD_voidSendNumber(Local_u16Reading3);
		//CLCD_voidSendData(' ');

		CLCD_voidSendNumber(Period_Ticks);
		CLCD_voidGotoXY(0, 1);
		CLCD_voidWriteString("OnTicks= ");
		CLCD_voidSendNumber(On_Ticks);

	}
}

void ICU_ISR(void) {

	static u8 Local_u8Counter = 0;


	Local_u8Counter++;

	if (Local_u8Counter == 1) {

		Local_u16Reading1 = ICU_u16ReadInputCapture();

	} else if (Local_u8Counter == 2) {

		CLR_BIT(TCCR1B, TCCR1B_ICES1);
		//ICU_u8SetTrigger(FALLING_EDGE);
		Local_u16Reading2 = ICU_u16ReadInputCapture();
		Period_Ticks = Local_u16Reading2 - Local_u16Reading1;

	} else if (Local_u8Counter == 3) {

		Local_u16Reading3 = ICU_u16ReadInputCapture();
		On_Ticks = Local_u16Reading3 - Local_u16Reading2;

		CLR_BIT(TIMSK, TIMSK_TICIE1);

	}

}
