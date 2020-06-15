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
#define BAUDRATE 9600
//calculate UBRR value
#define UBRRVAL ((F_CPU/(BAUDRATE*16UL))-1)
//define receive parameters
#define SYNC 0XAA// synchro signal

#define RADDR 0x44

#define LEDON1 0x01//switch led on command
#define LEDON2 0x02

#define LEDOFF1 0x03//switch led off command
#define LEDOFF2 0x05

#define LEDON3 0x06//switch led on command
#define LEDON4 0x07

#define LEDOFF3 0x08//switch led off command
#define LEDOFF4 0x09

#define checkingPoint 10

int pressed1 = 0;
int pressed2 = 0;
int pressed3 = 0;
int pressed4 = 0;

int pressed1_off = 0;
int pressed2_off = 0;
int pressed3_off = 0;
int pressed4_off = 0;

int on1 = 0;
int on2 = 0;
int on3 = 0;
int on4 = 0;

// initialize adc
void adc_init()
{
    // AREF = AVcc
    ADMUX = (1<<REFS0);
 
    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}
 
// read adc value
uint16_t adc_read(uint8_t ch)
{
    // select the corresponding channel 0~7
    // ANDing with '7' will always keep the value
    // of 'ch' between 0 and 7
	
    ch &= 0b00000111;  // AND operation with 7
    ADMUX = (ADMUX & 0xF8)|ch;     // clears the bottom 3 bits before ORing
 
    // start single conversion
    // write '1' to ADSC
    ADCSRA |= (1<<ADSC);
 
    // wait for conversion to complete
    // ADSC becomes '0' again
    // till then, run loop continuously
    while(ADCSRA & (1<<ADSC));
 
    return (ADC);
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


/*

void ScanButton4()
{
	if(bit_is_clear(PINB, 4))
	{
		if(pressed4 >= checkingPoint)
		{
			pressed4 = checkingPoint;
			
			for(int k=0;k<10;k++)
				Send_Packet(RADDR, LEDON4);
				
			pressed4 = 0;
		}
		else
		{
			pressed4++;
		}							
	}
	else
	{
		if(pressed4_off >= checkingPoint)
		{
			pressed4_off = checkingPoint;
			
			for(int k=0;k<10;k++)
				Send_Packet(RADDR, LEDOFF4);
				
			pressed4_off = 0;
		}
		else
		{
			pressed4_off++;
		}
		
	}			
}


void ScanButton3()
{
	if(bit_is_clear(PINB, 3))
	{
		if(pressed3 >= checkingPoint)
		{
			pressed3 = checkingPoint;
			
			for(int k=0;k<10;k++)
				Send_Packet(RADDR, LEDON3);
				
			pressed3 = 0;	
		}
		else
		{
			pressed3++;
		}							
	}	
	else
	{
		if(pressed3_off >= checkingPoint)
		{
			pressed3_off = checkingPoint;
			
			for(int k=0;k<10;k++)
				Send_Packet(RADDR, LEDOFF3);
				
			pressed3_off = 0;
		}
		else
		{
			pressed3_off++;
		}
		
	}		
}



void ScanButton2()
{
	if(bit_is_clear(PINB, 2))
	{
		if(pressed2 >= checkingPoint)
		{
			pressed2 = checkingPoint;
			
			for(int k=0;k<10;k++)
				Send_Packet(RADDR, LEDON2);
				
			pressed2 = 0;	
			
		}
		else
		{
			pressed2++;
		}							
	}	
	else
	{
		if(pressed2_off >= checkingPoint)
		{
			pressed2_off = checkingPoint;
			
			for(int k=0;k<10;k++)
				Send_Packet(RADDR, LEDOFF2);
				
			pressed2_off = 0;
		}
		else
		{
			pressed2_off++;
		}
		
	}		
}

void ScanButton1()
{
	
	if(bit_is_clear(PINB, 1))
	{
		if(pressed1 >= checkingPoint)
		{
			pressed1 = checkingPoint;
			
			for(int k=0;k<10;k++)
				Send_Packet(RADDR, LEDON1);
				
			pressed1 = 0;	
			
		}
		else
		{
			pressed1++;
		}							
	}	
	else
	{
		if(pressed1_off >= checkingPoint)
		{
			pressed1_off = checkingPoint;
			
			for(int k=0;k<10;k++)
				Send_Packet(RADDR, LEDOFF1);
				
			pressed1_off = 0;
		}
		else
		{
			pressed1_off++;
		}
		
	}		
}
*/

int main(void)
{
	
	USART_Init();
	
	//DDRB |= 1 << PINB0;
	//DDRB &= ~(1 << PINB1);
	//DDRB &= ~(1 << PINB2);
	
	//DDRB &= ~(1 << PINB3);
	//DDRB &= ~(1 << PINB4);
	
	//PORTB |= 1 << PINB1;
	//PORTB |= 1 << PINB2;
	
	//PORTB |= 1 << PINB3;
	//PORTB |= 1 << PINB4;
	
	uint16_t adc_result0, adc_result1;
	
	adc_init();
	
	while(1)
	{
		adc_result0 = adc_read(2);      // read adc value at PC2
        adc_result1 = adc_read(3);      // read adc value at PC3
		
		if(adc_result0 > 900)
		{
			for(int k=0;k<10;k++)
				Send_Packet(RADDR, LEDON1);
		}
		else if(adc_result0 < 200)
		{
			for(int k=0;k<10;k++)
				Send_Packet(RADDR, LEDON2);
		}
		else
		{
			for(int k=0;k<10;k++)
				Send_Packet(RADDR, LEDOFF1);
				
			for(int k=0;k<10;k++)
				Send_Packet(RADDR, LEDOFF2);
		}
		
		if(adc_result1 > 900)
		{
			for(int k=0;k<10;k++)
				Send_Packet(RADDR, LEDON3);
		}
		else if(adc_result1 < 200)
		{
			for(int k=0;k<10;k++)
				Send_Packet(RADDR, LEDON4);
		}
		else
		{
			for(int k=0;k<10;k++)
				Send_Packet(RADDR, LEDOFF3);
				
			for(int k=0;k<10;k++)
				Send_Packet(RADDR, LEDOFF4);
		}
		
		//ScanButton1();
		//ScanButton2();
		
		//ScanButton3();
		//ScanButton4();
		
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
