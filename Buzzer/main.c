#include <util/delay.h>
#include <stdio.h>

#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "USART_interface.h"


#include "Buzzer_interface.h"

void main(void) {

	PORT_voidInit();
	USART_voidInit();


	u16 Local_u16Notes[7] = {A,B,C,D,E,F,G};
	//47
	u16 Local_u16Melody[50] = {G,G,D,D,E,E,D,PAUSE,C,C,B,B,A,A,G,PAUSE,D,D,C,C,B,B,A,PAUSE,D,D,C,C,B,B,A,PAUSE,G,G,D,D,E,E,D,PAUSE,C,C,B,B,A,A,G};
	u16 Local_u16BloodyStream[15] = {C,D,G,F,F,F,C,D,F,C,D,G,F,F,F};
	u16 Local_u16nanana[] = {F,A,B,PAUSE,F,A,B,PAUSE,F,A,B,PAUSE,PAUSE,B,PAUSE,B,G,E,PAUSE,PAUSE,D,E,G,E,PAUSE,F,A,B,PAUSE,F,A,B,F,A,B,PAUSE,B,PAUSE,B,G,PAUSE,B,G,D,E,PAUSE,D,E,F,PAUSE,G,A,B,PAUSE,B,E,PAUSE,F,G,A,PAUSE,B,A,B,PAUSE,D,E,F,PAUSE,G,0};
	u8 Local_u8Counter ;




	while(1) {

		Local_u8Counter = 0;
		while(Local_u16nanana[Local_u8Counter] != 0) {
			Buzzer_u16PlayTone(Local_u16Melody[Local_u8Counter], 200);
			//_delay_ms(500);
			Local_u8Counter++;
		}

	}
}


