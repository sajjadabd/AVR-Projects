/*
 * Rele1.c
 *
 * Created: 11/21/2017 12:01:22 PM
 *  Author: sajjad
 */ 


#include <avr/io.h>
#include <util/delay.h>

int pressed = 0;


void ScanButton()
{
	
	if(bit_is_clear(PINC, 4))
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
		if(bit_is_clear(PINC,4))
		{
			//Do Nothing
		}
		else
		{
			PORTC ^= 1 << PINC5;
			pressed = 0;					
		}
	}
}


int main(void)
{
	DDRC |= 1 << PINC5;
	DDRC &= ~(1<<PINC4);
	PORTC |= 1 << PINC4;
	
    while(1)
    {
        //TODO:: Please write your application code 
		ScanButton();
    }
}