/*
 * main.c
 *
 *  Created on: 14 Oct 2020
 *      Author: es-RaghadAly2023
 */

#include <util/delay.h>

#include "STD_TYPES.h"
#include "Mapping_interface.h"

#include "PORT_interface.h"
#include "ADC_interface.h"
#include "TIMER_interface.h"

#include "CLCD_interface.h"
#include "SERVO_interface.h"

void main(void) {

	ADC_voidInit();
	PORT_voidInit();
	Timer1_voidInit();
	CLCD_voidInit();

	u16 Local_u16Lm35Reading;
	u16 Local_u16AnalogValue;
	u16 Local_u16LDR_Reading;
	u8 Local_u8Temperature;
	u16 Local_u16Volt;
	MAP_T Local_LightToOnTime= {26,240,0,100};
	MAP_T Local_VoltToAngle = { 0, 255, 0, 180 };
	MAP_T Local_VoltToOnTime = {0,255,0,100};
	MAP_T Local_TemperatureToOnTime = {25,40,0,100};
	MAP_T Local_FlexToAngle = { 50 , 120 , 0 , 180};
	u8 Local_u8Angle;
	u8 Local_u8OnTime;

	CLCD_voidSendNumber(Local_u8Angle);

	while (1) {
		ADC_u8StartSingleConversionSynch(0, &Local_u16Volt);
		CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);
		CLCD_voidSendNumber(Local_u16Volt);
		//Local_u16AnalogValue = ((u32)Local_u16Lm35Reading * 5000UL) / 256UL;
		//Local_u8Temperature = Local_u16AnalogValue/10;
		Local_u8Angle = (u8) (Map_s32(&Local_FlexToAngle, Local_u16Volt));
		SERVO_u8SetAngle(0, Local_u8Angle);
		_delay_ms(250);
	}


}
