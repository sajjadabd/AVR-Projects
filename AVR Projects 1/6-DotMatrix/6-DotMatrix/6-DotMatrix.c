/*
 * _6_DotMatrix.c
 *
 * Created: 11/9/2017 11:26:51 PM
 *  Author: sajjad
 */ 


#include <avr/io.h>
#include <util/delay.h>

//#define input PINC

int pressed = 0;
int counter = 0;

void turnOnA()
{
	PORTB ^= 1 << PINB1;//a
}

void turnOnB()
{
	PORTB ^= 1 << PINB0;//b
}

void turnOnC()
{
	PORTB ^= 1 << PINB5;//c
}

void turnOnD()
{
	PORTB ^= 1 << PINB6;//d
}

void turnOnE()
{
	PORTB ^= 1 << PINB7;//e
}

void turnOnF()
{
	PORTB ^= 1 << PINB2;//f
}

void turnOnG()
{
	PORTB ^= 1 << PINB3;//g
}


void ScanButton()
{
	
	
	if(bit_is_clear(PINC, 0))
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
		if(bit_is_clear(PINC,0))
		{
			//Do Nothing
		}
		else
		{
			PORTB = 0x00;//set PORTB to 0b00000000;
			switch(counter)
			{
				case 0:
				//a,b,c,d,e,f
				turnOnA();
				turnOnB();
				turnOnC();
				turnOnD();
				turnOnE();
				turnOnF();
				//turnOnG();
				break;
				case 1:
				//b,c
				turnOnB();
				turnOnC();
				break;
				case 2:
				//a,b,g,d,e
				turnOnA();
				turnOnB();
				turnOnG();
				turnOnD();
				turnOnE();
				break;
				case 3:
				//a,b,g,c,d
				turnOnA();
				turnOnB();
				turnOnG();
				turnOnC();
				turnOnD();
				break;
				case 4:
				//f,g,b,c
				turnOnF();
				turnOnG();
				turnOnB();
				turnOnC();
				break;
				case 5:
				//a,f,g,c,d
				turnOnA();
				turnOnF();
				turnOnG();
				turnOnC();
				turnOnD();
				break;
				case 6:
				//g,c,d,e,f,a
				turnOnG();
				turnOnC();
				turnOnD();
				turnOnE();
				turnOnF();
				turnOnA();
				break;
				case 7:
				//a,b,c
				turnOnA();
				turnOnB();
				turnOnC();
				break;
				case 8:
				//a,b,c,d,e,f,g
				turnOnA();
				turnOnB();
				turnOnC();
				turnOnD();
				turnOnE();
				turnOnF();
				turnOnG();
				break;
				case 9:
				//all - e
				turnOnA();
				turnOnB();
				turnOnC();
				turnOnD();
				//turnOnE();
				turnOnF();
				turnOnG();
				break;
			}
			/*
			//PORTC ^= 1 << PINC1;
			PORTB ^= 1 << PINB0;//b
			_delay_ms(1000);
			PORTB ^= 1 << PINB1;//a
			_delay_ms(1000);
			PORTB ^= 1 << PINB2;//f
			_delay_ms(1000);
			PORTB ^= 1 << PINB3;//g
			_delay_ms(1000);
			
			PORTB ^= 1 << PINB4;//h
			_delay_ms(1000);
			PORTB ^= 1 << PINB5;//c
			_delay_ms(1000);
			PORTB ^= 1 << PINB6;//d
			_delay_ms(1000);
			PORTB ^= 1 << PINB7;//e
			_delay_ms(1000);
			*/
			
			pressed = 0;
			counter++;
			if(counter > 9)	
			{
				counter = 0;
			}	
		}
	}
}

int main(void)
{
	//DDRB |= 1 << PINB0;    // Data Direction Register output PINB0
	//DDRB |= 0b11111111;
	DDRC |= 1 << PINC1;
	DDRC &= ~(1 << PINC0); //Data Direction Register input PINB1
	PORTC |= 1 << PINC0;   // set PINB1 to a high reading
	
	
	//PORTC ^= 1 << PINC1;
	
    while(1)
    {
        ScanButton();
    }
}