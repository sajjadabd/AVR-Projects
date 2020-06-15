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
#define F_CPU 8000000
#endif
//set desired baud rate
#define BAUDRATE 9600
//calculate UBRR value
#define UBRRVAL ((F_CPU/(BAUDRATE*16UL))-1)
//define receive parameters

#define SYNC 0XAA// synchro signal

#define RADDR 0x44

#define LEDON1 0x01//LED on command
#define LEDON2 0x02

#define LEDOFF1 0x03
#define LEDOFF2 0x05//LED off command


#define LEDON3 0x06//LED on command
#define LEDON4 0x07

#define LEDOFF3 0x08
#define LEDOFF4 0x09//LED off command

//PB4 IN4
//PB3 IN3
//PB2 IN2
//PB1 IN1


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

void makeAllOff()
{
	//PB4 IN4
	//PB3 IN3
	//PB2 IN2
	//PB1 IN1
	PORTB &= ~(1 << PINB1);
	PORTB &= ~(1 << PINB2);		
	PORTB &= ~(1 << PINB3);
	PORTB &= ~(1 << PINB4);
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
				if(data==LEDON1) // forward
				{
					//PORTC&=~(1<<0);//LED ON
					PORTC |= 1 << PINC5; // forward LED
					
					//PB4 IN4
					//PB3 IN3
					//PB2 IN2
					//PB1 IN1
					PORTB &= ~(1 << PINB4);
					PORTB &= ~(1 << PINB2);
					
					PORTB |= (1 << PINB1);
					PORTB |= (1 << PINB3);
				}
				else if(data==LEDOFF1)
				{
					//PORTC|=(1<<0);//LED OFF
					PORTC &= ~(1 << PINC5);
					makeAllOff();
				}
				else if(data == LEDON2) // backward
				{
					PORTC |= 1 << PINC4; // backward LED
					
					//PB4 IN4
					//PB3 IN3
					//PB2 IN2
					//PB1 IN1
					PORTB |= (1 << PINB4);
					PORTB |= (1 << PINB2);
					
					PORTB &= ~(1 << PINB3);
					PORTB &= ~(1 << PINB1);
				}
				else if(data == LEDOFF2)
				{
					PORTC &= ~ (1 << PINC4);
					makeAllOff();
				}
				else if(data == LEDON3) // right
				{
					PORTC |= 1 << PINC3; // right LED
					
					//PB4 IN4
					//PB3 IN3
					//PB2 IN2
					//PB1 IN1
					PORTB |= (1 << PINB4);
					PORTB &= ~(1 << PINB3);
					
					PORTB &= ~(1 << PINB2);
					PORTB |= (1 << PINB1);
				}
				else if(data == LEDOFF3)
				{
					PORTC &= ~ (1 << PINC3);
					makeAllOff();
				}
				else if(data == LEDON4) // left
				{
					PORTC |= 1 << PINC2; // left LED
					
					//PB4 IN4
					//PB3 IN3
					//PB2 IN2
					//PB1 IN1
					PORTB &= ~(1 << PINB4);
					PORTB |= (1 << PINB3);
					
					PORTB |= (1 << PINB2);
					PORTB &= ~(1 << PINB1);
				}
				else if(data == LEDOFF4)
				{
					PORTC &= ~ (1 << PINC2);
					makeAllOff();
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
	DDRC |= 1 << PINC5;//forward  LED
	DDRC |= 1 << PINC4;//backward LED
	DDRC |= 1 << PINC3;//right    LED 
	DDRC |= 1 << PINC2;//left     LED
	
	
	//PB4 IN4
	//PB3 IN3
	//PB2 IN2
	//PB1 IN1
	DDRC |= 1 << PINB1;
	DDRC |= 1 << PINB2;
	DDRC |= 1 << PINB3;
	DDRD |= 1 << PINB4;
	
	makeAllOff();
	//PORTC|=(1<<0);//LED OFF
	//DDRC=0X001;//define port C pin 0 as output;
	//enable global interrupts
	//sei();
}
int main(void)
{
	//disable JTAG
	//MCUCSR = (1 << JTD);
	//MCUCSR = (1 << JTD);
	
	Main_Init();
	USART_Init();
	while(1)
	{
		looping();
	}
	//nothing here interrupts are working
	return 0;
}
