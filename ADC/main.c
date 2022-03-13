/*
 * main.c
 *
 *  Created on: Sep 17, 2020
 *      Author: es-RaghadAly2023
 */
#include <util/delay.h>

#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "GIE_interface.h"
#include "ADC_interface.h"

#include "CLCD_interface.h"

u16 Local_u16ADC_readings[2];
u8 NeededChannels[2] = { 0, 5 };
u16 Local_u16Analog_reading;
u8 Temperature;
Chain_T Chain_One = { 2, Local_u16ADC_readings, NeededChannels, &ISR_ADC };

void ISR_ADC(void);

void main(void) {

//	u8 Local_u8Dark = 70;
//	u8 Local_u8Max_light_intensity = 200;
//	u8 Local_u8Average = (u8) ((Local_u8Dark + Local_u8Max_light_intensity) / 2);

	PORT_voidInit();
	GIE_voidEnableGlobal();
	ADC_voidInit();

	CLCD_voidInit();

	u8 Local_u8ErrorState;
	while (1) {

		Local_u8ErrorState = ADC_u8StartChainConversionASynch(&Chain_One);

		/*
		 // LM35 is connected to channel 0
		 Local_u8ErrorState = ADC_u8StartConversionSynch(0, &Local_u16ADC_reading);

		 Local_u16Analog_reading = ((u32)Local_u16ADC_reading * 5000UL) / 256UL;

		 // LM35 changes 10mv  with every 1 degree celsius change.
		 Temperature = Local_u16Analog_reading/10;
		 CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
		 CLCD_voidGotoXY(0,0);
		 CLCD_voidSendNumber(Temperature);
		 _delay_ms(1000);


		 if(ADC_reading  < Local_average ) {
		 DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN7, DIO_u8PIN_HIGH);
		 } else if (ADC_reading > Local_average) {
		 DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN7, DIO_u8PIN_LOW);
		 }

		 */

	}

}

void ISR_ADC(void) {

	CLCD_voidGotoXY(0, 0);
	CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
	Local_u16Analog_reading = ((u32) Chain_One.Results[0] * 5000UL) / 256UL;
	Temperature = Local_u16Analog_reading / 10;
	CLCD_voidSendNumber(Temperature);

	CLCD_voidGotoXY(5, 0);
	CLCD_voidSendNumber(Chain_One.Results[1]);

}

