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

//Master
void main(void) {
	PORT_voidInit();
	GIE_voidEnableGlobal();
	SPI_voidInit();
	u8 Local_u8ReceivedData;
	u8 Local_u8ReceivedDataArr[3];
	u8 Local_u8SentDataArr[3] = {1,2,3};

	while(1) {

		//Send 1 to the slave
		//SPI_u8TransceiveBufferSynchronous(Local_u8SentDataArr, Local_u8ReceivedDataArr, 3);
		//SPI_u8Transcieve(1, &Local_u8ReceivedData);
		SPI_u8TransceiveBufferAsynchronous(Local_u8SentDataArr, Local_u8ReceivedDataArr, 3, &SPI_ISR);

		_delay_ms(1000);
	}

}

void SPI_ISR(void) {

	/*Do nothing*/
}
