/*
 * DotMatrix_Chamran.c
 *
 * Created: 6/5/2019 10:39:52 PM
 *  Author: sajjad
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
 
#define F_CPU 4000000UL

#define checkingPoint 10

uint16_t appleX;
uint16_t appleY;

uint16_t size = 8;

uint16_t i = 1;
uint16_t j = 3;

uint16_t up = 0;
uint16_t down = 0;
uint16_t left = 0;
uint16_t right = 0;

uint16_t goUp = 0;
uint16_t goDown = 0;
uint16_t goLeft = 0;
uint16_t goRight = 0;

uint16_t TIME_1 = 64911;

typedef struct Node;

uint16_t x[3] = { 2 , 2 , 2 };
uint16_t y[3] = { 2 , 3 ,  4 };

ISR (TIMER1_OVF_vect)    // Timer1 ISR
{
	//PORTD ^= (1 << LED);	
	//offPixel(i,j);
	for(uint16_t k = 0; k < 3; k ++ )
	{
		offPixel(x[k],y[k]);
	}
	
	if( goUp == 1)//left
	{
		if( i < 7 )
			i++;
	}
	if( goDown == 1 )//right
	{
		if( i > 0 )
			i--;
	}
	if(goRight == 1)//up
	{
		if( j < 7 )
			j++;
	}
	if(goLeft == 1)//down
	{
		if( j > 0 )
			j--;
	}
	
	x[1] = x[2];
	y[1] = y[2];
	
	x[2] = x[3];
	y[2] = y[3];
	
	x[3] = i;
	y[3] = j;
	
	
	for(uint16_t k = 0; k < 3; k ++ )
	{
		putPixel(x[k],y[k]);
	}
	
	//putPixel(i,j);
	
	TCNT1 = TIME_1;   // for 1 sec at 16 MHz
	//TCNT1 = 31987;
}


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


//PORTB Columns
//PORTC Rows

void firstGame()
{
	for(uint16_t i=0;i<size;i++)
	{
		PORTC |= 1 << i;
		for(uint16_t j=0;j<size;j++)
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
	for(uint16_t i=0;i<size;i++)
	{
		
		PORTB &= ~(1 << i);
		for(uint16_t j=0;j<size;j++)
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

void putPixel(uint16_t x,uint16_t y)
{
	PORTB &= ~(1 << x);
	PORTC |= 1 << y;
}

void offPixel(uint16_t x,uint16_t y)
{
	PORTB |= (1 << x);
	PORTC &= ~(1 << y);
}



void makeAllFalse()
{
	goUp = goDown = goLeft = goRight = 0;
}

int main(void)
{
	//disable JTAG
	MCUCSR = (1 << JTD);
	MCUCSR = (1 << JTD);
	
	goRight = 1;
	
	init();
	adc_init();
	
	
	// Set timer1_counter to the correct value for our interrupt interval
    //timer1_counter = 64911;   // preload timer 65536-16MHz/256/100Hz
    //timer1_counter = 64286;   // preload timer 65536-16MHz/256/50Hz
    //timer1_counter = 34286;   // preload timer 65536-16MHz/256/2Hz
	//TCNT1 = 63974;   // for 1 sec at 16 MHz	
	TCNT1 = TIME_1;

	TCCR1A = 0x00;
	TCCR1B = (1<<CS10) | (1<<CS12);;  // Timer mode with 1024 prescler
	TIMSK = (1 << TOIE1) ;   // Enable timer1 overflow interrupt(TOIE1)
	sei();        // Enable global interrupts by setting global interrupt enable bit in SREG
	
	//PORTC |= 1 << PINC7;
	//PORTB &= ~(1 << PINB0);
	
	uint16_t adc_result0, adc_result1;
	
	putPixel(i,j);
	
    while(1)
    {
		
        //TODO:: Please write your application code 
		adc_result0 = adc_read(0);
        adc_result1 = adc_read(1);

		
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
		
		//----------------------------
		
		if(up > checkingPoint)
		{
			makeAllFalse();
			goUp = 1;
				
			up = 0;
		}
		
		if(down > checkingPoint)
		{
			makeAllFalse();
			goDown = 1;
			
			down = 0;
		}
		
		if(right > checkingPoint)
		{
			makeAllFalse();
			goRight = 1;
			
			right = 0;
		}
		
		if(left > checkingPoint)
		{
			makeAllFalse();
			goLeft = 1;
			
			left = 0;
		}
		
		
		
    }
}