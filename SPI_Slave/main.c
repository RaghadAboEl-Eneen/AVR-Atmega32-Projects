/*
 * main.c
 *
 *  Created on: Oct 8, 2020
 *      Author: es-RaghadAly2023
 */

#include "util/delay.h"

#include "STD_TYPES.h"

#include "SPI_interface.h"
#include "PORT_interface.h"
#include "DIO_interface.h"
#include "GIE_interface.h"
void SPI_ISR(void);

u8 Local_u8ReceivedDataArr[3];
//Slave main

void main(void) {
	PORT_voidInit();
	GIE_voidEnableGlobal();
	SPI_voidInit();

	u8 Local_u8ReceivedData;

	u8 Local_u8SentDataArr[3] = { 1, 2, 3 };

	while (1) {

		//Receive from  the master

		//SPI_u8Transcieve(Local_u8SentDataArr[0], &Local_u8ReceivedData);
		//SPI_u8TransceiveBufferSynchronous(Local_u8SentDataArr, Local_u8ReceivedDataArr, 3);

		SPI_u8TransceiveBufferAsynchronous(Local_u8SentDataArr, Local_u8ReceivedDataArr, 3, &SPI_ISR);

		_delay_ms(100);

	}

}

void SPI_ISR(void) {

	if (Local_u8ReceivedDataArr[2] == 3) {
		DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_HIGH);
	}
}

