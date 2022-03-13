/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: TIMER    			     **********/
/**********      Date: 24-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#define FALLING_EDGE					1
#define RISING_EDGE						2

void Timer0_voidInit(void);
void Timer1_voidInit(void);

void Timer1_voidSetCompValue(u16 Copy_u16Value);


u8 Timer0_u8OverflowSetCallBack(void (*Copy_pvCallBackFunction)(void));
u8 Timer0_u8CompareMatchSetCallBack(void (*Copy_pvCallBackFunction)(void));

void Timer0_voidSetPreload(u8 Copy_u8Preload);
void Timer1_voidSetPreload(u16 Copy_u16Value);

u16 Timer1_u16ReadTimerValue(void);

void ICU_voidInit(void);

u16 ICU_u16ReadInputCapture(void);

u8 ICU_u8SetCallBack(void (*Copy_pvCallBackFunc)(void));

u8 ICU_u8SetTrigger(u8 Copy_u8trigger);


#endif
