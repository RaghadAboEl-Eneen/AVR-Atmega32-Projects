#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Mapping_interface.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"
#include "ADC_interface.h"

#include "CLCD_interface.h"
#include "TactileButton_interface.h"
#include "SSD_interface.h"
#include "LED_interface.h"
#include "SWITCH_interface.h"
#include "Motor_interface.h"
#include "Keypad_interface.h"

u8 Global_u8EnableFlag = 1;
u8 Global_u8Enable = 0; // 1 for Enable 0 for Disable
u8 Global_u8LoginFlag = 0;
u8 Global_u8MotorPhaseFlag = 0;
u16 Local_u16ADC_readings[2];
u8 NeededChannels[2] = { 0, 1 };
u8 Temperature;
u16 Local_u16Analog_reading;

Motor_T Motor_One = { DIO_u8PORTA, DIO_u8PIN7, DIO_u8PIN7 };

void INT0_ISR(void);
void ISR_ADC(void);

Chain_T Chain_One = { 2, Local_u16ADC_readings, NeededChannels, &ISR_ADC };

void main(void) {

	PORT_voidInit();
	CLCD_voidInit();
	GIE_voidEnableGlobal();
	ADC_voidInit();
	//EXTI_voidINT0Init();
	//EXTI_u8INTSetCallBack(&INT0_ISR, EXTI_INT0);

	u8 Local_u8ID[4];
	u8 Local_u8Password[4];
	s8 Local_u8Counter = 0;
	s8 Local_u8NumberOfTries = 3;
	u8 Local_u8CorrectPasswordFlag = 0;
	u8 Local_u8EnteredKey;
	s32 Local_s32MapResult;
	u8 Local_u8NumberOfLeds = 1;
	SSD_T SSD_One = { CKATHODE, DIO_u8PORTB, DIO_u8PORTA, DIO_u8PIN5 };
	LED_T LED_All = { DIO_u8PORTA, DIO_u8PIN6, SOURCE };
	MAP_T Map = {0,210,0,8};
	//SWITCH_T Switch_One = { PULLUP, DIO_u8PORTC, DIO_u8PIN4 };
	//SWITCH_T Switch_Two = { PULLUP, DIO_u8PORTC, DIO_u8PIN5 };
	//SWITCH_T Switch_Three = { PULLUP, DIO_u8PORTC, DIO_u8PIN6 };
	//SWITCH_T Switch_Four = { PULLUP, DIO_u8PORTC, DIO_u8PIN7 };

	while (1) {

		//	if (Global_u8Enable == 1) {

		Global_u8MotorPhaseFlag = 0;

		Local_u8NumberOfTries = 3;
		Local_u8Counter = 0;
		Local_u8CorrectPasswordFlag = 0;
		Global_u8EnableFlag = 0;
		Global_u8LoginFlag = 1;
		CLCD_voidSendCommand(CLCD_TURN_DISPLAY_ON);
		CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
		CLCD_voidGotoXY(4, 0);
		CLCD_voidWriteString("Welcome!");
		_delay_ms(3000);
		/*
		 } else if (Global_u8Enable == 0) {

		 Global_u8EnableFlag = 1;
		 CLCD_voidSendCommand(CLCD_TURN_DISPLAY_OFF);
		 Motor_u8TurnOff(&Motor_One);
		 SSD_Off(&SSD_One);
		 LED_u8LED_OFF(&LED_All);
		 Global_u8LoginFlag = 0;

		 }
		 */
		//while (Global_u8LoginFlag == 1) {
		CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
		CLCD_voidWriteString("Enter ID:");

		while (Local_u8Counter < 4) {

			Local_u8EnteredKey = Keypad_u8GetPressedKey();
			if (Local_u8EnteredKey != 0) {
				Local_u8ID[Local_u8Counter] = Local_u8EnteredKey;
				CLCD_voidSendNumber(Local_u8EnteredKey);
				Local_u8Counter++;
			}


		}

		_delay_ms(250);
		CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
		CLCD_voidGotoXY(0, 0);
		CLCD_voidWriteString("Enter Password:");
		CLCD_voidGotoXY(0, 1);
		Local_u8Counter = 3;
		LED_u8LED_ON(&LED_All);
		SSD_On(&SSD_One);
		SSD_u8SetNumber(&SSD_One, Local_u8NumberOfTries);

		do {
			while (Local_u8Counter >= 0) {

				Local_u8EnteredKey = Keypad_u8GetPressedKey();
				if (Local_u8EnteredKey != 0) {
					Local_u8Password[3 - Local_u8Counter] = Local_u8EnteredKey;
					CLCD_voidSendNumber(Local_u8EnteredKey);
					 _delay_ms(100);
					CLCD_voidGotoXY(3 - Local_u8Counter, 1);
					CLCD_voidSendData('*');
					Local_u8Counter--;
				}


			}

			for (Local_u8Counter = 0; Local_u8Counter < 4; Local_u8Counter++) {
				if (Local_u8ID[Local_u8Counter] == Local_u8Password[(3 - Local_u8Counter)]) {

					Local_u8CorrectPasswordFlag = 1;

				} else {
					Local_u8CorrectPasswordFlag = 0;
				}
			}

			if (Local_u8CorrectPasswordFlag == 0) {
				Local_u8NumberOfTries--;
				SSD_u8SetNumber(&SSD_One, Local_u8NumberOfTries);
				Local_u8Counter = 3;

				if (Local_u8NumberOfTries != 0) {
					_delay_ms(250);
					CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
					CLCD_voidWriteString("Try Again");
					_delay_ms(1000);
					CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
					CLCD_voidWriteString("Enter Password:");
					CLCD_voidGotoXY(0, 1);
				}

			}

		}
		while (Local_u8NumberOfTries > 0 && Local_u8CorrectPasswordFlag == 0);

		Global_u8LoginFlag = 0;
		Global_u8EnableFlag = 1;
		_delay_ms(250);
		CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);

		if (Local_u8NumberOfTries == 0) {
			SSD_On(&SSD_One);
			Global_u8Enable = 0;
			CLCD_voidWriteString("Goodbye.");
			SSD_u8SetNumber(&SSD_One, 3);
			_delay_ms(1000);
			SSD_u8SetNumber(&SSD_One, 2);
			_delay_ms(1000);
			SSD_u8SetNumber(&SSD_One, 1);
			_delay_ms(1000);
			CLCD_voidSendCommand(CLCD_TURN_DISPLAY_OFF);
			SSD_Off(&SSD_One);
			_delay_ms(3000);


		} else if (Local_u8CorrectPasswordFlag == 1) {

			SSD_Off(&SSD_One);
			Global_u8MotorPhaseFlag = 1;
			CLCD_voidWriteString("Welcome ");
			CLCD_voidSendNumber(Local_u8ID[0]);
			CLCD_voidSendNumber(Local_u8ID[1]);
			CLCD_voidSendNumber(Local_u8ID[2]);
			CLCD_voidSendNumber(Local_u8ID[3]);
			CLCD_voidSendData('!');
			_delay_ms(1000);
			LED_u8LED_OFF(&LED_All);

			while (Global_u8MotorPhaseFlag == 1) {
				Local_u8NumberOfLeds = 1;
				ADC_u8StartChainConversionASynch(&Chain_One);

				if(Temperature >= 29) {
					Motor_u8TurnOn(&Motor_One);
				} else {
					Motor_u8TurnOff(&Motor_One);
				}

				Local_s32MapResult = Map_s32(&Map, (s32) Chain_One.Results[1]);
				CLCD_voidGotoXY(7,1);
				CLCD_voidSendNumber(8 - Local_s32MapResult);

				if(Local_s32MapResult == 0 ) {
					Local_u8NumberOfLeds = 255;
				} else {
				for(Local_u8Counter = 0 ; Local_u8Counter < 8-Local_s32MapResult ; Local_u8Counter++) {

					Local_u8NumberOfLeds *=2;

					}
				Local_u8NumberOfLeds--;
				}
				DIO_u8SetPortValue(DIO_u8PORTB, (Local_u8NumberOfLeds));
				_delay_ms(1000);
			}
		}

	}

}

void INT0_ISR(void) {

	if (Global_u8EnableFlag == 1 && Global_u8LoginFlag == 0) {

		if (Global_u8Enable == 1 && Global_u8MotorPhaseFlag == 1) {
			Global_u8Enable = 0;
			Global_u8MotorPhaseFlag = 0;
			Motor_u8TurnOff(&Motor_One);
			CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
			CLCD_voidWriteString("Thank You :)");
			_delay_ms(1000);
		} else if (Global_u8Enable == 0) {
			Global_u8Enable = 1;
		}

	}

}

void ISR_ADC(void) {

	CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
	CLCD_voidGotoXY(0, 0);
	CLCD_voidWriteString("Temperature: ");
	Local_u16Analog_reading = ((u32) Chain_One.Results[0] * 5000UL) / 256UL;
	Temperature = Local_u16Analog_reading / 10;
	CLCD_voidSendNumber(Temperature);
	CLCD_voidWriteString("C");

	CLCD_voidGotoXY(0, 1);
	CLCD_voidWriteString("Light: ");
	//CLCD_voidSendNumber(Chain_One.Results[1]);

}

