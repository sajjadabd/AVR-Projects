/*
 * ledBlink1.c
 *
 * Created: 1/23/2019 1:02:56 AM
 *  Author: sajjad
 */ 


#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= 1 << PINB0;
	DDRB |= 1 << PINB1;
	
	PORTB |= 1 << PINB0;
	PORTB &= ~(1 << PINB1);
	
    while(1)
    {
		PORTB ^= 1 << PINB0;
		PORTB ^= 1 << PINB1;
		_delay_ms(1000);
        //TODO:: Please write your application code 
    }
}