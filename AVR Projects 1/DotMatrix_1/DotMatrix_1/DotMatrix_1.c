/*
 * DotMatrix_1.c
 *
 * Created: 1/27/2018 12:42:04 PM
 *  Author: sajjad
 */ 


#include <avr/io.h>
#include <util/delay.h>

#define R8 PINA0
#define R7 PINA1
#define R6 PINA2
#define R5 PINA3
#define R4 PINA4
#define R3 PINA5
#define R2 PINA6
#define R1 PINA7

#define C1 PINB0
#define C2 PINB1
#define C3 PINB2
#define C4 PINB3
#define C5 PINB4
#define C6 PINB5
#define C7 PINB6
#define C8 PINB7

int pressed1 = 0;
int pressed2 = 0;
int pressed3 = 0;
int pressed4 = 0;

int i = 4;
int j = 4;

void init()
{
	DDRA |= 1 << R1;
	DDRA |= 1 << R2;
	DDRA |= 1 << R3;
	DDRA |= 1 << R4;
	DDRA |= 1 << R5;
	DDRA |= 1 << R6;
	DDRA |= 1 << R7;
	DDRA |= 1 << R8;
	//-----------------------
	DDRB |= 1 << C1;
	DDRB |= 1 << C2;
	DDRB |= 1 << C3;
	DDRB |= 1 << C4;
	DDRB |= 1 << C5;
	DDRB |= 1 << C6;
	DDRB |= 1 << C7;
	DDRB |= 1 << C8;
	//------------------------
	PORTB |= 1 << C1;
	PORTB |= 1 << C2;
	PORTB |= 1 << C3;
	PORTB |= 1 << C4;
	PORTB |= 1 << C5;
	PORTB |= 1 << C6;
	PORTB |= 1 << C7;
	PORTB |= 1 << C8;
	//------------------------	
}
//
//LED(volatile uint8_t* port, uint8_t pin);
//{
    //Port=port;
    //Pin=pin;
//}
//void write(bool val)
//{
    //if(val) (*Port) |= 1 << Pin;
    //else    (*Port) &= ~(1 << Pin);
//}

void firstPlay(uint8_t row)
{
	//turn on the first LED
	PORTA |= 1 << row;
	PORTB &= ~(1 << C1);
	_delay_ms(100);
	
	PORTB |= 1 << C1;
	PORTB &= ~(1 << C2);
	_delay_ms(100);
	
	PORTB |= 1 << C2;
	PORTB &= ~(1 << C3);
	_delay_ms(100);
	
	PORTB |= 1 << C3;
	PORTB &= ~(1 << C4);
	_delay_ms(100);
	
	PORTB |= 1 << C4;
	PORTB &= ~(1 << C5);
	_delay_ms(100);
	
	PORTB |= 1 << C5;
	PORTB &= ~(1 << C6);
	_delay_ms(100);
	
	PORTB |= 1 << C6;
	PORTB &= ~(1 << C7);
	_delay_ms(100);
	
	PORTB |= 1 << C7;
	PORTB &= ~(1 << C8);
	_delay_ms(100);
	
	PORTB |= (1 << C8);	
	PORTA &= ~(1 << row);
}

void secondPlay(uint8_t row)
{
	//turn on the first LED
	PORTB &= ~(1 << row);
	PORTA |= (1 << R1);
	_delay_ms(100);
	
	PORTA &= ~(1 << R1);
	PORTA |= 1 << R2;
	_delay_ms(100);
	
	PORTA &= ~(1 << R2);
	PORTA |= 1 << R3;
	_delay_ms(100);
	
	PORTA &= ~(1 << R3);
	PORTA |= 1 << R4;
	_delay_ms(100);
	
	PORTA &= ~(1 << R4);
	PORTA |= 1 << R5;
	_delay_ms(100);
	
	PORTA &= ~(1 << R5);
	PORTA |= 1 << R6;
	_delay_ms(100);
	
	PORTA &= ~(1 << R6);
	PORTA |= 1 << R7;
	_delay_ms(100);
	
	PORTA &= ~(1 << R7);
	PORTA |= 1 << R8;
	_delay_ms(100);
	
	PORTA &= ~(1 << R8);	
	PORTB |= 1 << row;
}

void resetRow()
{
	PORTA &= ~(1 << R1);
	PORTA &= ~(1 << R2);
	PORTA &= ~(1 << R3);
	PORTA &= ~(1 << R4);
	PORTA &= ~(1 << R5);
	PORTA &= ~(1 << R6);
	PORTA &= ~(1 << R7);
	PORTA &= ~(1 << R8);
}

void resetCol()
{
	PORTB |= 1 << C1;
	PORTB |= 1 << C2;
	PORTB |= 1 << C3;
	PORTB |= 1 << C4;
	PORTB |= 1 << C5;
	PORTB |= 1 << C6;
	PORTB |= 1 << C7;
	PORTB |= 1 << C8;
}

void reset()
{
	PORTA &= ~(1 << R1);
	PORTA &= ~(1 << R2);
	PORTA &= ~(1 << R3);
	PORTA &= ~(1 << R4);
	PORTA &= ~(1 << R5);
	PORTA &= ~(1 << R6);
	PORTA &= ~(1 << R7);
	PORTA &= ~(1 << R8);
	
	PORTB |= 1 << C1;
	PORTB |= 1 << C2;
	PORTB |= 1 << C3;
	PORTB |= 1 << C4;
	PORTB |= 1 << C5;
	PORTB |= 1 << C6;
	PORTB |= 1 << C7;
	PORTB |= 1 << C8;
}

void ScanButtonUp()
{
	
	if(bit_is_clear(PINC, 0))
	{
		if(pressed1 >= 1000)
		{
			pressed1 = 500;
		}
		else
		{
			pressed1++;
		}							
	}	
		
	if(pressed1 >= 400)
	{
		if(bit_is_clear(PINC,0))
		{
			//Do Nothing
		}
		else
		{
			//PORTB ^= 1 << PINB0;
			if( j > 1 )
			{
				j-=1;
			}
			play();
			pressed1 = 0;					
		}
	}
}

void ScanButtonDown()
{
	
	if(bit_is_clear(PIND, 7))
	{
		if(pressed2 >= 1000)
		{
			pressed2 = 500;
		}
		else
		{
			pressed2++;
		}							
	}	
		
	if(pressed2 >= 400)
	{
		if(bit_is_clear(PIND,7))
		{
			//Do Nothing
		}
		else
		{
			//PORTB ^= 1 << PINB0;
			if( j < 8 )
			{
				j +=1 ;
			}
			play();
			pressed2 = 0;					
		}
	}
}

void ScanButtonRight()
{
	
	if(bit_is_clear(PIND, 5))
	{
		if(pressed3 >= 1000)
		{
			pressed3 = 500;
		}
		else
		{
			pressed3++;
		}							
	}	
		
	if(pressed3 >= 400)
	{
		if(bit_is_clear(PIND,5))
		{
			//Do Nothing
		}
		else
		{
			//PORTB ^= 1 << PINB0;
			if(i > 1)
			{
				i -= 1;
			}
			play();
			pressed3 = 0;					
		}
	}
}

void ScanButtonLeft()
{
	
	if(bit_is_clear(PIND, 6))
	{
		if(pressed4 >= 1000)
		{
			pressed4 = 500;
		}
		else
		{
			pressed4++;
		}							
	}	
		
	if(pressed4 >= 400)
	{
		if(bit_is_clear(PIND,6))
		{
			//Do Nothing
		}
		else
		{
			//PORTB ^= 1 << PINB0;
			
			if(i < 8)
			{
				i +=1 ;
			}
			play();
			pressed4 = 0;					
		}
	}
}

void turnOnRow(uint8_t row)
{
	resetRow();
	PORTA |= 1 << row;
}

void turnOffCol(uint8_t col)
{
	resetCol();
	PORTB &= ~(1 << col);
}

void play()
{
	int thisI,thisJ;
	thisI = i-1;
	thisJ = j-1;
	turnOnRow(thisI);
	turnOffCol(thisJ);
	
}

int main(void)
{
	init();
	
	firstPlay(R1);
	firstPlay(R2);
	firstPlay(R3);
	firstPlay(R4);
	firstPlay(R5);
	firstPlay(R6);
	firstPlay(R7);
	firstPlay(R8);
	//--------------------------
	_delay_ms(1000);
	reset();
	//--------------------------
	secondPlay(C1);
	secondPlay(C2);
	secondPlay(C3);
	secondPlay(C4);
	secondPlay(C5);
	secondPlay(C6);
	secondPlay(C7);
	secondPlay(C8);
	
	DDRC &= ~(1 << PINC0);//Up
	DDRD &= ~(1 << PIND7);//Down
	DDRD &= ~(1 << PIND5);//Right
	DDRD &= ~(1 << PIND6);//Left
	
	PORTC |= 1 << PINC0;
	PORTD |= 1 << PIND7;
	PORTD |= 1 << PIND5;
	PORTD |= 1 << PIND6;
	
	//DDRB |= 1 << PINB0;
	//DDRB &= ~(1<<PINB1);
	//PORTB |= 1 << PINB1;
	//
	//if(bit_is_clear(PINB,1))
	//{
		////Do This
	//}
	//else
	//{
		////Do That
	//}				
	while(1)
	{
		//TODO:: Please write your application code 
		ScanButtonUp();
		ScanButtonDown();
		ScanButtonRight();
		ScanButtonLeft();
		
		play();
	}
	
}