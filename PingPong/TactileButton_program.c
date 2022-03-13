#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_interface.h"

u8 TactileButton_u8DebounceButton(u8 Copy_u8Port, u8 Copy_u8Pin) {

	u8 Local_Flag;
	u8 Local_Stopper;

	while (1) {
		DIO_u8GetPinValue(Copy_u8Port, Copy_u8Pin, &Local_Flag);
		if (Local_Flag == 0) {
			while (Local_Flag == 0) {
				DIO_u8GetPinValue(Copy_u8Port, Copy_u8Pin, &Local_Flag);
				if (Local_Flag == 1) {
					Local_Stopper = 1;
				}

			}
		} else {
			Local_Stopper = 1;
		}

		if (Local_Flag && Local_Stopper) {
			DIO_u8GetPinValue(Copy_u8Port, Copy_u8Pin, &Local_Flag);
			_delay_ms(50);
			if (Local_Flag == 1) {
				return 1;
			} else {
				Local_Stopper = 0;
			}
		}

	}

}
