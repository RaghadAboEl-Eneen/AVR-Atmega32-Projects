/*
 * main.c
 *
 *  Created on: Sep 27, 2020
 *      Author: es-RaghadAly2023
 */

#include <util/delay.h>

#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"

#include "LED_interface.h"



void main(void) {

	LED_T LED_One 	= {DIO_u8PORTA, DIO_u8PIN0, SOURCE};
	LED_T LED_Two 	= {DIO_u8PORTA, DIO_u8PIN1, SOURCE};
	LED_T LED_Three = {DIO_u8PORTA, DIO_u8PIN2, SOURCE};

	LED_u8LED_ON(&LED_One);
	LED_u8LED_OFF(&LED_Two);
	while(1) {
		LED_u8LED_TOGGLE(&LED_Three);
		_delay_ms(250);
	}
}
