#include <avr/io.h>
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"

void main(void) {

	DDRD = 255; //setting port D to be output for first seven segment .
	DDRA = 255; //setting port A to be output for second seven segment.
	DDRC = 7;   //setting port C to be output for green , yellow and red leds.

	u8 sev_seg[10] = { 0b00111111, 0b00000110, 0b01011011, 0b01001111,
			0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111,
			0b01101111 };
	//array containing binary coded values for seven segment from 0 to 9;

	s8 i, j, k = 0;

	while (1) {

		PORTC = 1;
		i = 1;
		j = 5;
		while (i >= 0) {
			PORTD = sev_seg[i];
			while (j >= 0) {
				PORTA = sev_seg[j];
				_delay_ms(1000);
				j--;
			}
			i--;
			j = 9;
		}

		j = 5;
		PORTC = 2;
		while (j >= 0) {
			PORTA = sev_seg[j];
			_delay_ms(1000);
			j--;
		}
		i = 1;
		j = 5;
		PORTC = 4;
		while (i >= 0) {
			PORTD = sev_seg[i];
			while (j >= 0) {
				PORTA = sev_seg[j];
				_delay_ms(1000);
				j--;
			}
			i--;
			j = 9;
		}

	}

}
