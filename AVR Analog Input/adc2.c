//getting the full 10 bits from the ADC
#include <avr/io.h>
#include <avr/interrupt.h>

char adcResult[4];

int main(void)
{
	//Configuring the ADC
	ADCSRA |= 1 << ADPS2;
	ADMUX  |= 1 << ADLAR;
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
	uint8_t theLow = ADCL;
	uint16_t tenBitValue = ADCH << 2 | theLow;

	itoa(tenBitValue,adcResult,10);
	//Send_A_String(adcResult);
	//Send_A_String(" ");

	ADCSRA |= 1 << ADSC;
}