#include <avr/io.h>
#include <util/delay.h>

#define KeypadDirectionRegister DDRC
#define KeypadPortControl PORTC
#define KeypadPortValue PINC

#define MrLCDsCrib PORTB
#define DataDir_MrLCDsCrib DDRB

#define MrLCDsControl PORTD
#define DataDir_MrLCDsControl DDRD

#define LightSwitch 5
#define ReadWrite 7
#define BiPolarMood 2


char firstColumnPosition[4] = {0,64,20,84};

int pressed = 0;

int on = 0;
//int printed = 0;

void Check_IF_MrLCD_isBusy(void);
void Peek_A_Boo(void);
void Send_A_Command(unsigned char command);
void Send_A_Character(unsigned char character);
void Send_A_String(char *string);


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
			PORTC ^= 1 << PINC0;//LED PORT
			_delay_ms(100);
			PORTC ^= 1 << PINC0;//LED PORT
			_delay_ms(100);
		}
			
	}
	
}



void print()
{
	if (on == 0)
	{
		//on = 1;//you should not change on here and in ScanButton is enough
		//cls();
		GotoLocation(0,0);
		Send_A_String("                 ");
		GotoLocation(0,0);
		Send_A_String("Lamp Turned OFF!");
	}
	else if(on == 1)
	{
		//on = 0;//you should not change on here and in ScanButton in enough
		//cls();
		GotoLocation(0,0);
		Send_A_String("                 ");
		GotoLocation(0,0);
		Send_A_String("Lamp Turned ON!");
	}

}


void ScanButton()
{
	
	
	if(bit_is_clear(PINC, 1))
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
		if(bit_is_clear(PINC,1))
		{
			//Do Nothing
		}
		else
		{
			PORTC ^= 1 << PINC0;
			
			if(on == 0)
			{
				on = 1;
				print();
		    }
			else if (on == 1)
			{
				on = 0;
				print();
			}			
				
			//printed = 0;
			
			pressed = 0;					
		}
	}
}

/*
void blink()
{
	PORTB ^= 1 << PINB0;
	_delay_ms(1000);
}
*/


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
void Send_A_String(char *Str)
{
	while(*Str > 0)
	{
		Send_A_Character(*Str++);
	}
}

void GotoLocation(uint8_t x, uint8_t y)
{
	Send_A_Command(0x80 + firstColumnPosition[y] + x);
}

void cls()
{
	Send_A_Command(0x01);
}

int main(void)
{
	KeypadDirectionRegister = 0b00001111;
	KeypadPortControl = 0b11110000;
	
	DDRC |= 1 << PINC0;
	DDRC &= ~(1 << PINC1);
	PORTC |= 1 << PINC1;
	//PORTB ^= 1 << PINB0;
	
	DataDir_MrLCDsControl |= 1<<LightSwitch | 1<<ReadWrite | 1<<BiPolarMood;
	_delay_ms(15);

	Send_A_Command(0x01); //Clear Screen 0x01 = 00000001
	_delay_ms(2);
	Send_A_Command(0x38);
	_delay_us(50);
	Send_A_Command(0b00001111);//last 1 is for blinking cursor
	_delay_us(50);

	/*
	Send_A_Character(0x4E); //N
	//blink();
	Send_A_Character(0x65); //e
	//blink();
	Send_A_Character(0x77); //w
	//blink();
	Send_A_Character(0x62); //b
	//blink();
	Send_A_Character(0x69); //i
	//blink();
	Send_A_Character(0x65); //e
	//blink();
	Send_A_Character(0x48); //H
	//blink();
	Send_A_Character(0x61); //a
	//blink();
	Send_A_Character(0x63); //c
	//blink();
	Send_A_Character(0x6B); //k
	//blink();
	Send_A_Character(0x2E); //.
	//blink();
	Send_A_Character(0x63); //c
	//blink();
	Send_A_Character(0x6F); //o
	//blink();
	Send_A_Character(0x6D); //m
	//blink();
	*/
	Send_A_String("Welcome to AVR!");

	while(1)
	{
		KeypadScan();
		ScanButton();
		
	}
}
