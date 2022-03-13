#include <util/delay.h>

#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"

#include "CLCD_interface.h"
#include "TactileButton_interface.h"

#include <stdlib.h>

void main(void) {

	PORT_voidInit();


	/*
	DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN0, DIO_u8PIN_INPUT); //Setting pin as input for button.
	DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN0, DIO_u8PIN_HIGH); //Activating the pullup resistance of pin.

	DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN1, DIO_u8PIN_OUTPUT); //Setting pin as output for led.
	DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN2, DIO_u8PIN_OUTPUT); //Setting pin as output for led.

	DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN1, DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN2, DIO_u8PIN_HIGH);


	//Setting up pins as output for CLCD.
	DIO_u8SetPortDirection(DIO_u8PORTA, DIO_u8PORT_OUTPUT);

	DIO_u8SetPinDirection(DIO_u8PORTC, DIO_u8PIN0, DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTC, DIO_u8PIN1, DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTC, DIO_u8PIN2, DIO_u8PIN_OUTPUT);

*/
	//Initializing CLCD.
	CLCD_voidInit();

	u8 ShiftCounter = 0, Stopper = 0 , Switcher = 0, flag;

	while (1) {
		DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN0, &flag);

        if(flag == 0)
        	if(TactileButton_u8DebounceButton(DIO_u8PORTD, DIO_u8PIN0))
        		ShiftCounter++;


		/*
		DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN0, flag);

		while (*flag == 0) {
			DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN0, flag);
			if(*flag == 1) {
				Stopper = 1;
			}

		}

		if (*flag && Stopper) {
			_delay_ms(30);
			DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN0, flag);
			if (*flag == 1) {
				ShiftCounter++;
				Switcher ^= 1;
				DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN1, Switcher );
				DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN2, !Switcher);
				Stopper = 0;
			}
		}


		 if (*flag == 0) {
		 //DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN1, DIO_u8PIN_HIGH);
		 _delay_ms(8);
		 DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN0, flag);
		 if(*flag == 1) {
		 _delay_ms(15);
		 DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN0, flag);
		 if(*flag == 1) {
		 ShiftCounter++;
		 }
		 } else if(*flag == 0)
		 {
		 _delay_ms(8);
		 DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN0, flag);
		 if (*flag == 1) {
		 ShiftCounter++;
		 }
		 }
		 }
		 */
		CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
		CLCD_voidSendNumber(ShiftCounter);

	}

}
