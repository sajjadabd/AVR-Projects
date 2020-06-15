/*
 * ledPWM1.c
 *
 * Created: 1/23/2019 1:42:40 AM
 *  Author: sajjad
 */ 


#include <avr/io.h>
#include <util/delay.h>

//#define F_CPU 1000000UL
#define F_CPU 1000000UL

//OCR1A = 25;
//OCR1B = 50;
//OCR0  = 75;
//OCR2  = 100;

void initPWM2(){
    //TIMER0 (8 bit timer)
    //set pins 5D(OC0B) and 6D(OC0A) as output
    DDRD |= 1<<DDD5 | 1<<DDD6 | 1 << DDD5;
    //set fast-pwm mode
    TCCR0 |= 1<<WGM00;
    //set non-inverting mode for both pins
    TCCR0 |= 1<<COM01 | 1<<COM01;
    //set prescaler to 256
    TCCR0 |= 1<<CS02;

    //TIMER2 (8 bit timer)
    //set pins 3D(OC2B) as output
    DDRD |= 1<<DDD3;
    //set fast-pwm mode
    TCCR2 |= 1<<WGM20;
    //set non-inverting mode for both pins
    TCCR2 |= 1<<COM21;
    //set prescaler to 256
    TCCR2 |= 1<<CS22 | 1<<CS21;
}

void initPWM()
{
	TCCR0 |= 1 << WGM00 | 1 << WGM01 | 1 << CS00 | 1 << COM01;
	
	DDRB |= 1 << PINB3;
	
	//DDRC |= (1 << PC5) | (1 << PC4);
	
	//DDRD |= 1 << PIND4;
	
	//DDRD |= 1 << PINB3;
}

void setPWMOutput(int duty)
{
	// D3   D5    D6   B3
	OCR0 = duty;
	//INT1 = duty;
	//D3
	//OCR1B = duty;
	//OCR1A = duty;
	//ICP1 = duty;
}

void setPWMOutputD4(int duty)
{
	OCR1B = duty;
}

int main(void)
{
	initPWM();
	// D3   D5    D6   B3
    while(1)
    {
        //TODO:: Please write your application code
		
		for(int i=0;i<255;i++)
		{
			setPWMOutput(i);
			_delay_ms(5);
		}			 
		
		for(int i=255;i>0;i--)
		{
			setPWMOutput(i);
			_delay_ms(5);
		}			
    }
}