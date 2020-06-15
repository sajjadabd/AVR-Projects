/*
 * _1_FirstProject.c
 *
 * Created: 11/5/2017 12:08:10 AM
 *  Author: sajjad
 */ 


#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= 1 << PINB0;
	
    while(1)
    {
		PORTB ^= 1 << PINB0;//XOR to toggle only pin0 on port b
		_delay_ms(1000);
        //TODO:: Please write your application code 
    }
}