/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: ADC      			     **********/
/**********      Date: 17-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_config.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_register.h"

/*static allows global variable to switch from global scope to file scope*/
static u16* ADC_pu16ConversionResult = NULL;

/*Global pointer to function to carry the notification function called by ISR*/
static void (*ADC_pvNotificationFunction)(void) = NULL;

/*Global flag to indicate the ADC State (busy or idle)*/
static u8 ADC_u8State = IDLE;

static u8 ADC_u8Counter = 0;

static u8 ADC_u8ChainConversionFlag = NOT_WORKING;

static u8 ADC_u8NumberOfConversions;

void ADC_voidinit(void) {
	//Set AVCC reference voltage
	SET_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);

	//Activate left adjust result (8 bit resolution)
	SET_BIT(ADMUX, ADMUX_ADLAR);

	ADCSRA &= ADC_u8CHANNEL_MASK;
	ADCSRA |= ADC_u8PRESCALER;

	//Enable ADC peripheral
	SET_BIT(ADCSRA, ADCSRA_ADEN);
}

u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel, u16* Copy_pu16Result) {
	u32 Local_u32Counter = 0;
	u8 Local_u8ErrorState = OK;

	if (Copy_pu16Result != NULL) {

		if (ADC_u8State == IDLE) {

			/*ADC is now busy */
			ADC_u8State = BUSY;

			//Clear first 5 bits  in ADMUX register
			ADMUX &= 0b11100000;

			//Set required channel
			ADMUX |= Copy_u8Channel;

			//Start conversion
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			//Busy waiting (polling) until conversion is complete or until timeout is reached
			while (((GET_BIT(ADCSRA, ADCSRA_ADIF)) == 0)
					&& (Local_u32Counter < ADC_u32TIMEOUT)) {
				Local_u32Counter++;
			}

			if (Local_u32Counter == ADC_u32TIMEOUT) {
				//Loop is broken because timeout is reached
				Local_u8ErrorState = TIMEOUT_STATE;
				return Local_u8ErrorState;
			} else {
				//Loop is broken because flag is raised

				*Copy_pu16Result = ADCH;

				//Clearing the flag
				SET_BIT(ADCSRA, ADCSRA_ADIF);
			}
			/*ADC finished conversion and is now idle*/
			ADC_u8State = IDLE;

		} else {
			Local_u8ErrorState = BUSY_STATE;
			return Local_u8ErrorState;
		}
	} else {
		Local_u8ErrorState = NULLPOINTER;
		return Local_u8ErrorState;
	}
	return Local_u8ErrorState;
}

u8 ADC_u8StartConversionASynch(u8 Copy_u8Channel, u16* Copy_pu16Result,	void (*Copy_pvNotificationFunction)(void)) {

	u8 Local_u8ErrorState = OK;

	if ((Copy_pu16Result != NULL) && (Copy_pvNotificationFunction != NULL)) {

		if (ADC_u8State == IDLE) {

			/*ADC is now busy*/
			ADC_u8State = BUSY;


			/*Initialize the global result pointer*/
			ADC_pu16ConversionResult = Copy_pu16Result;

			/*Initialize the global notification  function pointer*/
			ADC_pvNotificationFunction = Copy_pvNotificationFunction;


			//Clear first 5 bits  in ADMUX register
			ADMUX &= ADC_u8CHANNEL_MASK;

			/*Set required channel*/
			ADMUX |= Copy_u8Channel;

			/*Start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*ADC conversion complete  interrupt enable*/
			SET_BIT(ADCSRA, ADCSRA_ADIE);

		} else {
			Local_u8ErrorState = BUSY_STATE;
		}
	} else {
		Local_u8ErrorState = NULLPOINTER;
	}

	return Local_u8ErrorState;
}

u8 ADC_u8StartChainConversionASynch(u8 Copy_u8NumberOfConversions,u16 Copy_pu16Result[], void(*Copy_pvNotificationFunction)(void)) {
	u8 Local_u8ErrorState = OK;

	if(ADC_u8Counter == 0) {

		ADC_u8NumberOfConversions = Copy_u8NumberOfConversions;

		/*Chain conversion now starts*/
		ADC_u8ChainConversionFlag = WORKING;
	}


	if( (Copy_pu16Result != NULL) && (Copy_pvNotificationFunction != NULL)) {

		if(ADC_u8State == IDLE) {

		/*ADC is now busy*/
		ADC_u8State = BUSY;


		if(ADC_u8Counter == 0) {
		/*Initialize the global result pointer*/
		ADC_pu16ConversionResult = Copy_pu16Result;

		/*Initialize the global notification  function pointer*/
		ADC_pvNotificationFunction = Copy_pvNotificationFunction;
		}

		//Clear first 5 bits  in ADMUX register
		ADMUX &= ADC_u8CHANNEL_MASK;

		/*Set required channel*/
		ADMUX |= ADC_u8Counter;

		/*Start conversion*/
		SET_BIT(ADCSRA, ADCSRA_ADSC);

		/*ADC conversion complete  interrupt enable*/
		SET_BIT(ADCSRA, ADCSRA_ADIE);
		}else {
			Local_u8ErrorState = BUSY_STATE;
		}

	} else {
		Local_u8ErrorState = NULLPOINTER;
	}



	return Local_u8ErrorState;
}


u8 ADC_u8SetNotificationFunction(void (*Copy_pvNotificationFunction)(void)) {

	u8 Local_u8ErrorState = OK;
	if(Copy_pvNotificationFunction != NULL) {

		ADC_pvNotificationFunction = Copy_pvNotificationFunction;

	} else {
		Local_u8ErrorState = NULLPOINTER;
		return Local_u8ErrorState;
	}

	return Local_u8ErrorState;


}


void __vector__16(void) 		__attribute__((signal));
void __vector__16(void) {

	if(ADC_u8ChainConversionFlag == NOT_WORKING) {

	/*Read the result*/
	*ADC_pu16ConversionResult = ADCH;

	/*ADC is now idle*/
	ADC_u8State = IDLE;

	/*Invoke the callback notification function*/
	ADC_pvNotificationFunction();

	/*Disable the ADC conversion complete interrupt*/
	CLR_BIT(ADCSRA, ADCSRA_ADIE);


}

  	if(ADC_u8Counter == (ADC_u8NumberOfConversions - 1)) {
			//Invoke the callback notification function
			ADC_pvNotificationFunction();

			//Reset the counter

			ADC_u8Counter = 0;
			//Disable the chain conversion flag
			ADC_u8ChainConversionFlag = NOT_WORKING;
		} else {
		//Increment the chain conversion counter
		ADC_u8Counter++;
		}

	}




