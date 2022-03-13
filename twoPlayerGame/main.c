#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PORT_interface.h"
#include "DIO_interface.h"

#include "CLCD_interface.h"
#include "Keypad_interface.h"
#include "TactileButton_interface.h"

#define ACTIVE 1
#define INACTIVE 0


static u8 Player1Score = 0;
static u8 Player2Score = 0;

static u8 Player1ClickCount = 0;
static u8 Player2ClickCount = 0;

static u8 Player1LedBlinkFlag = INACTIVE;
static u8 Player2LedBlinkFlag = INACTIVE;

void main(void) {

	PORT_voidInit();

	u8 Local_u8ButtonPressed = 0;

	CLCD_voidInit();
	CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
	CLCD_voidGotoXY(2, 0);
	CLCD_voidWriteString("Game Start In");

	CLCD_voidGotoXY(7, 1);
	CLCD_voidSendData('3');
	_delay_ms(1000);

	CLCD_voidGotoXY(7, 1);
	CLCD_voidSendData('2');
	_delay_ms(1000);

	CLCD_voidGotoXY(7, 1);
	CLCD_voidSendData('1');
	_delay_ms(1000);

	CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
	CLCD_voidGotoXY(4, 0);
	CLCD_voidWriteString("Start!");
	_delay_ms(500);
	CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);


	CLCD_voidGotoXY(13, 0);
	CLCD_voidSendNumber(Player1ClickCount);

	CLCD_voidGotoXY(13, 1);
	CLCD_voidSendNumber(Player2ClickCount);

	while (1) {

		CLCD_voidGotoXY(0, 0);
		CLCD_voidWriteString("P1 Score:");
		CLCD_voidSendNumber(Player1Score);

		CLCD_voidGotoXY(0, 1);
		CLCD_voidWriteString("P2 score:");
		CLCD_voidSendNumber(Player2Score);

		Local_u8ButtonPressed = Keypad_u8GetPressedKey();
		if (Local_u8ButtonPressed) {
			TactileButton_u8DebounceButton(DIO_u8PORTD, DIO_u8PIN5);
		}

		if (Local_u8ButtonPressed == 1) {
			Player1ClickCount++;

			if (Player1ClickCount % 3 == 0) {
				Player1Score++;
				Player1LedBlinkFlag = ACTIVE;
				//Player1ClickCount = 0;
			}

			if (Player2ClickCount != 0) {

				Player1ClickCount = 0;
				Player2ClickCount = 0;
				CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
			}

			CLCD_voidGotoXY(13, 0);
			CLCD_voidSendNumber(Player1ClickCount);
			CLCD_voidGotoXY(13, 1);
			CLCD_voidSendNumber(Player2ClickCount);
			Local_u8ButtonPressed = 0;
		}

		else if (Local_u8ButtonPressed == 16) {
			Player2ClickCount++;

			if (Player2ClickCount % 3 == 0) {
				Player2Score++;
				Player2LedBlinkFlag = ACTIVE;
			}

			if (Player1ClickCount != 0) {

				Player1ClickCount = 0;
				Player2ClickCount = 0;
				CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
			}

			CLCD_voidGotoXY(13, 0);
			CLCD_voidSendNumber(Player1ClickCount);
			CLCD_voidGotoXY(13, 1);
			CLCD_voidSendNumber(Player2ClickCount);
			Local_u8ButtonPressed = 0;
		}

		if (Player1LedBlinkFlag == ACTIVE) {
			DIO_u8TogglePinValue(DIO_u8PORTB, DIO_u8PIN1);
			_delay_ms(50);
			DIO_u8TogglePinValue(DIO_u8PORTB, DIO_u8PIN1);
			_delay_ms(50);

			DIO_u8TogglePinValue(DIO_u8PORTB, DIO_u8PIN1);
			_delay_ms(50);
			DIO_u8TogglePinValue(DIO_u8PORTB, DIO_u8PIN1);
			_delay_ms(50);

			DIO_u8TogglePinValue(DIO_u8PORTB, DIO_u8PIN1);
			_delay_ms(50);
			DIO_u8TogglePinValue(DIO_u8PORTB, DIO_u8PIN1);
			_delay_ms(50);

			Player1LedBlinkFlag = INACTIVE;
		}

		if (Player2LedBlinkFlag == ACTIVE) {
			DIO_u8TogglePinValue(DIO_u8PORTB, DIO_u8PIN0);
			_delay_ms(50);
			DIO_u8TogglePinValue(DIO_u8PORTB, DIO_u8PIN0);
			_delay_ms(50);

			DIO_u8TogglePinValue(DIO_u8PORTB, DIO_u8PIN0);
			_delay_ms(50);
			DIO_u8TogglePinValue(DIO_u8PORTB, DIO_u8PIN0);
			_delay_ms(50);

			DIO_u8TogglePinValue(DIO_u8PORTB, DIO_u8PIN0);
			_delay_ms(50);
			DIO_u8TogglePinValue(DIO_u8PORTB, DIO_u8PIN0);
			_delay_ms(50);

			Player2LedBlinkFlag = INACTIVE;
		}

	}

}

