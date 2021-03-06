/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: HAL                  **********/
/**********      SWC: Keypad                 **********/
/**********      Date: 1-9-2020              **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "Keypad_config.h"
#include "Keypad_private.h"
#include "Keypad_interface.h"



u8 Keypad_u8GetPressedKey(void) {
	
	u8 Local_u8ColumnIndex, Local_u8RowIndex, Local_u8PressedKey = NO_PRESSED_KEY, Local_u8PinState;
	u8 Local_u8_KeypadArr[ROW_NUMBER][COLUMN_NUMBER] = KEYPAD_BUTTONS_VALUES;
	u8 Local_u8ColumnArr [COLUMN_NUMBER] = {COLUMN_PIN0, COLUMN_PIN1, COLUMN_PIN2, COLUMN_PIN3};
	u8 Local_u8RowArr    [ROW_NUMBER]    = {ROW_PIN0, ROW_PIN1, ROW_PIN2, ROW_PIN3};

	for(Local_u8ColumnIndex = 0 ; Local_u8ColumnIndex < COLUMN_NUMBER ; Local_u8ColumnIndex++) {

		//Activate the current column;
		DIO_u8SetPinValue(KEYPAD_PORT, Local_u8ColumnArr[Local_u8ColumnIndex], DIO_u8PIN_LOW);

		for(Local_u8RowIndex = 0 ; Local_u8RowIndex < ROW_NUMBER; Local_u8RowIndex++) {

			//Read the current row;
			DIO_u8GetPinValue(KEYPAD_PORT, Local_u8RowArr[Local_u8RowIndex], &Local_u8PinState);

			if(Local_u8PinState == DIO_u8PIN_LOW) {
				Local_u8PressedKey = Local_u8_KeypadArr[Local_u8RowIndex][Local_u8ColumnIndex];
				// Pulling busy waiting until the key is released
				while(Local_u8PinState == DIO_u8PIN_LOW) {
					DIO_u8GetPinValue(KEYPAD_PORT, Local_u8RowArr[Local_u8RowIndex], &Local_u8PinState);
				}

				return Local_u8PressedKey;
			}
		}
		//Deactivate the current column;
		DIO_u8SetPinValue(KEYPAD_PORT, Local_u8ColumnArr[Local_u8ColumnIndex], DIO_u8PIN_HIGH);
	}


	return Local_u8PressedKey;
}
