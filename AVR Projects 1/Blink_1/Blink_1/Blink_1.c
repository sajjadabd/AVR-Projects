/*
 * Blink_1.c
 *
 * Created: 2/10/2018 3:50:34 PM
 *  Author: sajjad
 */ 


#include <avr/io.h>
#include <util/delay.h>

void blink()
{
	PORTB ^= 1 << PINB0;
	_delay_ms(1000);
	PORTB ^= 1 << PINB0;
	_delay_ms(100);
}

int main(void)
{
	DDRB |= 1 << PINB0;
	
    while(1)
    {
        //TODO:: Please write your application code 
		blink();
    }
}

