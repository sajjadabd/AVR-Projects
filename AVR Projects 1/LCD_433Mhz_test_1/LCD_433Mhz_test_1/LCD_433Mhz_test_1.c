/*
 * _4_LCD1.c
 *
 * Created: 11/7/2017 1:41:59 AM
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


#define FIRST PINA0
#define SECOND PINA1
#define THIRD PINA2
#define FOURTH PINA3



#define MrLCDsCrib PORTB
#define DataDir_MrLCDsCrib DDRB

#define MrLCDsControl PORTD
#define DataDir_MrLCDsControl DDRD

#define LightSwitch 5
#define ReadWrite 7
#define BiPolarMood 2

void Check_IF_MrLCD_isBusy(void);
void Peek_A_Boo(void);
void Send_A_Command(unsigned char command);
void Send_A_Character(unsigned char character);
void Send_A_String(char *StringOfCharacters);

char firstColumnPosition[4] = {0,64,20,84};
	
int NoCommand = 0;


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
					PORTA |= 1 << FIRST;
					cls(); 
					Send_A_String("address : ");
					Send_A_String(RADDR);
					GotoLocation(-1,1);
					Send_A_String(" data : ");
					Send_A_String(data);
					//Send_A_String("address : " + RADDR + " -- data : " + data);
					//justTurnOn();

				}
				else if(data == LEDOFF1)
				{
					//PORTC|=(1<<0);//LED OFF
					//PORTC &= ~(1 << PINC0);
					
					//PORTC &= ~(1 << PINC1);
					//PORTD &= ~(1 << PIND2);
					
					PORTA &= ~(1 << FIRST);
					cls(); 
					Send_A_String("address : ");
					Send_A_String(RADDR);
					GotoLocation(-1,1);
					Send_A_String(" data : ");
					Send_A_String(data);
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
					
					PORTA |= 1 << SECOND;
					cls(); 
					Send_A_String("address : ");
					Send_A_String(RADDR);
					GotoLocation(-1,1);
					Send_A_String(" data : ");
					Send_A_String(data);
					//justTurnOn();
				}
				else if(data == LEDOFF2)
				{
					//PORTC &= ~ (1 << PINC1);
					
					//PORTD &= ~(1 << PIND7);
					//PORTD &= ~(1 << PIND4);
					
					PORTA &= ~(1 << SECOND);
					cls(); 
					Send_A_String("address : ");
					Send_A_String(RADDR);
					GotoLocation(-1,1);
					Send_A_String(" data : ");
					Send_A_String(data);
					//justTurnOff();
				}
				else if(data == LEDON3)
				{
					//PORTA |= 1 << PINA7;
					
					//PORTC |= 1 << PINC1;
					//PORTD |= 1 << PIND4;
					
					PORTA |= 1 << THIRD;
					cls(); 
					Send_A_String("address : ");
					Send_A_String(RADDR);
					GotoLocation(-1,1);
					Send_A_String(" data : ");
					Send_A_String(data);
					//justTurnOn();
				}
				else if(data == LEDOFF3)
				{
					//PORTA &= ~ (1 << PINA7);
					
					//PORTC &= ~(1 << PINC1);
					//PORTD &= ~(1 << PIND4);
					
					PORTA &= ~(1 << THIRD);
					cls(); 
					Send_A_String("address : ");
					Send_A_String(RADDR);
					GotoLocation(-1,1);
					Send_A_String(" data : ");
					Send_A_String(data);
					
					//justTurnOff();
				}
				else if(data == LEDON4)
				{
					//PORTC |= 1 << PINC6;
					
					//PORTD |= 1 << PIND2;
					//PORTD |= 1 << PIND7;
					
					PORTA |= 1 << FOURTH;
					cls(); 
					Send_A_String("address : ");
					Send_A_String(RADDR);
					GotoLocation(-1,1);
					Send_A_String(" data : ");
					Send_A_String(data);
					//justTurnOn();
				}
				else if(data == LEDOFF4)
				{
					//PORTC &= ~ (1 << PINC6);
					
					//PORTD &= ~(1 << PIND2);
					//PORTD &= ~(1 << PIND7);
					
					PORTA &= ~(1 << FOURTH);
					cls(); 
					Send_A_String("address : ");
					Send_A_String(RADDR);
					GotoLocation(-1,1);
					Send_A_String(" data : ");
					Send_A_String(data);
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
			PORTA &= ~(1 << PINA0);
			PORTA &= ~(1 << PINA1);
			PORTA &= ~(1 << PINA2);
			PORTA &= ~(1 << PINA3);
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
	
	DDRA |= 1 << PINA0;
	DDRA |= 1 << PINA1;
	DDRA |= 1 << PINA2;
	DDRA |= 1 << PINA3;
	
	DDRD |= 1 << PIND6;
	
	turnOnSign();
	
	//PORTC|=(1<<0);//LED OFF
	//DDRC=0X001;//define port C pin 0 as output;
	//enable global interrupts
	//sei();
}


	
void GotoLocation(uint8_t x, uint8_t y)
{
	Send_A_Command(0x80 + firstColumnPosition[y] + x);
}

void cls()
{
	Send_A_Command(0x01); //Clear Screen 0x01 = 00000001
	_delay_ms(2);
}

int main(void)
{
	DataDir_MrLCDsControl |= 1<<LightSwitch | 1<<ReadWrite | 1<<BiPolarMood;
	_delay_ms(15);

	Send_A_Command(0x01); //Clear Screen 0x01 = 00000001
	_delay_ms(2);
	
	Send_A_Command(0x38);
	_delay_us(50);
	
	Send_A_Command(0b00001110);//fixed cursor
	//Send_A_Command(0b00001111);//blinked cursor
	_delay_us(50);
	
	
	
	//Send_A_Command(0b00000000);
	//_delay_us(50);
	
	Main_Init();
	//initPWM();
	USART_Init();

	Send_A_String("Welcome to Hack_World");

	while(1)
	{
		looping();
	}
}

void Check_IF_MrLCD_isBusy()
{
	DataDir_MrLCDsCrib = 0;
	MrLCDsControl |= 1<<ReadWrite;
	MrLCDsControl &= ~1<<BiPolarMood;

	while (MrLCDsCrib >= 0x80)
	{
	Peek_A_Boo();
	}

	DataDir_MrLCDsCrib = 0xFF; //0xFF means 0b11111111
}
void Peek_A_Boo()
{
	MrLCDsControl |= 1<<LightSwitch;
	asm volatile ("nop");
	asm volatile ("nop");
	MrLCDsControl &= ~1<<LightSwitch;
}

void Send_A_Command(unsigned char command)
{
	Check_IF_MrLCD_isBusy();
	MrLCDsCrib = command;
	MrLCDsControl &= ~ ((1<<ReadWrite)|(1<<BiPolarMood));
	Peek_A_Boo();
	MrLCDsCrib = 0;
}

void Send_A_Character(unsigned char character)
{
	Check_IF_MrLCD_isBusy();
	MrLCDsCrib = character;
	MrLCDsControl &= ~ (1<<ReadWrite);
	MrLCDsControl |= 1<<BiPolarMood;
	Peek_A_Boo();
	MrLCDsCrib = 0;
}

void Send_A_String(char *StringOfCharacters)
{
	while(*StringOfCharacters > 0)
	{
		Send_A_Character(*StringOfCharacters++);
	}
}