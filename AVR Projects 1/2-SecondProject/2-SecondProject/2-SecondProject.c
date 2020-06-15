/*
 * _2_SecondProject.c
 *
 * Created: 11/5/2017 1:29:41 AM
 *  Author: sajjad
 */ 

#define KeypadDirectionRegister DDRA
#define KeypadPortControl PORTA
#define KeypadPortValue PINA


#define LCDPort PORTC
#define LCDDataDirection DDRC

#define LCDControlPort PORTD
#define LCDControlDataDirection DDRD

#define LightSwitch PIND5  // PD5
#define ReadWrite   PIND7  // PD7 , output compare for timer
#define BiPolarMood PIND2  // PD2

//first pin GND
//second pin V+
//third is potentiometer
//4th(RS) go to PD2
//5th(RW) go to PD7
//6th(E) go to PD5(Oscillator output compare pin)


//#define LEDDirectionRegister DDRB
//#define LEDPort PORTB

#include <avr/io.h>
#include <util/delay.h>

int pressed = 0;

void PeekABoo();
void CheckLCDBusyOrNot();

void KeypadScan()
{
	if( KeypadPortValue == 0b11110000 )
		return;

	_delay_ms(50);
	
	//Scan The Keypad

	uint8_t KeyPressCode = KeypadPortValue;

	KeypadDirectionRegister ^= 0b11111111;
	KeypadPortControl ^= 0b11111111;
	
	asm volatile("nop");
	asm volatile("nop");
	
	KeyPressCode |= KeypadPortValue;

	uint8_t blinkDuration = 0;

	switch(KeyPressCode)
	{
		case 0b11101110 :
		blinkDuration = 1;
		break;
		case 0b11011110 :
		blinkDuration = 2;
		break;
		case 0b10111110 :
		blinkDuration = 3;
		break;
		case 0b01111110 :
		blinkDuration = 4;
		break;
		case 0b11101101 :
		blinkDuration = 5;
		break;
		case 0b11011101 :
		blinkDuration = 6;
		break;
		case 0b10111101 :
		blinkDuration = 7;
		break;
		case 0b01111101 :
		blinkDuration = 8;
		break;
		case 0b11101011 :
		blinkDuration = 9;
		break;
		case 0b11011011 :
		blinkDuration = 10;
		break;
		case 0b10111011 :
		blinkDuration = 11;
		break;
		case 0b01111011 :
		blinkDuration = 12;
		break;
		case 0b11100111 :
		blinkDuration = 13;
		break;
		case 0b11010111 :
		blinkDuration = 14;
		break;
		case 0b10110111 :
		blinkDuration = 15;
		break;
		case 0b01110111 :
		blinkDuration = 16;
		break;

	}
	
	
	if(KeyPressCode < 0b11111111 )
	{
		
		for(int i=0;i<blinkDuration;i++)
		{
			PORTB ^= 1 << PINB0;//LED PORT
			_delay_ms(100);
			PORTB ^= 1 << PINB0;//LED PORT
			_delay_ms(100);
		}
		
	}
	
}


void ScanButton()
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
			PORTB ^= 1 << PINB0;
			pressed = 0;					
		}
	}
}

void CheckLCDBusyOrNot()
{
	LCDDataDirection = 0;
	
	
	LCDControlPort |= 1 << ReadWrite;
	LCDControlPort &= ~ (1 << BiPolarMood);
	
	while(LCDPort >= 0x80 ) // D7 PORTB PIN7 is 1 or 0 // 0b10000000 == 0x80
	{
		PeekABoo();
	}
	
	LCDDataDirection = 0xff; // mean 0b11111111;
}

void PeekABoo()
{
	LCDControlPort |= 1 << LightSwitch;
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	LCDControlPort &= ~ (1 << LightSwitch);
}

void SendACommand(unsigned char command)
{
	CheckLCDBusyOrNot();
	
	LCDPort = command;
	
	LCDControlPort &=  ~( (1 << ReadWrite) | (1 << BiPolarMood) );
	
	PeekABoo();
	LCDPort = 0;
}



void SendACharacter(unsigned char character)
{
	CheckLCDBusyOrNot();
	
	LCDPort = character;
	
	LCDControlPort &=  ~(1 << ReadWrite);
	LCDControlPort |= 1 << BiPolarMood;
	
	PeekABoo();
	LCDPort = 0;
}

void SendString(char *Str)
{
	while(*Str > 0)
	{
		SendACharacter(*Str++);
	}
}

void blink()
{
	PORTB ^= 1 << PINB0;
	_delay_ms(100);	
	PORTB ^= 1 << PINB0;
	_delay_ms(100);	
}

void cls()
{
	SendACommand(0x38);
}



int main(void)
{
	//Initialize LED
	//LEDDirectionRegister = 0b00000001;// 1 << PINB0;
	//PORTB |= 1 << PINB0;
	
	//Initialize the Keypad Data Direction And Port Settings
	
	KeypadDirectionRegister = 0b00001111;
	KeypadPortControl = 0b11110000;
	
	
	
	DDRB |= 1 << PINB0;
	DDRB &= ~(1 << PINB1);
	
	PORTB |= 1 << PINB1;
	
	LCDControlDataDirection |= (1 << LightSwitch) | (1 << ReadWrite) | (1 << BiPolarMood);
	
	_delay_ms(15);
	SendACommand(0x01);//clear the screen
	_delay_ms(2);
	SendACommand(0x38);
	_delay_us(50);//MicroSeconds
	SendACommand(0b00000000);
	_delay_us(50);
	
	//SendACharacter(0x4E);
	//SendACharacter(0x4E);
	
	/*
	SendACharacter(0x4E); //N
	SendACharacter(0x65); //e
	SendACharacter(0x77); //w
	SendACharacter(0x62); //b
	SendACharacter(0x69); //i
	SendACharacter(0x65); //e
	SendACharacter(0x48); //H
	SendACharacter(0x61); //a
	SendACharacter(0x63); //c
	SendACharacter(0x6B); //k
	SendACharacter(0x2E); //.
	SendACharacter(0x63); //c
	SendACharacter(0x6F); //o
	SendACharacter(0x6D); //m
	*/
	
	SendString("Welcome to AVR Programming");
	//_delay_ms(2000);
	//SendACommand(0x01);//clear the screen
	
    while(1)
    {
		
		KeypadScan();
		
		
		ScanButton();
		
		
		
			
        //TODO:: Please write your application code 
    }
}