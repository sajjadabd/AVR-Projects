/*
 * Arduino1.c
 *
 * Created: 11/22/2017 3:25:05 PM
 *  Author: sajjad
 */ 

#define F_CPU 10000
#include <avr/io.h>

#include <avr/cores/arduino/Arduino.h>
#include <avr/cores/arduino/wiring_private.h>
#include <avr/cores/arduino/wiring.c>
#include <avr/cores/arduino/wiring_digital.c>

#define led PINB0

int main(void)
{
	pinMode(led,OUTPUT);
	
    while(1)
    {
		digitalWrite(led,HIGH);
        delay(1000);
		digitalWrite(led,LOW);
		delay(1000);
    }
}



