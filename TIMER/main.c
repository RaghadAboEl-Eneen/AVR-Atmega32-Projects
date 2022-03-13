/*
 * main.c
 *
 *  Created on: Sep 24, 2020
 *      Author: es-RaghadAly2023
 */

#include "STD_TYPES.h"


#include "DIO_interface.h"
#include "PORT_interface.h"
#include "TIMER_interface.h"
#include "GIE_interface.h"


void Timer_ISR(void);
void Timer_ISR2(void);


void main(void) {

	PORT_voidInit();
	GIE_voidEnableGlobal();
	Timer0_voidInit();
	Timer0_u8OverflowSetCallBack(&Timer_ISR);
	Timer0_u8CompareMatchSetCallBack(&Timer_ISR2);
	while(1) {

	}
}




void Timer_ISR(void) {

	static u8 flag = 0;
	static u16 Local_u16Counter = 0;
	Local_u16Counter++;
	if(Local_u16Counter == 4883) {
		if(flag == 0) {
				DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN0, DIO_u8PIN_HIGH);
				flag = 1;
				} else if(flag == 1) {
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN0, DIO_u8PIN_LOW);
					flag = 0;
				}

		Local_u16Counter = 0;
		Timer0_voidSetPreload(48);

	}

}

void Timer_ISR2(void) {

	static u8 flag = 0;
	static u16 Local_u16Counter = 0;
	Local_u16Counter++;
	if(Local_u16Counter == 6250) {
		if(flag == 0) {
				DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN0, DIO_u8PIN_HIGH);
				flag = 1;
				} else if(flag == 1) {
					DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN0, DIO_u8PIN_LOW);
					flag = 0;
				}

		Local_u16Counter = 0;

	}

}




