/*
 * main.c
 *
 *  Created on: Oct 1, 2020
 *      Author: es-RaghadAly2023
 */
#include "util/delay.h"

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "WATCH_DOG_interface.h"




void main(void) {

	PORT_voidInit();
	DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN7, DIO_u8PIN_HIGH);
	_delay_ms(1000);
	DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN7, DIO_u8PIN_LOW);
	WDT_voidEnable();
	WDT_u8Sleep(6); // sleep for one second
	WDT_voidDisable();

	while(1) {

	}

}

