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


void Timer0_voidInit(void);
void Timer1_voidInit(void);

void Timer1_voidSetCompValue(u16 Copy_u16Value);


u8 Timer0_u8OverflowSetCallBack(void (*Copy_pvCallBackFunction)(void));
u8 Timer0_u8CompareMatchSetCallBack(void (*Copy_pvCallBackFunction)(void));

void Timer0_voidSetPreload(u8 Copy_u8Preload);




#endif
