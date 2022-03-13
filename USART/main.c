/*
 * main.c
 *
 *  Created on: Oct 6, 2020
 *      Author: es-RaghadAly2023
 */

#include "STD_TYPES.h"

#include "USART_interface.h"
#include "PORT_interface.h"
#include "DIO_interface.h"
#include "GIE_interface.h"

#include "LED_interface.h"

void Transmit_Function(void);
void Receive_Function(void);

u8 Local_u8Arr[255];
u8 Local_u8Counter = 0;

void main(void) {

	PORT_voidInit();
	USART_voidInit();
	GIE_voidEnableGlobal();



	LED_T LED_One = { DIO_u8PORTA, DIO_u8PIN0, SOURCE };
	LED_u8LED_OFF(&LED_One);

	//USART_u8SendStringAsynchronous(Local_cString, &Transmit_Function);
	//USART_u8ReceiveBufferSynchronous(Local_u8Arr , 10);
	/*
	for(Local_u8Counter = 0 ; Local_u8Counter < 10 ; Local_u8Counter++) {
		USART_u8SendData(Local_u8Arr[Local_u8Counter]);
	}
	*/
	//USART_u8SendStringSynchronous("Hello world");

	while (1) {

		USART_u8ReceiveBufferAsynchronous(Local_u8Arr, 10, &Receive_Function);



/*
		if (Local_u8ReceivedData == '1') {
			LED_u8LED_ON(&LED_One);
		} else if (Local_u8ReceivedData == '2') {
			LED_u8LED_OFF(&LED_One);
		}
*/
	}

}

void Transmit_Function(void) {

	USART_u8SendStringSynchronous(" Transmit Complete ");

}

void Receive_Function(void) {

	for(Local_u8Counter = 0 ; Local_u8Counter < 10 ;  Local_u8Counter++) {
				USART_u8SendData(Local_u8Arr[Local_u8Counter]);

			}


}



