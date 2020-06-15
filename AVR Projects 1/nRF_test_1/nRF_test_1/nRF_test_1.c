/*
 * nRF_test_1.c
 *
 * Created: 2/13/2018 1:41:46 PM
 *  Author: sajjad
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	while(1)
	{
	   // Initialize AVR for use with mirf
	   mirf_init();
	   // Wait for mirf to come up
	   _delay_ms(50);
	   // Activate interrupts
	   sei();
	   // Configure mirf
	   mirf_config();
	   // Test communication
	   mirf_send(buffer,buffersize);
	   while (!mirf_data_ready());
	   mirf_get_data(buffer);
	}
}
