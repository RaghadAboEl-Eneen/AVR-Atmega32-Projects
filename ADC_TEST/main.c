#include "STD_TYPES.h"

#include "ADC_interface.h"

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "GIE_interface.h"

#include "CLCD_interface.h"
#include <util/delay.h>


void ISR_ADC(void);

u16 ADC_READINGS[2];
u16 Local_u16Analog_reading;
u8 Temperature;
void main(void)
{
	PORT_voidInit();
	GIE_voidEnableGlobal();
	ADC_voidInit();

	CLCD_voidInit();

	u8 Local_u8ErrorState;
	u16 Local_u16ADC_reading;
	u8 NeededChannels[2] = {0,1};

	while(1) {

		Local_u8ErrorState = ADC_u8StartChainConversionASynch(2, ADC_READINGS,NeededChannels, &ISR_ADC);

	}
}

void ISR_ADC(void) {


	CLCD_voidGotoXY(0,0);
	Local_u16Analog_reading = ((u32)ADC_READINGS[0] * 5000UL) / 256UL;
	Temperature = Local_u16Analog_reading/10;
	CLCD_voidWriteNumber(Temperature);

	CLCD_voidGotoXY(5,0);
	CLCD_voidWriteNumber(ADC_READINGS[1]);


}
