// Created on: Aug 18, 2020
#include <avr/io.h>
#include <util/delay.h>\>

void main(void) {
	DDRA = 255; // port a0 as output

	while (1) {

		PORTA = 255; // port a0 as high
		_delay_ms(500);
		PORTA = 0;
		_delay_ms(500);

	}
}

