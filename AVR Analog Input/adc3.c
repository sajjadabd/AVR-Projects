//multiple analog Input
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	ADCSRA |= 1 << ADPS2;
	ADMUX  |= (1 << REFS0) | (1 << REFS1);
	//ADMUX  |= 1 << REFS1;
	ADCSRA |= 1 << ADIE;
	ADCSRA |= 1 << ADEN;

	sei();

	//start the convertion
	ADCSRA |= 1 << ADSC;



	while(1)
	{

	}
}

ISR(ADC_vect)
{
	uint8_t theLowADC = ADCL;
	uint16_t theTenBitResults = ADCH<<8 | theLowADC;

	ADCSRA |= 1 << ADSC;
}