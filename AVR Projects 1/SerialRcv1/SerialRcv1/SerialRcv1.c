//SerialRecieve for MicroController
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//#define F_CPU 1000000
#define BAUD  9600
#define BRC   ( (F_CPU/16/BAUD)-1 )

//#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
//#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

#define RX_BUFFER_SIZE 128
char rxBuffer[RX_BUFFER_SIZE];
uint8_t rxReadPos = 0;
uint8_t rxWritePos = 0;

char getChar(void);
char peekChar(void);



int main(void)
{
	
	UBRRH = BRC >> 8;
	UBRRL = BRC ;
	
	UCSRB = 1 << RXEN | 1 << RXCIE;
	UCSRC = 1 << UCSZ1 | 1 << UCSZ0;
	
	DDRB |= 1 << PINB0;
	
	sei();
	
	while(1)
	{
		char c = getChar();
		
		if( c == '1' )
		{
			//sbi(PORTB , PORTB0);
			PORTB ^= 1 << PINB0;
		}
		else if( c == '0' )
		{
			//cbi(PORTB, PORTB0);
			PORTB ^= 1 << PINB0;
		}
	}
}

char peekChar()
{
	char ret = '\0';
	
	if(rxReadPos != rxWritePos)
	{
		ret = rxBuffer[rxReadPos];
		
		
	}
	
	return ret;
}

char getChar()
{
	char ret = '\0';
	if(rxReadPos != rxWritePos )
	{
		ret = rxBuffer[rxReadPos];
		rxReadPos++;
		if(rxReadPos >= RX_BUFFER_SIZE)
		{
			rxReadPos = 0;
		}
	} 
	
	return ret;
}

ISR(USART_RX_vect)
{
	rxBuffer[rxWritePos] = UDR;
	rxWritePos++;
	
	if(rxWritePos >= RX_BUFFER_SIZE )
	{
		rxWritePos = 0;
	}
}

