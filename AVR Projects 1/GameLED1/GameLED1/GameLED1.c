/*
 * GameLED1.c
 *
 * Created: 11/17/2017 10:05:41 AM
 *  Author: sajjad
 */ 


#include <avr/io.h>
#include <util/delay.h>


int pressed = 0;
int counter = 0;

void turnAllOn()
{
	
}

void turnAllOff()
{
	
}

void blinkAll()
{
	//PORTC ^= 0xff;
	PORTC |= 1 << PINC0;
	PORTC |= 1 << PINC1;
	PORTC |= 1 << PINC2;
	PORTC |= 1 << PINC3;
	PORTC |= 1 << PINC4;
	_delay_ms(200);
	//PORTC ^= 0xff;
	PORTC ^= 1 << PINC0;
	PORTC ^= 1 << PINC1;
	PORTC ^= 1 << PINC2;
	PORTC ^= 1 << PINC3;
	PORTC ^= 1 << PINC4;
	_delay_ms(200);
}

void train1()
{
	//PORTC |= 0xff;
	//_delay_ms(200);
	PORTC ^= 1 << PINC0;
	_delay_ms(200);
	PORTC ^= 1 << PINC1;
	_delay_ms(200);
	PORTC ^= 1 << PINC2;
	_delay_ms(200);
	PORTC ^= 1 << PINC3;
	_delay_ms(200);
	PORTC ^= 1 << PINC4;
	_delay_ms(200);
	
	
	PORTC ^= 1 << PINC0;
	_delay_ms(200);
	PORTC ^= 1 << PINC1;
	_delay_ms(200);
	PORTC ^= 1 << PINC2;
	_delay_ms(200);
	PORTC ^= 1 << PINC3;
	_delay_ms(200);
	PORTC ^= 1 << PINC4;
	_delay_ms(200);
}

void DoIt()
{
	switch(counter)
	{
		case 1:
			PORTC ^= 1 << PINC0;
			break;
		case 2:
			PORTC ^= 1 << PINC1;
			break;
		case 3:
			PORTC ^= 1 << PINC2;
			break;
		case 4:
			PORTC ^= 1 << PINC3;
			break;
		case 5:
			PORTC ^= 1 << PINC4;	
			break;	
		case 6:
			//PORTC |= 0xff; Don't Do This Because Reset is in PORTC
			PORTC |= 1 << PINC0;
			PORTC |= 1 << PINC1;
			PORTC |= 1 << PINC2;
			PORTC |= 1 << PINC3;
			PORTC |= 1 << PINC4;
			break;
		case 7:
			//PORTC ^= 0xff;
			PORTC ^= 1 << PINC0;
			PORTC ^= 1 << PINC1;
			PORTC ^= 1 << PINC2;
			PORTC ^= 1 << PINC3;
			PORTC ^= 1 << PINC4;
			break;
		case 8:
			blinkAll();
			break;
		case 9:
			train1();
			break;
		case 10:
			for(int i=0;i<5;i++)
			{
				blinkAll();
			}
			break;
		case 11:
			for(int i=0;i<5;i++)
			{
				train1();
			}
			break;
	}

	if ( counter >= 11 ) 
	{
		counter = 0;
	}
}

void ScanButton()
{
	
	if(bit_is_clear(PINC, 5))
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
		if(bit_is_clear(PINC,5))
		{
			//Do Nothing
		}
		else
		{
			//PORTB ^= 1 << PINB0;
			counter++;
			DoIt();
			pressed = 0;					
		}
	}
}

int main(void)
{
	DDRC |= 1 << PINC0;
	DDRC |= 1 << PINC1;
	DDRC |= 1 << PINC2;
	DDRC |= 1 << PINC3;
	DDRC |= 1 << PINC4;
	
	
	DDRC &= ~(1 << PINC5);
	
	PORTC |= 1 << PINC5;
	
    while(1)
    {
        //TODO:: Please write your application code 
		ScanButton();
    }
}