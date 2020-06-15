//using multiple channels on the analog
//to digital converter

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	ADCSRA |= 1 << ADPS2;
	ADMUX  |= 1 << REFS0 | 1 << REFS1;
	// 0b1100 0000 (C0)
	// 0b1100 0001 (C1)
	ADCSRA |= 1 << ADIE;
	ADCSRA |= 1 << ADEN;

	sei();

	ADCSRA |= 1 << ADSC;

	while(1)
	{

	}
}

ISR(ADC_vect)
{
	uint8_t theLow = ADCL;
	uint16_t theTenBitResult = ADCH << 8 | theLow;

	switch(ADMUX)
	{
		//case C0:
		case 0xC0:
			//ADMUX = C1;
			ADMUX = 0xC1;
			break;
		//case C1:
		case 0xC1:
			//ADMUX = C0;
			ADMUX = 0xC0;
			break;
		default:
			break;
	}

	/*
	if(ADMUX == 0)
	{
	
	}
	else if (ADMUX == 1)
	{
	
	}
	*/

	ADCSRA |= 1 << ADSC;
}