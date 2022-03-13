#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"

#include "CLCD_interface.h"
#include "TactileButton_interface.h"
#include "SSD_interface.h"
#include "LED_interface.h"
#include "SWITCH_interface.h"
#include "Motor_interface.h"

u8 Global_u8EnableFlag = 1;
u8 Global_u8Enable = 0; // 1 for Enable 0 for Disable
u8 Global_u8LoginFlag = 0;
u8 Global_u8MotorPhaseFlag = 0;

Motor_T Motor_One = { DIO_u8PORTD, DIO_u8PIN6, DIO_u8PIN7 };


void INT0_ISR(void);

void main(void) {

	PORT_voidInit();
	CLCD_voidInit();
	GIE_voidEnableGlobal();
	EXTI_voidINT0Init();
	EXTI_u8INTSetCallBack(&INT0_ISR, EXTI_INT0);

	u8 Local_u8ID[3];
	u8 Local_u8Password[3];
	s8 Local_u8Counter = 0;
	s8 Local_u8NumberOfTries = 3;
	u8 Local_u8CorrectPasswordFlag = 0;

	SSD_T SSD_One = { CKATHODE, DIO_u8PORTB, DIO_u8PORTA, DIO_u8PIN3 };
	LED_T LED_One = { DIO_u8PORTA, DIO_u8PIN4, SOURCE };
	SWITCH_T Switch_One = { PULLUP, DIO_u8PORTA, DIO_u8PIN0 };
	SWITCH_T Switch_Two = { PULLUP, DIO_u8PORTA, DIO_u8PIN1 };
	SWITCH_T Switch_Three = { PULLUP, DIO_u8PORTA, DIO_u8PIN2 };
	while (1) {

		if (Global_u8Enable == 1) {

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

		} else if (Global_u8Enable == 0) {

			Global_u8EnableFlag = 1;
			CLCD_voidSendCommand(CLCD_TURN_DISPLAY_OFF);
			Motor_u8TurnOff(&Motor_One);
			SSD_Off(&SSD_One);
			LED_u8LED_OFF(&LED_One);
			Global_u8LoginFlag = 0;

		}

		while (Global_u8LoginFlag == 1) {

			CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
			CLCD_voidWriteString("Enter ID:");

			while (Local_u8Counter < 3) {

				if (SWITCH_u8GetState(&Switch_One) == PRESSED) {
					TactileButton_u8DebounceButton(Switch_One.Input_Port, Switch_One.Input_Pin);
					Local_u8ID[Local_u8Counter] = 1;
					CLCD_voidSendData('1');
					Local_u8Counter++;
				}
				if (SWITCH_u8GetState(&Switch_Two) == PRESSED) {
					TactileButton_u8DebounceButton(Switch_Two.Input_Port, Switch_Two.Input_Pin);
					Local_u8ID[Local_u8Counter] = 2;
					CLCD_voidSendData('2');

					Local_u8Counter++;
				}
				if (SWITCH_u8GetState(&Switch_Three) == PRESSED) {
					TactileButton_u8DebounceButton(Switch_Three.Input_Port, Switch_Three.Input_Pin);
					Local_u8ID[Local_u8Counter] = 3;
					CLCD_voidSendData('3');
					Local_u8Counter++;
				}

			}

			_delay_ms(250);
			CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
			CLCD_voidGotoXY(0, 0);
			CLCD_voidWriteString("Enter Password:");
			CLCD_voidGotoXY(0, 1);
			Local_u8Counter = 2;
			SSD_On(&SSD_One);
			SSD_u8SetNumber(&SSD_One, Local_u8NumberOfTries);

			do {
				while (Local_u8Counter >= 0) {

					if (SWITCH_u8GetState(&Switch_One) == PRESSED) {
						TactileButton_u8DebounceButton(Switch_One.Input_Port, Switch_One.Input_Pin);
						Local_u8Password[2 - Local_u8Counter] = 1;
						CLCD_voidSendData('1');
						Local_u8Counter--;
					}
					if (SWITCH_u8GetState(&Switch_Two) == PRESSED) {
						TactileButton_u8DebounceButton(Switch_Two.Input_Port, Switch_Two.Input_Pin);
						Local_u8Password[2 - Local_u8Counter] = 2;
						CLCD_voidSendData('2');

						Local_u8Counter--;
					}
					if (SWITCH_u8GetState(&Switch_Three) == PRESSED) {
						TactileButton_u8DebounceButton(Switch_Three.Input_Port, Switch_Three.Input_Pin);
						Local_u8Password[2 - Local_u8Counter] = 3;
						CLCD_voidSendData('3');
						Local_u8Counter--;
					}

				}

				for (Local_u8Counter = 0; Local_u8Counter < 3; Local_u8Counter++) {
					if (Local_u8ID[Local_u8Counter] == Local_u8Password[(2 - Local_u8Counter)]) {

						Local_u8CorrectPasswordFlag = 1;

					} else {
						Local_u8CorrectPasswordFlag = 0;
					}
				}

				if (Local_u8CorrectPasswordFlag == 0) {
					Local_u8NumberOfTries--;
					SSD_u8SetNumber(&SSD_One, Local_u8NumberOfTries);
					Local_u8Counter = 2;

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
			SSD_Off(&SSD_One);
			_delay_ms(250);
			CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);

			if (Local_u8NumberOfTries == 0) {
				Global_u8Enable = 0;
				CLCD_voidWriteString("Goodbye.");
				_delay_ms(1000);
				CLCD_voidSendCommand(CLCD_TURN_DISPLAY_OFF);

			} else if (Local_u8CorrectPasswordFlag == 1) {

				Global_u8MotorPhaseFlag = 1;
				CLCD_voidWriteString("Welcome ");
				CLCD_voidSendNumber(Local_u8ID[0]);
				CLCD_voidSendNumber(Local_u8ID[1]);
				CLCD_voidSendNumber(Local_u8ID[2]);
				CLCD_voidSendData('!');
				LED_u8LED_ON(&LED_One);
				while (Global_u8MotorPhaseFlag == 1) {

					Motor_u8RotateClockwise(&Motor_One);
					_delay_ms(3000);
					Motor_u8RotateAntiClockwise(&Motor_One);
					_delay_ms(3000);
/*
					if(Global_u8Enable == 1) {
					Motor_u8RotateClockwise(&Motor_One);
					} else {
						break;
					}
					_delay_ms(3000);
					if(Global_u8Enable == 1) {
					Motor_u8RotateAntiClockwise(&Motor_One);
					} else {
						break;
					}
					_delay_ms(3000);
					*/
				}
				if (Global_u8Enable == 0) {


						}

			}

		}


	}

}

void INT0_ISR(void) {

	if (Global_u8EnableFlag == 1 && Global_u8LoginFlag == 0) {

		if(Global_u8Enable == 1 && Global_u8MotorPhaseFlag == 1) {
			Global_u8Enable = 0;
			Global_u8MotorPhaseFlag = 0;
			Motor_u8TurnOff(&Motor_One);CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
			CLCD_voidWriteString("Thank You :)");
			_delay_ms(1000);
		} else if (Global_u8Enable == 0 ) {
			Global_u8Enable = 1;
		}

	}

}

