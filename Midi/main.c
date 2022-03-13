/*
 * main.c
 *
 *  Created on: Sep 24, 2020
 *      Author: es-RaghadAly2023
 */
#include <util/delay.h>

#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "TIMER_interface.h"
#include "GIE_interface.h"

#include "CLCD_interface.h"

void Timer_ISR(void);
void Timer_ISR2(void);

void main(void) {

	PORT_voidInit();
	GIE_voidEnableGlobal();
	Timer0_voidInit();
	Timer1_voidInit();
	u16 Local_u16OverflowTicks;
	//Timer0_u8OverflowSetCallBack(&Timer_ISR);
	//Timer0_u8CompareMatchSetCallBack(&Timer_ISR2);
	CLCD_voidInit();

	u16 Local_u16Counter=100;
	//Local_u16OverflowTicks = Timer1_voidSetTimer1_voidSetTone(3,261,30);
	//CLCD_voidSendNumber(Local_u16OverflowTicks);

	while (1) {

/*
		Timer1_voidSetTone(Local_u16Counter, 1000);
		_delay_ms(250);
		Local_u16Counter+=10;
		CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
		CLCD_voidGotoXY(0,0);
		CLCD_voidSendNumber(Local_u16Counter);
*/


		    Timer1_voidSetTone( 493, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 440, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 349, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 493, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 440, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 349, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 174, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 440, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 329, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 293, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 164, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 246, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(375.0);
		    Timer1_voidSetTone( 246, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(375.0);
		    Timer1_voidSetTone( 246, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 130, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 440, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    /*
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 349, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 493, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 440, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 349, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 493, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 440, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 329, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 293, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 123, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 246, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(375.0);
		    Timer1_voidSetTone( 246, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(375.0);
		    Timer1_voidSetTone( 246, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 349, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 220, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 220, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 246, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 220, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 349, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 220, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);

		    Timer1_voidSetTone( 220, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 246, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 220, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 130, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 195, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 329, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 195, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 246, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 220, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 246, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 195, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(375.0);
		    Timer1_voidSetTone( 195, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(375.0);
		    Timer1_voidSetTone( 195, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 349, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 220, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 220, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 246, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 220, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 349, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 220, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 220, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 246, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 220, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 130, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 195, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 329, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 195, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 493, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 195, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 391, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 195, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(375.0);
		    Timer1_voidSetTone( 195, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(375.0);
		    Timer1_voidSetTone( 195, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 349, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 174, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 349, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 174, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 293, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 174, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 116, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 174, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 587, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 174, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 587, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 174, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 329, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 164, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 391, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 164, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 391, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 164, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 110, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 164, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 391, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 164, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 261, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(375.0);
		    Timer1_voidSetTone( 349, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 174, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 220, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 174, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 293, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 174, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 116, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 174, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 233, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 174, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 349, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 174, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 349, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 174, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 493, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 174, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 349, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 220, 112.5);
		    _delay_ms(125.0);
		    _delay_ms(125.0);
		    Timer1_voidSetTone( 164, 112.5);
		    _delay_ms(125.0);
*/
	}
}

void Timer0_ISR(void) {
	static u8 flag = 0;
	static u16 Local_u16Counter = 0;
	Local_u16Counter++;
	if (Local_u16Counter == 4883) {
		if (flag == 0) {
			DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN0, DIO_u8PIN_HIGH);
			flag = 1;
		} else if (flag == 1) {
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
	if (Local_u16Counter == 6250) {
		if (flag == 0) {
			DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN0, DIO_u8PIN_HIGH);
			flag = 1;
		} else if (flag == 1) {
			DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN0, DIO_u8PIN_LOW);
			flag = 0;
		}

		Local_u16Counter = 0;

	}

}
