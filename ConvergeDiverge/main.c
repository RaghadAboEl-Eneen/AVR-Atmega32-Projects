
#include <avr/io.h>
#include <util/delay.h>

void main (void) {

	DDRA = 255;

	while(1){
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
	}







}
