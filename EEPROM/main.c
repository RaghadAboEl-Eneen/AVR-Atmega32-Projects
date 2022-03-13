/*
 * main.c
 *
 *  Created on: 13 Oct 2020
 *      Author: es-RaghadAly2023
 */

#include "STD_TYPES.h"

#include "TWI_interface.h"
#include "PORT_interface.h"
#include "DIO_interface.h"

#include "EEPROM_interface.h"


void main(void) {

	u8 Local_u8ReceivedData;

	PORT_voidInit(); 		//Define PORTA as output
	TWI_voidInitMaster(0);

 	EEPROM_voidSendDataByte(0, 255);

 	//Local_u8ReceivedData = 255;

    Local_u8ReceivedData = EEPPROM_u8ReadDataByte(0);

 	//Local_u8ReceivedData = 255;

	DIO_u8SetPortValue(DIO_u8PORTC, Local_u8ReceivedData);

	while(1) {

	}

}
