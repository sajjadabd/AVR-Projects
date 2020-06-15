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
	DDRC  |= 1 << PINC5; // this is for Relay
	PORTC |= 1 << PINC5;
	
	DDRB  |= 1 << PINB1;// this is for green or ON led
	PORTB |= 1 << PINB1;
	
	
    while(1) // make Relay 10 sec ON and 3 sec OFF
    {
		PORTB |= 1 << PINB1;
		_delay_ms(5000);
		PORTB &= ~(1 << PINB1);
		_delay_ms(10000);
    }
}
