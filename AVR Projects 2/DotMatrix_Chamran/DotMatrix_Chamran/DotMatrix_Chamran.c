/*
 * DotMatrix_Chamran.c
 *
 * Created: 6/5/2019 10:39:52 PM
 *  Author: sajjad
 */ 


#include <avr/io.h>
#include <util/delay.h>

#define checkingPoint 10

// initialize adc
void adc_init()
{
    // AREF = AVcc
    ADMUX = (1<<REFS0);
 
    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}
 
// read adc value
uint16_t adc_read(uint8_t ch)
{
    // select the corresponding channel 0~7
    // ANDing with '7' will always keep the value
    // of 'ch' between 0 and 7
	
    ch &= 0b00000111;  // AND operation with 7
    ADMUX = (ADMUX & 0xF8)|ch;     // clears the bottom 3 bits before ORing
 
    // start single conversion
    // write '1' to ADSC
    ADCSRA |= (1<<ADSC);
 
    // wait for conversion to complete
    // ADSC becomes '0' again
    // till then, run loop continuously
    while(ADCSRA & (1<<ADSC));
 
    return (ADC);
}

void init()
{
	DDRB |= 1 << PINB0;
	DDRB |= 1 << PINB1;
	DDRB |= 1 << PINB2;
	DDRB |= 1 << PINB3;
	DDRB |= 1 << PINB4;
	DDRB |= 1 << PINB5;
	DDRB |= 1 << PINB6;
	DDRB |= 1 << PINB7;
	
	DDRC |= 1 << PINC0;
	DDRC |= 1 << PINC1;
	DDRC |= 1 << PINC2;
	DDRC |= 1 << PINC3;
	DDRC |= 1 << PINC4;
	DDRC |= 1 << PINC5;
	DDRC |= 1 << PINC6;
	DDRC |= 1 << PINC7;
	
	PORTB |= 1 << 0;
	PORTB |= 1 << 1;
	PORTB |= 1 << 2;
	PORTB |= 1 << 3;
	PORTB |= 1 << 4;
	PORTB |= 1 << 5;
	PORTB |= 1 << 6;
	PORTB |= 1 << 7;
}

//char rows[] = {PINB0,PINB1,PINB2,PINB3,PINB4,PINB5,PINB6,PINB7};
//char cols[] = {PINC7,PINC6,PINC5,PINC4,PINC3,PINC2,PINC1,PINC0};
int size = 8;

//PORTB Columns
//PORTC Rows

void firstGame()
{
	for(int i=0;i<size;i++)
	{
		PORTC |= 1 << i;
		for(int j=0;j<size;j++)
		{
				
			PORTB &= ~(1 << j);
			_delay_ms(100);
			PORTB |= (1 << j);
		}
		PORTC &= ~(1 << i);
		_delay_ms(100);
	}
}

void secondGame()
{
	for(int i=0;i<size;i++)
	{
		
		PORTB &= ~(1 << i);
		for(int j=0;j<size;j++)
		{
			PORTC |= 1 << j;
			_delay_ms(100);
			PORTC &= ~(1 << j);
		}
		
		PORTB |= (1 << i);
		_delay_ms(100);
	}
}

void thirdGame()
{
	putPixel(1,2);
	_delay_ms(1000);
	offPixel(1,2);
		
		
	putPixel(3,4);
	_delay_ms(1000);
	offPixel(3,4);
		
	putPixel(5,6);
	_delay_ms(1000);
	offPixel(5,6);
}

void putPixel(int x,int y)
{
	PORTB &= ~(1 << x);
	PORTC |= 1 << y;
}

void offPixel(int x,int y)
{
	PORTB |= (1 << x);
	PORTC &= ~(1 << y);
}

int up = 0;
int down = 0;
int left = 0;
int right = 0;

int main(void)
{
	//disable JTAG
	MCUCSR = (1 << JTD);
	MCUCSR = (1 << JTD);
	
	init();
	adc_init();
	
	//PORTC |= 1 << PINC7;
	//PORTB &= ~(1 << PINB0);
	
	uint16_t adc_result0, adc_result1;
	
	uint16_t i = 4;
	uint16_t j = 4;
	
	
    while(1)
    {
		
        //TODO:: Please write your application code 
		adc_result0 = adc_read(0);
        adc_result1 = adc_read(1);
		
		
		putPixel(i,j);
		
		if(adc_result0 > 800)
		{
			down++;
		}
		else if(adc_result0 < 200)
		{
			up++;
		}
		else
		{
			up = down = 0;
		}
		
		if(up > checkingPoint)
		{
			offPixel(i,j);
			if( i < 7 )
				i++;
				
			up = 0;
		}
		
		if(down > checkingPoint)
		{
			offPixel(i,j);
			if( i > 0 )
				i--;
			
			down = 0;
		}
		
		if(adc_result1 > 800)
		{
			right++;
		}
		else if(adc_result1 < 200)
		{
			left++;
		}
		else
		{
			right = left = 0;
		}
		
		if(right > checkingPoint)
		{
			offPixel(i,j);
			if( j < 7 )
				j++;
			
			right = 0;
		}
		
		if(left > checkingPoint)
		{
			offPixel(i,j);
			if( j > 0 )
				j--;
			
			left = 0;
		}
		
		
		
    }
}