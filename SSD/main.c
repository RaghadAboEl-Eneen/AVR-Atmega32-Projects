/*
 * main.c
 *
 *  Created on: Sep 27, 2020
 *      Author: es-RaghadAly2023
 */

#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"

#include "SSD_interface.h"


void main(void) {


	PORT_voidInit();
	SSD_T SSD_One = {CKATHODE, DIO_u8PORTA , DIO_u8PORTC, DIO_u8PIN0};
 	SSD_Off(&SSD_One);
	SSD_u8SetNumber(&SSD_One, 8);

	while(1) {

	}
}

