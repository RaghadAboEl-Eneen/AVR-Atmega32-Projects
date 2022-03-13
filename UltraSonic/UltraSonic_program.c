/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: HAL                  **********/
/**********      SWC: UltraSonic             **********/
/**********      Date: 30-08-2021            **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "TIMER_interface.h"
#include "GIE_interface.h"
#include "EXTI_interface.h"

#include "UltraSonic_Interface.h"
#include "UltraSonic_config.h"
#include "UltraSonic_private.h"

static u8 CalculateFlag = INACTIVE;
static u8 InterruptCounter = 0;
static volatile f32 NumberOfTicks = 0;

void UltraSonic_voidSendTrigger(void) {

	DIO_u8SetPinValue(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, DIO_u8PIN_LOW);
	DIO_u8SetPinValue(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, DIO_u8PIN_HIGH);
	_delay_us(10);
	DIO_u8SetPinValue(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, DIO_u8PIN_LOW);

}

f32 Ultrasonic_voidGetDistance(void) {

	//f32 Local_f32NumberOfTicks;

	UltraSonic_voidSendTrigger();
	//UltraSonic_voidGetEchoTicks();
	f32 Local_f32Prescalar = 58;
	//f32 Local_f32SpeedOfSound = 0.034;
	//f32 Local_f32Frequency = 10000000;
	//f32 Local_f32Distance = 0;
	//f32 Local_f32Duration = (Local_f32Prescalar * Local_f32Frequency* Local_f32NumberOfTicks) / Local_f32Frequency;

	//Local_f32Distance = (Local_f32Duration * Local_f32SpeedOfSound)/2;
	//Local_f32Distance /= 2;

	return NumberOfTicks / Local_f32Prescalar;

}

void UltraSonic_voidInit(void) {

	GIE_voidEnableGlobal();
	EXTI_voidINT0Init();
	Timer0_voidInit();
	Timer0_voidDisable();
	Timer0_voidClearCounterValue();

	EXTI_u8INTSetCallBack(&UltraSonic_voidGetEchoTicks, EXTI_INT0);
}

u8 UltraSonic_voidGetEchoTicks2(void) {

	u8 Local_u8PinValue = DIO_u8PIN_LOW;
	u8 Local_u8NumberOfTicks = 0;

	//Disabling the timer
	Timer0_voidDisable();

	//Clearing the timer counter
	Timer0_voidClearCounterValue();

	UltraSonic_voidSendTrigger();

	//polling until a signal is recieved
	while (Local_u8PinValue == DIO_u8PIN_LOW) {
		DIO_u8GetPinValue(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN, &Local_u8PinValue);
	}

	//Enabling the timer as a signal was recieved
	Timer0_voidEnable();

	//polling until end of signal
	while (Local_u8PinValue == DIO_u8PIN_HIGH) {
		DIO_u8GetPinValue(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN, &Local_u8PinValue);
	}

	//getting the counter value
	Local_u8NumberOfTicks = Timer0_u8GetCounterValue();

	//Disabling the timer again
	Timer0_voidDisable();

	return Local_u8NumberOfTicks;

}

void UltraSonic_voidGetEchoTicks(void) {

	if(InterruptCounter == 0) {

		Timer0_voidClearCounterValue();
		Timer0_voidEnable();
		InterruptCounter = 1;

	} else if(InterruptCounter == 1){

		Timer0_voidDisable();
		NumberOfTicks = Timer0_u8GetCounterValue();
		InterruptCounter = 0;

	}


	//InterruptCounter++;
	//Timer0_voidEnable();
	//if (InterruptCounter == 2) {

	//NumberOfTicks = (f32) Timer0_u8GetCounterValue();
	//	Timer0_voidDisable();
	//Timer0_voidClearCounterValue();
	//InterruptCounter = 0;
	//CalculateFlag = ACTIVE;

}



