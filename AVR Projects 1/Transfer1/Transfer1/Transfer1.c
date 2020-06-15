/*
 * Transfer1.c
 *
 * Created: 11/22/2017 5:55:27 PM
 *  Author: sajjad
 */ 


#include <avr/io.h>
#include <util/delay.h>

int pressed = 0;

void ScanButton()
{
	
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
}

int main(void)
{
	DDRB |= 1 << PINB0;
	DDRB |= ~(1<<PINB1);
	
	PORTB |= 1 << PINB1;
	
    while(1)
    {
        //TODO:: Please write your application code 
		ScanButton();
		
    }
}