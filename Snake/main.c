
#include <avr/io.h>
#include <util/delay.h>

void main (void) {

	DDRA = 255;

	while(1){
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

	}







}
