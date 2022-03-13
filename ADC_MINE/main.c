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

u16 Local_u16ADC_reading1[2];
u16 Local_u16Analog_reading;
u16 Local_u16ADC_reading;
u8 Temperature;

void ISR_ADC(void);

void main(void) {

//	u8 Local_u8Dark = 70;
//	u8 Local_u8Max_light_intensity = 200;
//	u8 Local_u8Average = (u8) ((Local_u8Dark + Local_u8Max_light_intensity) / 2);

	PORT_voidInit();
	GIE_voidEnableGlobal();
	ADC_voidinit();

	CLCD_voidInit();

	u8 Local_u8ErrorState;

	u8 Local_u8Counter=0;

	while (1) {

		Local_u8ErrorState = ADC_u8StartConversionASynch(0,&Local_u16ADC_reading,&ISR_ADC);
		CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
		CLCD_voidSendNumber(Local_u8ErrorState);
		/*
		Local_u8ErrorState = ADC_u8StartChainConversionASynch(2, Local_u16ADC_reading1, &ISR_ADC);
		if(Local_u8ErrorState == OK) {
			Local_u8Counter++;
		}
		CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
		CLCD_voidSendNumber(Local_u8Counter);
	*/
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

	CLCD_voidWriteString("Called");

	//CLCD_voidGotoXY(0,0);
	//Local_u16Analog_reading = ((u32)Local_u16ADC_reading * 5000UL) / 256UL;
	//Temperature = Local_u16Analog_reading/10;
	//CLCD_voidSendNumber(Temperature);

	 /*
	CLCD_voidGotoXY(5,0);
	CLCD_voidSendNumber(Local_u16ADC_reading[1]);
    */

}

