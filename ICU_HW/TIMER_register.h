/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: TIMER    			     **********/
/**********      Date: 24-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_


#define OSC0			*((volatile u8*)0x5C)			//Output compare match register


#define TIMSK			*((volatile u8*)0x59)			//Timer Mask Register
#define TIMSK_TICIE1	5								//Input capture interrupt enable
#define TIMSK_TOIE0		0								//Timer overflow interrupt enable
#define TIMSK_OCIE0		1								//Timer0 compare match interrupt enable


#define TCCR0			*((volatile u8*)0x53)   		//Timer Counter Control Register 0
#define TCCR0_WGM00		6								//Waveform Generation Mode Bit 0
#define TCCR0_COM01		5								//Timer0 output compare match mode bit1
#define TCCR0_COM00		4								//Timer0 output compare match mode bit0
#define TCCR0_WGM01		3								//Waveform Generation Mode Bit 1



#define TCNT0			*((volatile u8*)0x52)			//Timer Counter 0 register

#define TCCR1A			*((volatile u16*)0x4F)			//Timer1 Control Register A
#define TCCR1A_COM1A1	7								//Compare output mode for channel A bit1
#define TCCR1A_COM1A0	6								//Compare output mode for channel A bit0
#define TCCR1A_WGM11	1								//Waveform generation mode bit1
#define TCCR1A_WGM10	0								//Waveform generation mode bit0

#define TCCR1B			*((volatile u16*)0x4E)			//Timer Control Register8
#define TCCR1B_ICES1	6								//Input capture edge select
#define TCCR1B_WGM13	4								//Waveform generation mode bit3
#define TCCR1B_WGM12	3								//Waveform generation mode bit2
#define TCCR1B_CS12		2								//Prescalar bit2
#define TCCR1B_CS11		1								//Prescalar bit1
#define TCCR1B_CS10		0								//Prescalar bit0


#define OCR1A			*((volatile u16*)0x4A)			//Output compare match for channel A

#define ICR1			*((volatile u16*)0x46)			//Input Capture Register

#define TCNT1			*((volatile u16*)0x4C)			//Timer1 counter register 1

#endif
