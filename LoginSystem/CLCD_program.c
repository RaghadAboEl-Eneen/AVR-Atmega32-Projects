/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: CLCD                   **********/
/**********      Date: 25-8-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#include "STD_TYPES.h"
#include <util/delay.h>
#include <stdio.h>

#include "DIO_interface.h"

#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"

void CLCD_voidSendCommand(u8 Copy_u8Command) {

	//1-Set RS value to low for command.
	DIO_u8SetPinValue(CLCD_CONTROL_PORT, CLCD_RS_PIN, DIO_u8PIN_LOW);

	//2- Set RW value to low for write.
	DIO_u8SetPinValue(CLCD_CONTROL_PORT, CLCD_RW_PIN, DIO_u8PIN_LOW);

	//3- Send command to LCD.
	DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Command);

	//4- Send E(nable) pulse to LCD.
	DIO_u8SetPinValue(CLCD_CONTROL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CONTROL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);

}

void CLCD_voidSendData(u8 Copy_u8Data) {

	//1-Set RS value to high for data.
	DIO_u8SetPinValue(CLCD_CONTROL_PORT, CLCD_RS_PIN, DIO_u8PIN_HIGH);

	//2- Set RW value to low for write.
	DIO_u8SetPinValue(CLCD_CONTROL_PORT, CLCD_RW_PIN, DIO_u8PIN_LOW);

	//3- Set data to LCD.
	DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Data);

	//4- Send E(nable) pulse to LCD.
	DIO_u8SetPinValue(CLCD_CONTROL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CONTROL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);

}

void CLCD_voidInit(void) {

	//1- Delay for more than 30 milliseconds.
	_delay_ms(40);

	//2- Function set command: 2 lines(DB3), Font = 5*7(DB2).
	CLCD_voidSendCommand(0b00111000);

	//3- Display on off Control: Display on, Cursor off, Blinking off.
	CLCD_voidSendCommand(0b00001100);

	//4- Display clear.
	CLCD_voidSendCommand(1);

}

void CLCD_voidWriteString(const char * Copy_pchString) {

	u8 LoopCounter = 0;
	if (Copy_pchString != NULL) {

		while (*(Copy_pchString + LoopCounter)) {
			CLCD_voidSendData((char) *(Copy_pchString + LoopCounter));
			LoopCounter++;
		}
	}

}

void CLCD_voidSendNumber(u32 Copy_u32Number) {
	u32 Local_u32TempValue = Copy_u32Number;
	u8 Local_u8DigitCounter = 0, Local_u8Counter = 0, Local_u8Remainder;

	while (Local_u32TempValue > 0) {
		Local_u32TempValue /= 10;
		Local_u8DigitCounter++;
	}

	char arr[Local_u8DigitCounter];
	sprintf(arr, "%d", Copy_u32Number);
	CLCD_voidWriteString(arr);

}

void CLCD_voidGotoXY(u8 Copy_u8XPos, u8 Copy_u8YPos) {
	u8 Local_u8DDRAMAddress;
	if (Copy_u8YPos == 0) {
		/*Check if in first line*/
		Local_u8DDRAMAddress = Copy_u8XPos;
	} else if (Copy_u8YPos == 1) {
		/*Check if in second line*/
		Local_u8DDRAMAddress = 0x40 + Copy_u8XPos;
	}

	/*Setbit number 7 for SetDDRAM Address command then send the command*/
	CLCD_voidSendCommand(Local_u8DDRAMAddress + 128);
}

void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern,
		u8 Copy_u8PatternNumber, u8 Copy_u8XPos, u8 Copy_u8YPos) {
	u8 Local_u8CGRamAddress, Local_u8Counter;

	/*1- calculate CGRAM address knowing that every pattern consumes 8 bytes*/
	Local_u8CGRamAddress = Copy_u8PatternNumber * 8;

	/*2-Send SET CGRAM address command to LCD with setting bit6 ,clearing bit7*/
	CLCD_voidSendCommand(Local_u8CGRamAddress + 64);

	/*3- write the pattern into CGRAM*/
	for (Local_u8Counter = 0; Local_u8Counter < 8; Local_u8Counter++) {
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Counter]);
	}
	/*4- Back to the DDRAM to display the special pattern*/
	CLCD_voidGotoXY(Copy_u8XPos, Copy_u8YPos);

	/*5- Display the special pattern*/
	CLCD_voidSendData(Copy_u8PatternNumber);
}


