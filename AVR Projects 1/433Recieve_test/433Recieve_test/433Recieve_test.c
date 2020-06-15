/*
 * _915Mhz_Rx_Car_2.c
 *
 * Created: 1/18/2018 7:49:42 PM
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

//#define PINC1 input1
//#define PIND7 input2
//#define PIND2 input3
//#define PIND4 input4

//int PWM_Counter = 200;//PWM Counter for Increase Or Decrease
int PWM_Counter = 255;
int NoCommand = 0;

void setPWMOutput(int duty)
{
	OCR0 = duty;
}

void wait()
{
	_delay_loop_2(3200);
}



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
				if( data == LEDON1)
				{
					//PORTC&=~(1<<0);//LED ON
					//PORTC |= 1 << PINC0;
					//#define PINC1 input1
					//#define PIND7 input2
					//#define PIND2 input3
					//#define PIND4 input4
					
					
					//PORTC |= 1 << PINC1;
					//PORTD |= 1 << PIND2;
					PORTB |= 1 << PINB0;
					
					//justTurnOn();

				}
				else if(data == LEDOFF1)
				{
					//PORTC|=(1<<0);//LED OFF
					//PORTC &= ~(1 << PINC0);
					
					//PORTC &= ~(1 << PINC1);
					//PORTD &= ~(1 << PIND2);
					
					PORTB &= ~(1 << PINB0);
					
					//justTurnOff();
				}
				else if(data == LEDON2)
				{
					//PORTC |= 1 << PINC1;
					//#define PINC1 input1
					//#define PIND7 input2
					//#define PIND2 input3
					//#define PIND4 input4
					
					//PORTD |= 1 << PIND7;
					//PORTD |= 1 << PIND4;
					
					PORTB |= 1 << PINB1;
					
					//justTurnOn();
				}
				else if(data == LEDOFF2)
				{
					//PORTC &= ~ (1 << PINC1);
					
					//PORTD &= ~(1 << PIND7);
					//PORTD &= ~(1 << PIND4);
					
					PORTB &= ~(1 << PINB1);
					
					//justTurnOff();
				}
				else if(data == LEDON3)
				{
					//PORTA |= 1 << PINA7;
					
					//PORTC |= 1 << PINC1;
					//PORTD |= 1 << PIND4;
					
					PORTB |= 1 << PINB2;
					
					//justTurnOn();
				}
				else if(data == LEDOFF3)
				{
					//PORTA &= ~ (1 << PINA7);
					
					//PORTC &= ~(1 << PINC1);
					//PORTD &= ~(1 << PIND4);
					
					PORTB &= ~(1 << PINB2);
					
					
					//justTurnOff();
				}
				else if(data == LEDON4)
				{
					//PORTC |= 1 << PINC6;
					
					//PORTD |= 1 << PIND2;
					//PORTD |= 1 << PIND7;
					
					PORTB |= 1 << PINB3;
					
					//justTurnOn();
				}
				else if(data == LEDOFF4)
				{
					//PORTC &= ~ (1 << PINC6);
					
					//PORTD &= ~(1 << PIND2);
					//PORTD &= ~(1 << PIND7);
					
					PORTB &= ~(1 << PINB3);
				
					//justTurnOff();
				}
				else
				{
					//blink led as error
					PORTD |=   1 << PIND6;//LED OFF
					_delay_ms(1000);
					PORTD &= ~(1<< PIND6);//LED ON	
				} 
			}
	}
	else
	{
		//if you don't send command to car it automatically stop
		//C0
		//C1
		//A7
		//C6
		
		NoCommand++;
		if(NoCommand > 200)
		{
			PORTB &= ~(1 << PINB0);
			PORTB &= ~(1 << PINB1);
			PORTB &= ~(1 << PINB2);
			PORTB &= ~(1 << PINB3);
			NoCommand = 0;
		}
		
		
	}
}

void justTurnOn()
{
	PORTD |= 1 << PIND6;	
}

void justTurnOff()
{
	PORTD &= ~(1 << PIND6);
}

void turnOnSign()
{
	/*
	//PINC0
	PORTC |= 1 << PINC0;
	_delay_ms(500);
	PORTC &= ~(1 << PINC0);
	
	//PINC1
	PORTC |= 1 << PINC1;
	_delay_ms(500);
	PORTC &= ~(1 << PINC1);
	
	//PINA7
	PORTA |= 1 << PINA7;
	_delay_ms(500);
	PORTA &= ~(1 << PINA7);
	
	//PINC6
	PORTC |= 1 << PINC6;
	_delay_ms(500);
	PORTC &= ~(1 << PINC6);
	*/
	
	
	
	//PIND6
	PORTD |= 1 << PIND6;
	_delay_ms(1000);
	PORTD &= ~(1 << PIND6);
}
void Main_Init(void)
{
	//DDRC |= 1 << PINC0;//Up Button
	//DDRC |= 1 << PINC1;//Down Button
	//
	//DDRA |= 1 << PINA7;//Right Button
	//DDRC |= 1 << PINC6;//Left Button
	//
	//DDRD |= 1 << PIND6;//Turn On Sign
	//
	//DDRB |= 1 << PINB3;//PWM OUTPUT for Enable A And Enable B
	
	
	
	//DDRC |= 1 << PINC1;//Up Button
	//DDRD |= 1 << PIND7;//Down Button
	
	//DDRD |= 1 << PIND2;//Right Button
	//DDRD |= 1 << PIND4;//Left Button
	
	//DDRD |= 1 << PIND6;//Turn On Sign
	
	//DDRB |= 1 << PINB3;//PWM OUTPUT for Enable A And Enable B
	
	DDRB |= 1 << PINB0;
	DDRB |= 1 << PINB1;
	DDRB |= 1 << PINB2;
	DDRB |= 1 << PINB3;
	
	DDRD |= 1 << PIND6;
	
	turnOnSign();
	
	//PORTC|=(1<<0);//LED OFF
	//DDRC=0X001;//define port C pin 0 as output;
	//enable global interrupts
	//sei();
}

void initPWM()
{
	TCCR0 |= 1 << WGM00 | 1 << WGM01 | 1 << CS00 | 1 << COM01;
	
	setPWMOutput(PWM_Counter);
}	

int main(void)
{
	
	
	Main_Init();
	//initPWM();
	USART_Init();
	while(1)
	{
		looping();
	}
	//nothing here interrupts are working
	return 0;
}
