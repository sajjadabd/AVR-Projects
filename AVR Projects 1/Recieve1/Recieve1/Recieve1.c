//AnalogRead
//#Define F_CPU 20000000
//This is For Atmega328p

#include <avr/io.h>
#include <avr/interrupt.h>

double dutyCycle = 0;

void setPWMOutput(int duty)
{
	OCR0 = duty;
	if(duty > 10)
	{
		PORTB ^= 1 << PINB0;
	}
}

int main(void)
{
	DDRD |= 1 << PINB0;
	
	//TCCR0A = (1 << COM0A1) | 1 << (WGM00) | (1 << WGM01);
	//TIMSK0 = (1 << TOIE0);
	TCCR0 |= 1 << WGM00 | 1 << WGM01 | 1 << CS00 | 1 << COM01;
	DDRB |= 1 << PINB3;
	
	setupADC();
	sei();
	
	while(1)
	{
		
	}
}

void setupADC()
{
	ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << MUX2);
	
	// MUX0 MUX1 MUX2 MUX3
	//  1    0    1    0     ------>  for ADC5 (PIN 28)
	
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	//DIDR0 = (1 << ADC5D);
	
	startConvertion();
}

void startConvertion()
{
	ADCSRA |= (1 << ADSC);
}


ISR(TIMER0_OVF_vect)
{
	//OCR0A = dutyCycle;
	setPWMOutput(dutyCycle);
}


ISR(ADC_vect)
{
	dutyCycle = ADC;
	startConvertion();
}