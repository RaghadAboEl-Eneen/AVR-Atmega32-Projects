/*
 * main.c
 *
 *  Created on: Sep 30, 2020
 *      Author: es-RaghadAly2023
 */

#include <util/delay.h>

#include "STD_TYPES.h"

#include "PORT_interface.h"
#include "DIO_interface.h"

#include "DAC_interface.h"
#include "CLCD_interface.h"



void main(void) {

	PORT_voidInit();
	CLCD_voidInit();

	u8 Local_u8ErrorState;
	u16 Local_u16Volt = 1700;
	while(1) {

		Local_u8ErrorState = DAC_u8SetAnalogVolt(Local_u16Volt);
		_delay_ms(150);
		Local_u16Volt+= 100;
		if(Local_u16Volt == 5000) {
			Local_u16Volt = 1700;
		}

		CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
		CLCD_voidGotoXY(0,0);
		CLCD_voidSendNumber(Local_u8ErrorState);


	}



}
