#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"

#include "CLCD_interface.h"


void main(void) {


		//1- Direction initialization:
		PORT_voidInit();
		//2- LCD initialization:
		CLCD_voidInit();

		//u8 u8Pattern[8] = {0,0,2,2,2,6,12,24,0};
		//u8 u8Pattern2[8] = {2,0,7,13,12,31,31,0};
		//u8 u8Pattern3[8] = {0,0,3,3,3,31,31,0};
		u8 u8Pattern[8] = {14,31,22,28,24,28,30,31};
		u8 AddressContent;
		CLCD_voidSendData('7');


	while(1) {

	}
}
