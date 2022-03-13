#include <avr/io.h>
#include <util/delay.h>
#include "STD_TYPES.h"


void main(void) {

	u8 sev_seg[10] = {0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};
    u8 i ;
	DDRA = 255;

	while(1) {

	  for(i=0 ; i < 10 ; i++) {
		  PORTA = sev_seg[i];
		   _delay_ms(1000);
	  }

	}
}
