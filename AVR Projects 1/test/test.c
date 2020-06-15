#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRB |= 1 << PINB0;
	
	while(1)
	{
		PORTB ^= 1 << PINB0;
		_delay_ms(1000);
	}
}