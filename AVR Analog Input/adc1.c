#include <avr/io.h>
#include <avr/interrupt.h>

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
	char adcResult[4];
	itoa(ADCH,adcResult,10);
	//Send_A_String(adcResult);
	//Send_A_String(" ");

	ADCSRA |= 1 << ADSC;
}