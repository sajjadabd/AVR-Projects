/*
 * _4_LCD1.c
 *
 * Created: 11/7/2017 1:41:59 AM
 *  Author: sajjad
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <math.h>


#define KeypadDirectionRegister DDRA
#define KeypadPortControl PORTA
#define KeypadPortValue PINA

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

void GotoLocation(uint8_t x, uint8_t y)
{
	Send_A_Command(0x80 + firstColumnPosition[y] + x);
}

void cls()
{
	Send_A_Command(0x01); //Clear Screen 0x01 = 00000001
	_delay_ms(2);
}

uint8_t blinkDuration = 0;

int counter = 0;

int count1 = 0; 

int count2 = 0;

int temp = 0;

char operation = 'n';

int result = 0;

int nextOperation = 0;

void DO()
{
	
	if(nextOperation == 1)
	{
		cls();
		
		nextOperation = 0;
	}	
	
	switch (blinkDuration)
	{
		case 1:
			
			if(operation == 'n')
			{
				operation = '-';
				Send_A_String(" - ");
				counter = 0;
			}
			
			break;
		case 2:
			counter = 0;
			
			nextOperation = 1;
			Send_A_String(" = ");
			switch(operation)
			{
				case '+':
				result = count1 + count2 ;
				break;
				case '-':
				result = count1 - count2 ;
				break;
				case '/':
				result = count1 / count2 ;
				break;
				case '%':
				result = count1 % count2 ;
				break;
				case '*':
				result = count1 * count2 ;
				break;
				default:
				break;
			}	
			/*
			switch (result)
			{
				case 1:
					Send_A_String("1");
					break;
				case 2:
					Send_A_String("2");
					break;
				case 3:
					Send_A_String("3");
					break;
				case 4:
					Send_A_String("4");
					break;
				case 5:
					Send_A_String("5");
					break;
				case 6:
					Send_A_String("6");
					break;
				case 7:
					Send_A_String("7");
					break;
				case 8:
					Send_A_String("8");
					break;
				case 9:
					Send_A_String("9");
					break;
				case 10:
					Send_A_String("10");
					break;
				case 11:
					Send_A_String("11");
					break;
				case 12:
					Send_A_String("12");
					break;
				case 13:
					Send_A_String("13");
					break;
				case 14:
					Send_A_String("14");
					break;
				case 15:
					Send_A_String("15");
					break;
				case 16:
					Send_A_String("16");
					break;
				case 17:
					Send_A_String("17");
					break;
				case 18:
					Send_A_String("18");
					break;
				case 19:
					Send_A_String("19");
					break;
				case 20:
					Send_A_String("20");
					break;
				default:
					//Send_A_String("Other");
					
					break;
			}*/
			
			char str[5];
			itoa(result,str,10);
			Send_A_String(str);
			
			
			/*
			_delay_ms(1000);
			cls();
			Send_A_String("count1 : ");
			itoa(count1,str,10);
			Send_A_String(str);
			_delay_ms(1000);
			cls();
			Send_A_String("count2 : ");
			itoa(count2,str,10);
			Send_A_String(str);
			*/
			
			operation = 'n';
			count1 = 0;
			count2 = 0;
			
			break;
		case 3:
			
			if(operation == 'n')
			{
				operation = '*';
				Send_A_String(" * ");
				counter = 0;
			}
			
			break;
		case 4:
			
			if(operation == 'n')
			{
				operation = '+';
				Send_A_String(" + ");
				counter = 0;
			}
			
			break;
		case 5:
			if(operation == 'n')
			{
				if(counter != 0)
					count1 *= 10;
				count1 += 6;
			}
			else
			{
				if(counter != 0)
					count2 *= 10;
				count2 += 6;
			}
			Send_A_String("6");
			counter++;
			break;
		case 6:
			
			if(operation == 'n')
			{
				operation = '%';
				Send_A_String(" % ");
				counter = 0;
			}
			
			break;
		case 7:
			if(operation == 'n')
			{
				if(counter != 0)
					count1 *= 10;
				count1 += 9;
			}
			else
			{
				if(counter != 0)
					count2 *= 10;
				count2 += 9;
			}
			Send_A_String("9");
			counter++;
			break;
		case 8:
			if(operation == 'n')
			{
				if(counter != 0)
					count1 *= 10;
				count1 += 3;
			}
			else
			{
				if(counter != 0)
					count2 *= 10;
				count2 += 3;
			}
			Send_A_String("3");
			counter++;
			break;
		case 9:
			if(operation == 'n')
			{
				if(counter != 0)
					count1 *= 10;
				count1 += 5;
			}
			else
			{
				if(counter != 0)
					count2 *= 10;
				count2 += 5;
			}
			Send_A_String("5");
			counter++;
			break;
		case 10:
			if(operation == 'n')
			{
				if(counter != 0)
					count1 *= 10;
				count1 += 0;
			}
			else
			{
				if(counter != 0)
					count2 *= 10;
				count2 += 0;
			}
			Send_A_String("0");
			counter++;
			break;
		case 11:
			if(operation == 'n')
			{
				if(counter != 0)
					count1 *= 10;
				count1 += 8;
			}
			else
			{
				if(counter != 0)
					count2 *= 10;
				count2 += 8;
			}
			Send_A_String("8");
			counter++;
			break;
		case 12:
			if(operation == 'n')
			{
				if(counter != 0)
					count1 *= 10;
				count1 += 2;
			}
			else
			{
				if(counter != 0)
					count2 *= 10;
				count2 += 2;
			}
			Send_A_String("2");
			counter++;
			break;
		case 13:
			if(operation == 'n')
			{
				if(counter != 0)
					count1 *= 10;
				count1 += 4;
			}
			else
			{
				if(counter != 0)
					count2 *= 10;
				count2 += 4;
			}
			Send_A_String("4");
			counter++;
			break;
		case 14:
			if(operation == 'n')
			{
				operation = '/';
				Send_A_String(" / ");
				counter = 0;
			}			
			
			
			break;
		case 15:
			if(operation == 'n')
			{
				if(counter != 0)
					count1 *= 10;
				count1 += 7;
			}
			else
			{
				if(counter != 0)
					count2 *= 10;
				count2 += 7;
			}
			Send_A_String("7");
			counter++;
			break;
		case 16:
			if(operation == 'n')
			{
				if(counter != 0)
					count1 *= 10;
				count1 += 1;
			}
			else
			{
				if(counter != 0)
					count2 *= 10;
				count2 += 1;
			}
			Send_A_String("1");
			counter++;
			break;
		default:
			break;
	}
	
	
	
	
	_delay_ms(100);
}
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
		DO();
		
	}
	
}


int main(void)
{
	KeypadDirectionRegister = 0b00001111;
	KeypadPortControl = 0b11110000;
	
	
	DataDir_MrLCDsControl |= 1<<LightSwitch | 1<<ReadWrite | 1<<BiPolarMood;
	_delay_ms(15);

	Send_A_Command(0x01); //Clear Screen 0x01 = 00000001
	_delay_ms(2);
	Send_A_Command(0x38);
	_delay_us(50);
	Send_A_Command(0b00001110);
	_delay_us(50);

	Send_A_String("Welcome ...");
	_delay_ms(1000);
	cls();

	while(1)
	{
		KeypadScan();
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