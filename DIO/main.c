#include "STD_TYPES.h"
#include "DIO_interface.h"
#include <util/delay.h>

void main(void) {
	// 1- Test set pin direction , set pin value ;
/*
    DIO_u8SetPinDirection(DIO_u8PORTA, DIO_u8PIN0,DIO_u8PORT_OUTPUT);

    while(1) {
    	DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_HIGH);
    	_delay_ms(1000);
    	DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_LOW);
    	_delay_ms(1000);
    }
*/
   // 2- Test set port direction , set port value;


    DIO_u8SetPortDirection(DIO_u8PORTA, DIO_u8PORT_OUTPUT);
    DIO_u8SetPortValue(DIO_u8PORTA, DIO_u8PORT_LOW);

while(1);



}

