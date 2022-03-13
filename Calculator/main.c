#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"

#include "CLCD_interface.h"
#include "Keypad_interface.h"

void main(void) {

	PORT_voidInit();

	CLCD_voidInit();
	CLCD_voidSendCommand(CLCD_TURN_CURSOR_ON);

	u8 Operand1, Operand2, Operator, result;
	u8 Value_Pressed = 0;
	while (1) {

		Value_Pressed = Keypad_u8GetPressedKey();
		if (Value_Pressed != 0xff) {
			switch (Value_Pressed) {
			case 0:
				CLCD_voidSendData('0');
				break;
			case 1:
				CLCD_voidSendData('1');
				break;
			case 2:
				CLCD_voidSendData('2');
				break;
			case 3:
				CLCD_voidSendData('3');
				break;
			case 4:
				CLCD_voidSendData('4');
				break;
			case 5:
				CLCD_voidSendData('5');
				break;
			case 6:
				CLCD_voidSendData('6');
				break;
			case 7:
				CLCD_voidSendData('7');
				break;
			case 8:
				CLCD_voidSendData('8');
				break;
			case 9:
				CLCD_voidSendData('9');
				break;
			case 40:
				CLCD_voidSendData('+');
				break;
			case 50:
				CLCD_voidSendData('-');
				break;
			case 60:
				CLCD_voidSendData('*');
				break;
			case 70:
				CLCD_voidSendData('/');
				break;
			case 100:
				CLCD_voidSendData('=');
				break;
			case 90:
				CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
				break;
			}

		}

	}
}
