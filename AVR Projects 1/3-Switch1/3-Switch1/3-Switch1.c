/*
 * _3_Switch1.c
 *
 * Created: 11/6/2017 2:05:43 AM
 *  Author: sajjad
 */ 


#include <avr/io.h>

int main(void)
{
    DDRB |= 1 << PINB0;
	DDRB &= ~(1 << PINB1);
	
	PORTB |= 1 << PINB1;
	int pressed = 0;
	
    while(1)
    {
		
		//KeypadScan();
		
		
	
		if(bit_is_clear(PINB, 1))
		{
			if(pressed >= 1000)
			{
				pressed = 500;
			}
			else
			{
				pressed++;
			}							
		}	
		
		if(pressed >= 400)
		{
			if(bit_is_clear(PINB,1))
			{
				//Do Nothing
			}
			else
			{
				PORTB ^= 1 << PINB0;
				pressed = 0;					
			}
		}
				
        //TODO:: Please write your application code 
    }
}