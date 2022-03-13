#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_interface.h"

u8 TactileButton_u8DebounceButton(u8 Copy_u8Port, u8 Copy_u8Pin) {
	while (1) {
		u8 Local_Flag ;
		u8 Local_Stopper;
		DIO_u8GetPinValue(Copy_u8Port, Copy_u8Pin, &Local_Flag);
		while (Local_Flag == DIO_u8PIN_LOW) {
			DIO_u8GetPinValue(Copy_u8Port, Copy_u8Pin, &Local_Flag);
			if (Local_Flag == DIO_u8PIN_HIGH) {
				Local_Stopper = 1;
			}

		}

		if (Local_Flag && Local_Stopper) {
			_delay_ms(30);
			DIO_u8GetPinValue(Copy_u8Port, Copy_u8Pin, &Local_Flag);
			if (Local_Flag == DIO_u8PIN_HIGH) {
				return 1;
			}
		}

	}

}
