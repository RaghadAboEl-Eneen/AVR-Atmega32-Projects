/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: TIMER    			     **********/
/**********      Date: 24-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_config.h"
#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "TIMER_register.h"


// Global pointer to callback function to hold the function's address
static void(*Timer0_pvOverflowCallBackFunction)(void) = NULL;

// Global pointer to callback function to hold the function's address
static void(*Timer0_pvCompareMatchCallBackFunction)(void) = NULL;


void Timer0_voidInit(void) {

	//Initialize waveform generation mode to work as normal mode
	//CLR_BIT(TCCR0, TCCR0_WGM00);
	//CLR_BIT(TCCR0, TCCR0_WGM01);

	//Initialize waveform generation mode to work as CTC mode
	CLR_BIT(TCCR0, TCCR0_WGM00);
	SET_BIT(TCCR0, TCCR0_WGM01);

	//Set the required preload
	//TCNT0 = TIMER0_u8PRELOAD_VALUE;

	//Set the required compared match value
	OSC0 = TIMER0_COMPARE_MATCH_VALUE;


	SET_BIT(TIMSK, TIMSK_OCIE0);

	//Timer0 overflow interrupt enable
	//SET_BIT(TIMSK, TIMSK_TOIE0);

	//Set the required prescaler
	TCCR0 &= TIMER0_PRESCALER_MASK;
	TCCR0 |= TIMER0_u8PRESCALER;


}

void Timer1_voidInit(void) {

	//Compare match output mode: Set on top , Clear on compare (Non-inverted mode)
	SET_BIT(TCCR1A, TCCR1A_COM1A1);
	CLR_BIT(TCCR1A, TCCR1A_COM1A0);

	//Waveform generation form mode: Fast PWM with ICR1 as top value
	CLR_BIT(TCCR1A, TCCR1A_WGM10);
	SET_BIT(TCCR1A, TCCR1A_WGM11);
	SET_BIT(TCCR1B, TCCR1B_WGM12);
	SET_BIT(TCCR1B, TCCR1B_WGM13);

	//Set Timer1 top value
	ICR1 = 25000;

	//Set Compare Match value OCR1A
	OCR1A = 9375;

	//Prescalar setting: divide by 8
	CLR_BIT(TCCR1B, TCCR1B_CS12);
	SET_BIT(TCCR1B, TCCR1B_CS11);
	CLR_BIT(TCCR1B, TCCR1B_CS10);

}


void Timer1_voidSetCompValue(u16 Copy_u16Value) {

	OCR1A = Copy_u16Value;

}


u8 Timer0_u8OverflowSetCallBack(void (*Copy_pvCallBackFunction)(void)) {


	u8 Local_u8ErrorState = OK;

	if(Copy_pvCallBackFunction != NULL) {
		Timer0_pvOverflowCallBackFunction = Copy_pvCallBackFunction;

	} else {
		Local_u8ErrorState = NULLPOINTER;
		return Local_u8ErrorState;
	}

	return Local_u8ErrorState;

}

u8 Timer0_u8CompareMatchSetCallBack(void (*Copy_pvCallBackFunction)(void)) {


	u8 Local_u8ErrorState = OK;

	if(Copy_pvCallBackFunction != NULL) {
		Timer0_pvCompareMatchCallBackFunction = Copy_pvCallBackFunction;

	} else {
		Local_u8ErrorState = NULLPOINTER;
		return Local_u8ErrorState;
	}

	return Local_u8ErrorState;

}

void Timer0_voidSetPreload(u8 Copy_u8Preload) {

	TCNT0 = Copy_u8Preload;

}


void __vector_11(void)			__attribute__((signal));
void __vector_11(void) {


	if(Timer0_pvOverflowCallBackFunction != NULL) {
		Timer0_pvOverflowCallBackFunction();
	} else {
		//Do Nothing
	}

}

void __vector_10(void)			__attribute__((signal));
void __vector_10(void) {


	if(Timer0_pvCompareMatchCallBackFunction != NULL) {
		Timer0_pvCompareMatchCallBackFunction();
	} else {
		//Do Nothing
	}

}




