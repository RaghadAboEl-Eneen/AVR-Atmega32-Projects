#include <avr/io.h>
#include <util/delay.h>

#include "STD_TYPES.h"
#include "DIO_interface.h"

#include <stdlib.h>

void main(void) {


    DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN0, DIO_u8PIN_INPUT);
	DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN0, DIO_u8PIN_HIGH);

	DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN1, DIO_u8PIN_OUTPUT);

	u8 * flag = malloc(sizeof(u8));
	while(1) {
	DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN0, flag);
	if(*flag == 0) {
		_delay_ms(30);
		DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN1, DIO_u8PIN_HIGH);
	} else if(*flag == 1) {
		DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN1, DIO_u8PIN_LOW);
	}

	}



}
