/*
 * main.c
 *
 *  Created on: 14 Oct 2020
 *      Author: es-RaghadAly2023
 */

#include <util/delay.h>

#include "STD_TYPES.h"

#include "TIMER_interface.h"
#include "PORT_interface.h"

#include "SERVO_interface.h"

void main(void) {

	Timer1_voidInit();
	PORT_voidInit();
	u8 Local_u8Counter = 0;

	while (1) {
		SERVO_u8SetAngle(0, 180);
		_delay_ms(2000);
		SERVO_u8SetAngle(0, 0);
		_delay_ms(2000);

		/*
		Local_u8Counter++;
		if (Local_u8Counter == 180) {
			Local_u8Counter = 0;
		}
		*/
	}

}
