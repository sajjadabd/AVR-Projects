/*
 * _433Mhz_Tx_2.c
 *
 * Created: 12/25/2017 2:09:24 PM
 *  Author: sajjad
 */ 
#include <avr/io.h>
#include <util/delay.h>
#ifndef F_CPU
//define cpu clock speed if not defined
#define F_CPU 8000000
#endif
//set desired baud rate
#define BAUDRATE 1200
//calculate UBRR value
#define UBRRVAL ((F_CPU/(BAUDRATE*16UL))-1)
//define receive parameters
#define SYNC 0XAA// synchro signal

#define RADDR 0x44

#define LEDON1 0x11//switch led on command
#define LEDON2 0x22

#define LEDOFF1 0x33//switch led off command
#define LEDOFF2 0x55

#define LEDON3 0x66//switch led on command
#define LEDON4 0x77

#define LEDOFF3 0x88//switch led off command
#define LEDOFF4 0x99

int pressed = 0;

int on1 = 0;
int on2 = 0;

int on3 = 0;
int on4 = 0;

void ScanButton4()
{
	if(bit_is_clear(PINB, 4))
	{
		if(pressed >= 1000)
		{
			pressed = 500;
		}
		else
		{
			pressed++;
		}							
	}	
		
	if(pressed >= 400)
	{
		if(bit_is_clear(PINB,4))
		{
			//Do Nothing
		}
		else
		{
			//PORTB ^= 1 << PINB0;
			if( on4 == 0 )
			{
				for(int k=0;k<10;k++)
					Send_Packet(RADDR, LEDON4);
				on4 = 1;
			}
			else if( on4 == 1 )
			{
				for(int k=0;k<10;k++)
					Send_Packet(RADDR, LEDOFF4);
				on4 = 0;
			}
			
			pressed = 0;					
		}
	}
}


void ScanButton3()
{
	if(bit_is_clear(PINB, 3))
	{
		if(pressed >= 1000)
		{
			pressed = 500;
		}
		else
		{
			pressed++;
		}							
	}	
		
	if(pressed >= 400)
	{
		if(bit_is_clear(PINB,3))
		{
			//Do Nothing
		}
		else
		{
			//PORTB ^= 1 << PINB0;
			if( on3 == 0 )
			{
				for(int k=0;k<10;k++)
					Send_Packet(RADDR, LEDON3);
				on3 = 1;
			}
			else if( on3 == 1 )
			{
				for(int k=0;k<10;k++)
					Send_Packet(RADDR, LEDOFF3);
				on3 = 0;
			}
			
			pressed = 0;					
		}
	}
}



void ScanButton5()
{
	if(bit_is_clear(PINB, 5))
	{
		if(pressed >= 1000)
		{
			pressed = 500;
		}
		else
		{
			pressed++;
		}							
	}	
		
	if(pressed >= 400)
	{
		if(bit_is_clear(PINB,5))
		{
			//Do Nothing
		}
		else
		{
			//PORTB ^= 1 << PINB0;
			if( on1 == 0 )
			{
				for(int k=0;k<10;k++)
					Send_Packet(RADDR, LEDON2);
				on1 = 1;
			}
			else if( on1 == 1 )
			{
				for(int k=0;k<10;k++)
					Send_Packet(RADDR, LEDOFF2);
				on1 = 0;
			}
			
			pressed = 0;					
		}
	}
}

void ScanButton1()
{
	
	if(bit_is_clear(PINB, 1))
	{
		if(pressed >= 1000)
		{
			pressed = 500;
		}
		else
		{
			pressed++;
		}							
	}	
		
	if(pressed >= 400)
	{
		if(bit_is_clear(PINB,1))
		{
			//Do Nothing
		}
		else
		{
			//PORTB ^= 1 << PINB0;
			if( on2 == 0 )
			{
				for(int k=0;k<10;k++)
					Send_Packet(RADDR, LEDON1);
				on2 = 1;
			}
			else if( on2 == 1 )
			{
				for(int k=0;k<10;k++)
					Send_Packet(RADDR, LEDOFF1);
				on2 = 0;
			}
			
			pressed = 0;					
		}
	}
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
	UCSRB=(1<<TXEN);
}
void USART_vSendByte(uint8_t u8Data)
{
    // Wait if a byte is being transmitted
    while((UCSRA&(1<<UDRE)) == 0);
    // Transmit data
    UDR = u8Data; 
}
void Send_Packet(uint8_t addr, uint8_t cmd)
{
	USART_vSendByte(SYNC);//send synchro byte	
	USART_vSendByte(addr);//send receiver address
	USART_vSendByte(cmd);//send increment command
	USART_vSendByte((addr+cmd));//send checksum
}
void delayms(uint8_t t)//delay in ms
{
	uint8_t i;
	for(i=0;i<t;i++)
		_delay_ms(1);
}
int main(void)
{
	USART_Init();
	
	//DDRB |= 1 << PINB0;
	DDRB &= ~(1 << PINB1);
	DDRB &= ~(1 << PINB5);
	
	DDRB &= ~(1 << PINB3);
	DDRB &= ~(1 << PINB4);
	
	PORTB |= 1 << PINB1;
	PORTB |= 1 << PINB5;
	
	PORTB |= 1 << PINB3;
	PORTB |= 1 << PINB4;
	
	while(1)
	{
		ScanButton1();
		ScanButton5();
		
		ScanButton3();
		ScanButton4();
		//endless transmission
		//send command to switch led ON
		/*
		Send_Packet(RADDR, LEDON);
		delayms(100);
		//send command to switch led ON
		Send_Packet(RADDR, LEDOFF);
		delayms(100);
		*/
	}
	return 0;
}
