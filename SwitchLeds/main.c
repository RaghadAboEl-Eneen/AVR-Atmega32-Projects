#include <avr/io.h>
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"

void main(void) {

	DDRD = 1; // setting D0 as output.
	PORTD = 0; // putting low on D0 to act as ground.

	DDRA = 255; // setting port A as output for leds.

	DDRB = 0; // setting port B as input for switches.
	PORTB = 255; //enabling pull up of port B;

	DDRC = 0; // setting port C as input for switches.
	PORTC = 255; //enabling pull up of port C;

	while (1) {
		u8 flag = PINC;
		switch (flag) {
		case 1:
			PORTA = 255; // port a0 as high
			_delay_ms(500);
			PORTA = 0;
			_delay_ms(500);
			break;

		case 2:

			PORTA = 128;
			_delay_ms(250);
			while (PORTA != 1) {
				PORTA = PORTA >> 1;
				_delay_ms(250);
			}

			break;

		case 4:
			PORTA = 1;
			_delay_ms(200);
			while (PORTA != 128) {
				PORTA = PORTA << 1;
				_delay_ms(200);
			}

			break;
		case 8:
			PORTA = 24;
			_delay_ms(300);
			PORTA = 36;
			_delay_ms(300);
			PORTA = 66;
			_delay_ms(300);
			PORTA = 129;
			_delay_ms(300);
			break;
		case 16:
			PORTA = 129;
			_delay_ms(300);
			PORTA = 66;
			_delay_ms(300);
			PORTA = 36;
			_delay_ms(300);
			PORTA = 24;
			_delay_ms(300);
			break;
		case 32:
			PORTA = 129;
			_delay_ms(300);
			PORTA = 66;
			_delay_ms(300);
			PORTA = 36;
			_delay_ms(300);
			PORTA = 24;
			_delay_ms(300);
			PORTA = 36;
			_delay_ms(300);
			PORTA = 66;
			_delay_ms(300);
			break;
		case 64:
			PORTA = 128;
			_delay_ms(300);
			PORTA = 192;
			_delay_ms(300);
			PORTA = 224;
			_delay_ms(300);
			PORTA = 240;
			_delay_ms(300);
			PORTA = 248;
			_delay_ms(300);
			PORTA = 252;
			_delay_ms(300);
			PORTA = 254;
			_delay_ms(300);
			PORTA = 255;
			_delay_ms(300);
			break;
		case 128:
			PORTA = 128;
			_delay_ms(250);
			while (PORTA != 1) {
				PORTA = PORTA >> 1;
				_delay_ms(250);
			}
			PORTA = 1;
			_delay_ms(200);
			while (PORTA != 128) {
				PORTA = PORTA << 1;
				_delay_ms(200);
			}
			break;
		default:
			PORTA = 0;
		}

	}
}

