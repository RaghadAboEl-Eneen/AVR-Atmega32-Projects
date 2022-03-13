#include <util/delay.h>

#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"

#include "Motor_interface.h"

void main(void) {

	PORT_voidInit();

	Motor_T Motor_One = {DIO_u8PORTD, DIO_u8PIN6, DIO_u8PIN7};

    DIO_u8SetPortValue(DIO_u8PORTB, DIO_u8PORT_HIGH);
	while(1) {

/*

		Motor_u8RotateClockwise(&Motor_One);
		_delay_ms(3000);
		Motor_u8RotateAntiClockwise(&Motor_One);
		_delay_ms(3000);

*/

	}

}
