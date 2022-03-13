
#include <avr/io.h>
#include <util/delay.h>

void main(void) {


	DDRD = 1; // setting D0 as output.
	PORTD = 0; // putting low on D0 to act as ground.
	DDRA = 255;
	PORTA = 1;
    _delay_ms(200);
	while(1) {


		if(PORTA == 128) {
			PORTA = 1;
			_delay_ms(200);
		}
        PORTA = PORTA << 1 ;
        _delay_ms(200);

	}

}

