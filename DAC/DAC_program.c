/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: HAL                  **********/
/**********      SWC: DAC    			     **********/
/**********      Date: 30-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "DAC_config.h"
#include "DAC_interface.h"

//reference = 5V
//resolution = 8 bits
//Step = reference / 2^resolution
//Analog = digital * step

//Minimum volt is 0 mV and maximum volt is 5000 mV;
u8 DAC_u8SetAnalogVolt(u16 Copy_u16AnalogVolt) {


	u8 Local_u8ErrorState = OK;
	u8 Local_u8Digital;

	if(Copy_u16AnalogVolt >= 0 && Copy_u16AnalogVolt < 5000) {

		Local_u8Digital = (u8)((256UL*Copy_u16AnalogVolt) / 5000UL ) ;
		DIO_u8SetPortValue(DAC_PORT, Local_u8Digital);
		return Local_u8Digital;

	} else if (Copy_u16AnalogVolt == 5000) {
		DIO_u8SetPortValue(DAC_PORT, 0b11111111);
	} else {
		Local_u8ErrorState = OUT_OF_RANGE;
	}

	return Local_u8ErrorState;






}
