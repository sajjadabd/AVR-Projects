
#include <avr/io.h>
#include <util/delay.h>


uint8_t getLength(uint8_t* str)
{
	return strlen(str);
}

int main(void)
{
	DDRA |= 1 << PINA0;
	
	uint8_t buffer[1];
	uint8_t bufferSize = getLength(buffer);
	
	uint8_t getBuffer ;
	
	while(1)
	{
	   
	   // Initialize AVR for use with mirf
	   mirf_init();
	   // Wait for mirf to come up
	   _delay_ms(50);
	   // Activate interrupts
	   inter();
	   //sei();
	   // Configure mirf
	   mirf_config();
	   // Test communication
	   mirf_send(buffer,bufferSize);
	   while (!mirf_data_ready());
	   getBuffer = mirf_get_data(buffer);
	   
	   if ( getBuffer == (uint8_t)"a")
	   {
		   PORTA ^= 1 << PINA0;
	   }
	}
}
