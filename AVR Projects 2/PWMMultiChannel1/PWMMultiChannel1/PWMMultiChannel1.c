/*
 * PWMMultiChannel1.c
 *
 * Created: 1/23/2019 7:00:37 PM
 *  Author: sajjad
 */ 


#include <avr/io.h>
#include <util/delay.h>

void initPWM()
{
	
	TCCR0 |= 1 << WGM00 | 1 << WGM01 | 1 << CS00 | 1 << COM01;
	
	TCCR1A = (1<<WGM11)|(1<<COM1A1)|(1<<COM1B1);  
	
    TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS12); 
	
	//ICR1 = (F_CPU[MHz] * periode[us] / prescaler) - 1 
    ICR1   = 10;           // periode cca 0.5s / 8 MHz
	
	DDRB |= 1 << PINB3;
	
	DDRD |= 1 << PIND4;
	DDRD |= 1 << PIND5;
	

}

void setPWMOutput(int duty)
{
	OCR0  = duty;
	OCR1A = duty;          // duty cycle = 20 percent
    OCR1B = duty;    
}

int main(void)
{
	initPWM();
	
    while(1)
    {
        //TODO:: Please write your application code 
		for(int i=0;i<255;i++)
		{
			setPWMOutput(i);
			_delay_ms(1);
		}			 
		
		for(int i=255;i>0;i--)
		{
			setPWMOutput(i);
			_delay_ms(1);
		}		
    }
}