/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: ADC      			     **********/
/**********      Date: 17-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


void ADC_voidinit(void);

u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel, u16* Copy_pu16Result);

/*
 *
 * Preconditions: Enable the global interrupt before calling this function */
u8 ADC_u8StartConversionASynch(u8 Copy_u8Channel, u16* Copy_pu16Result, void (*Copy_pvNotificationFunction)(void));

u8 ADC_u8StartChainConversionASynch(u8 Copy_u8NumberOfConversions,u16* Copy_pu16Result, void(*Copy_pvNotificationFunction)(void));

u8 ADC_u8SetNotificationFunction(void (*Copy_pvNotificationFunction)(void));


#endif 
