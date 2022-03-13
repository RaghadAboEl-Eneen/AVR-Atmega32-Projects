/*
 * main.c
 *
 *  Created on: Sep 1, 2020
 *      Author: es-RaghadAly2023
 */


#include <util/delay.h>

#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"

#include "CLCD_interface.h"
#include "TactileButton_interface.h"

void main (void) {

	PORT_voidInit();
	CLCD_voidInit();
    u8 u8_ValuePressed = 0;

	while(1) {
		u8_ValuePressed = Keypad_u8GetPressedKey();
		if(u8_ValuePressed) {
			CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
			CLCD_voidSendNumber(u8_ValuePressed);
		}

	}
}
