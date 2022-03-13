#include <avr/io.h>
#include <util/delay.h>
#include "STD_TYPES.h"


void main(void) {

	while(1) {
	DDRC = 0;
	DDRA = 1;
	PORTA = 0;
    u8 flag = PORTC;

    if(flag)
        PORTA = 1;
    else if(!flag)
    	PORTA = 0;


		}
}
