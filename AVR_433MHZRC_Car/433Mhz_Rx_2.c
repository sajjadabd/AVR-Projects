/*
 * _433Mhz_Rx_2.c
 *
 * Created: 12/25/2017 2:29:50 PM
 *  Author: sajjad
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#ifndef F_CPU
//define cpu clock speed if not defined
#define F_CPU 4000000
#endif
//set desired baud rate
#define BAUDRATE 1200
//calculate UBRR value
#define UBRRVAL ((F_CPU/(BAUDRATE*16UL))-1)
//define receive parameters

#define SYNC 0XAA// synchro signal

#define RADDR 0x44

#define LEDON1 0x11//LED on command
#define LEDON2 0x22

#define LEDOFF1 0x33
#define LEDOFF2 0x55//LED off command


#define LEDON3 0x66//LED on command
#define LEDON4 0x77

#define LEDOFF3 0x88
#define LEDOFF4 0x99//LED off command


void USART_Init(void)
{
	//Set baud rate
	UBRRL=(uint8_t)UBRRVAL;		//low byte
	UBRRH=(UBRRVAL>>8);	//high byte
	//Set data frame format: asynchronous mode,no parity, 1 stop bit, 8 bit size
	UCSRC=(1<<URSEL)|(0<<UMSEL)|(0<<UPM1)|(0<<UPM0)|
		(0<<USBS)|(0<<UCSZ2)|(1<<UCSZ1)|(1<<UCSZ0);	
	//Enable Transmitter and Receiver and Interrupt on receive complete
	UCSRB=(1<<RXEN);//|(1<<RXCIE);//|(1<<TXEN);
	//enable global interrupts

}
uint8_t USART_vReceiveByte(void)
{
    // Wait until a byte has been received
    while((UCSRA&(1<<RXC)) == 0);
    // Return received data
    return UDR;
}
void looping()
{
	//define variables
	uint8_t raddress, data, chk;//transmitter address
	//receive destination address
	raddress=USART_vReceiveByte();
	//receive data
	data=USART_vReceiveByte();
	//receive checksum
	chk=USART_vReceiveByte();
	//compare received checksum with calculated
	if(chk==(raddress+data))//if match perform operations
	{
		//if transmitter address match
		if(raddress==RADDR)
			{
				if(data==LEDON1)
				{
					//PORTC&=~(1<<0);//LED ON
					PORTC |= 1 << PINC0;
				}
				else if(data==LEDOFF1)
				{
					//PORTC|=(1<<0);//LED OFF
					PORTC &= ~(1 << PINC0);
				}
				else if(data == LEDON2)
				{
					PORTC |= 1 << PINC1;
				}
				else if(data == LEDOFF2)
				{
					PORTC &= ~ (1 << PINC1);
				}
				else if(data == LEDON3)
				{
					PORTC |= 1 << PINC4;
				}
				else if(data == LEDOFF3)
				{
					PORTC &= ~ (1 << PINC4);
				}
				else if(data == LEDON4)
				{
					PORTC |= 1 << PINC6;
				}
				else if(data == LEDOFF4)
				{
					PORTC &= ~ (1 << PINC6);
				}
				else
				{
					//blink led as error
					//PORTC|=(1<<0);//LED OFF
					//_delay_ms(10);
					//PORTC&=~(1<<0);//LED ON	
				}
			}
	}
}
void Main_Init(void)
{
	DDRC |= 1 << PINC0;
	DDRC |= 1 << PINC1;
	
	DDRC |= 1 << PINC4;
	DDRC |= 1 << PINC6;
	//PORTC|=(1<<0);//LED OFF
	//DDRC=0X001;//define port C pin 0 as output;
	//enable global interrupts
	//sei();
}
int main(void)
{

	Main_Init();
	USART_Init();
	while(1)
	{
		looping();
	}
	//nothing here interrupts are working
	return 0;
}
