/*
 * _7_Transistor.c
 *
 * Created: 11/10/2017 12:29:31 AM
 *  Author: sajjad
 */ 


#include <avr/io.h>
#include <util/delay.h>


int pressed = 0;


void ScanButton()
{
	
	if(bit_is_clear(PINC, 1))
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
		if(bit_is_clear(PINC,1))
		{
			//Do Nothing
		}
		else
		{
			PORTC ^= 1 << PINC0;
			pressed = 0;					
		}
	}
}

int main(void)
{
	DDRC |= 1 << PINC0;
	
	DDRC &= ~(1<< PINC1);
	
	PORTC |= 1 << PINC1;//set PINC1 to high reading
	
	PORTC ^= 1 << PINC0;
	
    while(1)
    {
		ScanButton();
        //TODO:: Please write your application code 
    }
}