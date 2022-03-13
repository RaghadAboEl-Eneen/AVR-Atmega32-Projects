#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"

void INT0_ISR (void);

void main(void) {

	PORT_voidInit();
	EXTI_voidINT0Init();
	EXTI_u8INTSetCallBack(&INT0_ISR, EXTI_INT0);
	GIE_voidEnableGlobal();
    EXTI_u8INTSetSenseControl(FALLING_EDGE, EXTI_INT0);

	while(1) {

	}

}


void INT0_ISR (void) {
	DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_HIGH);
}
