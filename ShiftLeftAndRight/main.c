
#include <avr/io.h>
#include <util/delay.h>

void main(void) {

	DDRA = 255;
	PORTA = 128;
	int flag = 0 ;
    _delay_ms(250);
	while(1) {

		if(flag == 0) {
			PORTA = PORTA >> 1;
		   _delay_ms(250);
			if(PORTA == 1) {
				flag = 1;
				_delay_ms(250);
			}
		}

		if(flag == 1) {
			PORTA = PORTA << 1;
			_delay_ms(250);
			if(PORTA == 128) {
				flag = 0;
				_delay_ms(250);
				}
		}


	}

}

