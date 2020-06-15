/*
 * _8_Servo1.c
 *
 * Created: 11/12/2017 1:12:39 AM
 *  Author: sajjad
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main()
{
	//PD5 --> Data for Servo
	DDRD  |= 0xff; // set all D Pins for output
	
	TCCR1A |= 1 << WGM11 | 1 << COM1A1 | 1 << COM1A0;
	TCCR1B |= 1 << WGM12 | 1 << WGM13 | 1 << CS10;
	ICR1 = 19999;
	
	//OCR1A = ICR1 - 2000 ; // 17999 --> ~18000
	//OCR1A = ICR1 - 900; // .9 miliseconds 
	
	while(1)
	{
		OCR1A = ICR1 - 800;
		_delay_ms(1000);
		OCR1A = ICR1 - 2200;
		_delay_ms(1000);
		
	}
}