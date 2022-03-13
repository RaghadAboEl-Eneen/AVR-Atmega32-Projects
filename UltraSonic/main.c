/*
 * main.c
 *
 *  Created on: 30 Aug 2021
 *      Author: es-RaghadAly2023
 */

#include <util/delay.h>


#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "PORT_interface.h"

#include "UltraSonic_Interface.h"
#include "CLCD_interface.h"




void main(void) {

	f32 Local_f32Distance = 0;

	UltraSonic_voidInit();
	PORT_voidInit();
	CLCD_voidInit();


	while(1) {


	CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
	CLCD_voidWriteString("Distance:");
	CLCD_voidGotoXY(10,0);
	//UltraSonic_voidSendTrigger();
	Local_f32Distance = Ultrasonic_voidGetDistance();
	CLCD_voidSendNumber(Local_f32Distance);
	CLCD_voidWriteString("cm");
	_delay_ms(1000);


	}
}
