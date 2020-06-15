/*
 * OptacoplerTestWithAtmega8.c
 *
 * Created: 1/1/2018 4:35:07 PM
 *  Author: sajjad
 */ 


#include <avr/io.h>
#include <util/delay.h>

int pressed = 0;


void ScanButton()
{
	
	if(bit_is_clear(PINB, 0))
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
		if(bit_is_clear(PINB,0))
		{
			//Do Nothing
			PORTB |= 1 << PINB1;
		}
		else
		{
			PORTB &= ~(1 << PINB1);	
			pressed = 0;		
		}
		
	}
	
	
}

int main(void)
{
    while(1)
    {
		DDRB |= 1 << PINB1;
		DDRB &= ~(1 << PINB0);
		
		PORTB |= 1 << PINB0;
		
		ScanButton();
        //TODO:: Please write your application code 
    }
}