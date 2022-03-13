
#include <avr/io.h>
#include <util/delay.h>

void main(void) {

	DDRA = 255;
	PORTA = 128;
    _delay_ms(250);
	while(1) {

		if(PORTA == 1) {
			PORTA = 128;
			_delay_ms(250);
		}

        PORTA = PORTA >> 1;
        _delay_ms(250);

	}

}

