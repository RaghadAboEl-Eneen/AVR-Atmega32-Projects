/*
 * main.c
 *
 *  Created on: 22 Oct 2020
 *      Author: es-RaghadAly2023
 */
#include <util/delay.h>

#include "STD_TYPES.h"
#include "Mapping_interface.h"

#include "DIO_interface.h"
#include "USART_interface.h"
#include "PORT_interface.h"
#include "TIMER_interface.h"
#include "GIE_interface.h"
#include "ADC_interface.h"
#include "TWI_interface.h"

#include "SERVO_interface.h"
#include "SSD_interface.h"
#include "Buzzer_interface.h"
#include "EEPROM_interface.h"

#define ACTIVE			1
#define INACTIVE		0

#define CORRECT			1
#define INCORRECT		0



MAP_T TemperatureToOnTime = { 10, 30, 0, 100 };
MAP_T LightToOnTime = { 7, 200, 0, 100 };

static u8 Percentage;
static volatile u8 MelodyCounter = 1;

static u16 TEMPERATURE_u16ADC_Reading = 0;
static u16 TEMPERATURE_u16AnalogValue = 0;

static u8 WelcomePhaseFlag = ACTIVE;

static u8 IdPhaseFlag = INACTIVE;
static u8 IdCheckPhaseFlag = INACTIVE;
static u8 PasswordPhaseFlag = INACTIVE;
static u8 PasswordCheckPhaseFlag = INACTIVE;

static u8 MainMenuOptionsPhase = INACTIVE;
static u8 MainMenuPhaseFlag = INACTIVE;

static u8 FanControlPhaseFlag = INACTIVE;

static u8 DoorControlPhaseFlag = INACTIVE;

static u8 LightControlPhaseFlag = INACTIVE;
static u8 LightMapPhaseFlag = INACTIVE;

static u8 BuzzerControlPhaseFlag = INACTIVE;
static u8 MusicPhaseFlag = INACTIVE;

static u8 TemperatureMapPhaseFlag = INACTIVE;

static u8 SystemClosePhaseFlag = INACTIVE;

static u8 ErrorPhaseFlag = INACTIVE;

static u8 OptionSelect;
static u8 Temperature;
static u8 StringSize;



void MainMenuOptionsISR(void);
void FanOptionsISR(void);
void DoorOptionsISR(void);
void LightOptionsISR(void);
void ADC_TemperatureISR(void);
void ADC_LightISR(void);
void MusicOptionsISR(void);

void main(void) {

	ADC_voidInit();
	TWI_voidInitMaster(0);
	PORT_voidInit();
	USART_voidInit();
	Timer0_voidInit();
	Timer1_voidInit();
	Timer2_voidInit();
	GIE_voidEnableGlobal();

	SSD_T SSD_One = { CKATHODE, DIO_u8PORTC, DIO_u8PORTA, DIO_u8PIN6 };
	u16 Local_u16Melody[] = { F, A, B, PAUSE, F, A, B, PAUSE, F, A, B, PAUSE, PAUSE, B, PAUSE, B, G, E, PAUSE, PAUSE, D, E, G, E, PAUSE, F, A, B, PAUSE, F, A, B, F, A, B, PAUSE, B, PAUSE, B, G, PAUSE, B, G, D, E, PAUSE, D, E, F, PAUSE, G, A, B, PAUSE, B, E, PAUSE, F, G, A, PAUSE, B, A, B, PAUSE, D, E, F, PAUSE, G, END };
	u16 Local_u16Twinkle[] = { G, G, D, D, E, E, D, PAUSE, C, C, B, B, A, A, G, PAUSE, D, D, C, C, B, B, A, PAUSE, D, D, C, C, B, B, A, PAUSE, G, G, D, D, E, E, D, PAUSE, C, C, B, B, A, A, G, END};
	u8 Local_u8NumberOfTries;
	u8 Local_u8UsernameState;
	u8 Local_u8PasswordState;


	u8 Local_u8ID[20];
	u8 Local_u8Password[20];
	u8 Local_u8NameCounter;
	u8 Local_u8LetterCounter;
	u8 Local_u8Size;

	const char * Local_pchUsernames[10] = { "nada", "layla", "aly", "manar", "reem", "farah", "ahmed", "salim", "nour", "merna" };
	const char * Local_pchPasswords[10] = { "hcpfgj7hv", "gpl6q367u", "yq3x", "steu7e1q", "e3wum", "afra5q", "ltuwb", "vJf7h8buk", "nbw1hh", "fz2" };

	while (1) {



		if (MusicPhaseFlag == ACTIVE) {

			Buzzer_u16PlayTone(Local_u16Melody[MelodyCounter], 200);
			MelodyCounter++;

			if (Local_u16Melody[MelodyCounter] == 0) {
				MelodyCounter = 1;
			}

		}

		if (WelcomePhaseFlag == ACTIVE) {

			WelcomePhaseFlag = INACTIVE;
			USART_u8SendStringSynchronous("Welcome");
			USART_u8SendData('\n');
			Local_u8NumberOfTries = 3;
			IdPhaseFlag = ACTIVE;

		}

		if (IdPhaseFlag == ACTIVE) {
			IdPhaseFlag = INACTIVE;
			USART_u8SendStringSynchronous("Please enter your username");
			USART_u8SendData('\n');
			StringSize = USART_u8ReceiveStringSynchronous((char*) Local_u8ID);
			USART_u8SendStringSynchronous((char*) Local_u8ID);
			IdCheckPhaseFlag = ACTIVE;
		}

		if (IdCheckPhaseFlag == ACTIVE) {

			IdCheckPhaseFlag = INACTIVE;

			for (Local_u8NameCounter = 0; Local_u8NameCounter < 10; Local_u8NameCounter++) {

				Local_u8Size = 0;
				Local_u8LetterCounter = 0;

				while (Local_pchUsernames[Local_u8NameCounter][Local_u8LetterCounter] != '\0') {
					Local_u8Size++;
					Local_u8LetterCounter++;
				}

				if (Local_u8Size == StringSize) {

					for (Local_u8LetterCounter = 0; Local_u8LetterCounter < Local_u8Size; Local_u8LetterCounter++) {

						if ((u8) (Local_u8ID[Local_u8LetterCounter]) == (u8) (Local_pchUsernames[Local_u8NameCounter][Local_u8LetterCounter])) {
							Local_u8UsernameState = CORRECT;
						} else {
							Local_u8UsernameState = INCORRECT;
						}

					}

					if (Local_u8UsernameState == CORRECT) {
						USART_u8SendStringSynchronous("Hello ");
						USART_u8SendStringSynchronous((char*) Local_u8ID);
						USART_u8SendData('\n');
						PasswordPhaseFlag = ACTIVE;
						break;
					}

				}

			}

			if (Local_u8UsernameState == INCORRECT) {
				USART_u8SendStringSynchronous("Invalid Username");
				IdPhaseFlag = ACTIVE;
			}

		}

		if (PasswordPhaseFlag == ACTIVE) {
			PasswordPhaseFlag = INACTIVE;
			SSD_u8On(&SSD_One);
			SSD_u8SetNumber(&SSD_One, Local_u8NumberOfTries);
			USART_u8SendStringSynchronous("Please enter your password");
			USART_u8SendData('\n');
			StringSize = USART_u8ReceiveStringSynchronous((char*) Local_u8Password);
			USART_u8SendStringSynchronous((char*) Local_u8Password);
			PasswordCheckPhaseFlag = ACTIVE;
		}

		if (PasswordCheckPhaseFlag == ACTIVE) {

			PasswordCheckPhaseFlag = INACTIVE;

			Local_u8Size = 0;
			Local_u8LetterCounter = 0;

			while (Local_pchPasswords[Local_u8NameCounter][Local_u8LetterCounter] != '\0') {
				Local_u8Size++;
				Local_u8LetterCounter++;
			}

			if (Local_u8Size == StringSize) {

				for (Local_u8LetterCounter = 0; Local_u8LetterCounter < Local_u8Size; Local_u8LetterCounter++) {

					if ((u8) (Local_pchPasswords[Local_u8NameCounter][Local_u8LetterCounter]) == (u8) (Local_u8Password[Local_u8LetterCounter])) {

						Local_u8PasswordState = CORRECT;
					} else {
						Local_u8PasswordState = INCORRECT;
						break;
					}

				}
			} else {
				Local_u8PasswordState = INCORRECT;
			}

			Local_u8NumberOfTries--;

			if (Local_u8PasswordState == CORRECT) {
				MainMenuOptionsPhase = ACTIVE;
				SSD_u8Off(&SSD_One);
				USART_u8SendStringSynchronous("Welcome ");
				USART_u8SendStringSynchronous((char*) Local_u8ID);

			} else if (Local_u8PasswordState == INCORRECT && Local_u8NumberOfTries != 0) {

				SSD_u8SetNumber(&SSD_One, Local_u8NumberOfTries);
				USART_u8SendStringSynchronous("Password Incorrect, Please try again");
				USART_u8SendData('\n');
				PasswordPhaseFlag = ACTIVE;

			} else if (Local_u8PasswordState == INCORRECT && Local_u8NumberOfTries == 0) {

				USART_u8SendStringSynchronous("Out of tries , Goodbye");
				USART_u8SendData('\n');

				SSD_u8SetNumber(&SSD_One, 3);
				_delay_ms(1000);
				SSD_u8SetNumber(&SSD_One, 2);
				_delay_ms(1000);
				SSD_u8SetNumber(&SSD_One, 1);
				_delay_ms(1000);
				SSD_u8SetNumber(&SSD_One, 0);
				_delay_ms(1000);

				SSD_u8Off(&SSD_One);

			}

			/*
			 for (Local_u8Counter = 0; Local_u8Counter < 4; Local_u8Counter++) {

			 if (Local_u8ID[Local_u8Counter] == Local_u8Password[3 - Local_u8Counter]) {

			 Local_u8PasswordState = CORRECT;

			 } else {
			 Local_u8PasswordState = INCORRECT;
			 break;
			 }

			 }

			 Local_u8NumberOfTries--;

			 if (Local_u8PasswordState == CORRECT) {

			 MainMenuOptionsPhase = ACTIVE;
			 SSD_u8Off(&SSD_One);
			 USART_u8SendStringSynchronous("Welcome ");
			 USART_u8SendData((Local_u8ID[0]));
			 USART_u8SendData((Local_u8ID[1]));
			 USART_u8SendData((Local_u8ID[2]));
			 USART_u8SendData((Local_u8ID[3]));

			 } else if (Local_u8PasswordState == INCORRECT && Local_u8NumberOfTries != 0) {

			 SSD_u8SetNumber(&SSD_One, Local_u8NumberOfTries);
			 USART_u8SendStringSynchronous("Password Incorrect, Please try again");
			 USART_u8SendData('\n');
			 PasswordPhaseFlag = ACTIVE;

			 } else if (Local_u8PasswordState == INCORRECT && Local_u8NumberOfTries == 0) {

			 USART_u8SendStringSynchronous("Out of tries , Goodbye");
			 USART_u8SendData('\n');

			 SSD_u8SetNumber(&SSD_One, 3);
			 _delay_ms(1000);
			 SSD_u8SetNumber(&SSD_One, 2);
			 _delay_ms(1000);
			 SSD_u8SetNumber(&SSD_One, 1);
			 _delay_ms(1000);
			 SSD_u8SetNumber(&SSD_One, 0);
			 _delay_ms(1000);

			 SSD_u8Off(&SSD_One);

			 }
			 */

		}

		if (MainMenuOptionsPhase == ACTIVE) {

			MainMenuOptionsPhase = INACTIVE;

			USART_u8SendStringSynchronous("Choose one of the following options:");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("1 for fan control");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("2 for door control");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("3 for light control");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("4 to play music");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("5 to check the temperature");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("6 to close the system");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("7 to hear the options again");
			USART_u8SendData('\n');

			MainMenuPhaseFlag = ACTIVE;

		}

		if (MainMenuPhaseFlag == ACTIVE) {
			MainMenuPhaseFlag = INACTIVE;
			USART_u8SendStringSynchronous("Press the button and say an option");
			USART_u8SendData('\n');
			USART_u8ReceiveBufferAsynchronous(&OptionSelect, 1, &MainMenuOptionsISR);

		}

		if (FanControlPhaseFlag == ACTIVE) {
			FanControlPhaseFlag = INACTIVE;

			USART_u8SendStringSynchronous("Choose one of the following options:");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("1 to open the fan");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("2 to close the fan");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("3 to adjust fan speed to temperature");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("4 to return to the main menu");
			USART_u8SendData('\n');

			USART_u8ReceiveBufferAsynchronous(&OptionSelect, 1, &FanOptionsISR);


		}

		if (DoorControlPhaseFlag == ACTIVE) {
			DoorControlPhaseFlag = INACTIVE;

			USART_u8SendStringSynchronous("Choose one of the following options:");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("1 to open the door");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("2 to close the door");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("3 to return to the main menu");
			USART_u8SendData('\n');

			USART_u8ReceiveBufferAsynchronous(&OptionSelect, 1, &DoorOptionsISR);

		}

		if (LightControlPhaseFlag == ACTIVE) {
			LightControlPhaseFlag = INACTIVE;

			USART_u8SendStringSynchronous("Choose one of the following options:");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("1 to open the lights");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("2 to close the lights");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("3 to adjust light intensity");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("4 to return to the main menu");
			USART_u8SendData('\n');

			USART_u8ReceiveBufferAsynchronous(&OptionSelect, 1, &LightOptionsISR);


		}

		if (BuzzerControlPhaseFlag == ACTIVE) {
			BuzzerControlPhaseFlag = INACTIVE;

			USART_u8SendStringSynchronous("Choose one of the following options:");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("1 to play music");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("2 to stop playing");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("3 to return to main menu");
			USART_u8SendData('\n');

			USART_u8ReceiveBufferAsynchronous(&OptionSelect, 1, &MusicOptionsISR);


		}

		if (SystemClosePhaseFlag == ACTIVE) {
			SystemClosePhaseFlag = INACTIVE;
			MusicPhaseFlag = INACTIVE;
			Timer0_u8SetCompareMatchMode(DISABLE);
			Timer1_voidDisableFastPWM(CHANNEL_A);
			Timer2_u8SetCompareMatchMode(DISABLE);
			USART_u8SendStringSynchronous("Goodbye");
		}

		if (ErrorPhaseFlag == ACTIVE) {
			ErrorPhaseFlag = INACTIVE;
			USART_u8SendStringSynchronous("Please say a valid option");
			USART_u8SendData('\n');
			MainMenuPhaseFlag = ACTIVE;
		}

		if (TemperatureMapPhaseFlag == ACTIVE) {
			TemperatureMapPhaseFlag = INACTIVE;
			ADC_u8StartSingleConversionAsynch(0, &TEMPERATURE_u16ADC_Reading, &ADC_TemperatureISR);
		}

		if (LightMapPhaseFlag == ACTIVE) {
			LightMapPhaseFlag = INACTIVE;
			ADC_u8StartSingleConversionAsynch(1, &TEMPERATURE_u16ADC_Reading, &ADC_LightISR);

		}

	}

}

void LightOptionsISR(void) {

	USART_u8SendData(OptionSelect);


	switch (OptionSelect) {
	case '1':
		Timer0_voidSetOnTime(100);
		break;
	case '2':
		Timer0_u8SetCompareMatchMode(DISABLE);
		break;
	case '3':
		LightMapPhaseFlag = ACTIVE;
		break;
	case '4':
		MainMenuPhaseFlag = ACTIVE;
		break;
	default:
		ErrorPhaseFlag = ACTIVE;
		break;
	}
	MainMenuPhaseFlag = ACTIVE;

}


void MainMenuOptionsISR(void) {

	USART_u8SendData(OptionSelect);

	switch (OptionSelect) {
	case '1':
		FanControlPhaseFlag = ACTIVE;
		break;
	case '2':
		DoorControlPhaseFlag = ACTIVE;
		break;
	case '3':
		LightControlPhaseFlag = ACTIVE;
		break;
	case '4':
		BuzzerControlPhaseFlag = ACTIVE;
		break;
	case '6':
		SystemClosePhaseFlag = ACTIVE;
		break;
	case '7':
		MainMenuOptionsPhase = ACTIVE;
		break;
	default:
		ErrorPhaseFlag = ACTIVE;
		break;
	}

}

void FanOptionsISR(void) {

	USART_u8SendData(OptionSelect);


	switch (OptionSelect) {

	case '1':
		Timer2_voidSetOnTime(100);
		MainMenuPhaseFlag = ACTIVE;

		break;
	case '2':
		Timer2_u8SetCompareMatchMode(DISABLE);
		MainMenuPhaseFlag = ACTIVE;

		break;
	case '3':
		TemperatureMapPhaseFlag = ACTIVE;
		MainMenuPhaseFlag = ACTIVE;

		break;
	case '4':
		MainMenuPhaseFlag = ACTIVE;
		break;
	default:
		ErrorPhaseFlag = ACTIVE;
		break;
	}

}

void ADC_TemperatureISR(void) {

	TEMPERATURE_u16AnalogValue = ((u32) TEMPERATURE_u16ADC_Reading * 5000UL) / 256UL;
	Temperature = TEMPERATURE_u16AnalogValue / 10;

	Percentage = Map_s32(&TemperatureToOnTime, Temperature);
	if (Percentage == 0) {
		Timer2_u8SetCompareMatchMode(DISABLE);
	} else {
		Timer2_voidSetOnTime(Percentage);
	}

}

void DoorOptionsISR(void) {

	USART_u8SendData(OptionSelect);


	switch (OptionSelect) {
	case '1':
		SERVO_u8SetAngle(CHANNEL_A, 90);
		MainMenuPhaseFlag = ACTIVE;
		break;
	case '2':
		SERVO_u8SetAngle(CHANNEL_A, 0);
		MainMenuPhaseFlag = ACTIVE;
		break;
	case '3':
		MainMenuPhaseFlag = ACTIVE;
		break;
	default:
		ErrorPhaseFlag = ACTIVE;
		break;
	}

}

void ADC_LightISR(void) {

	Percentage = Map_s32(&LightToOnTime, TEMPERATURE_u16ADC_Reading);
	if (Percentage == 100) {
		Timer0_u8SetCompareMatchMode(DISABLE);
	} else {
		Timer0_voidSetOnTime(100 - Percentage);
	}
}

void MusicOptionsISR(void) {

	USART_u8SendData(OptionSelect);

	switch (OptionSelect) {

	case '1':
		MusicPhaseFlag = ACTIVE;
		MelodyCounter = 1;
		MainMenuPhaseFlag = ACTIVE;
		break;
	case '2':
		MusicPhaseFlag = INACTIVE;
		MainMenuPhaseFlag = ACTIVE;
		break;
	case '3':
		MainMenuPhaseFlag = ACTIVE;
		break;
	default:
		ErrorPhaseFlag = ACTIVE;
		break;

	}

}

