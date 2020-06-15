#include <avr/io.h>
#include <util/delay.h>
 
//#include "lcd.h"
 
#define LTHRES 500
#define RTHRES 500

#define MrLCDsCrib PORTB
#define DataDir_MrLCDsCrib DDRB
#define MrLCDsControl PORTD
#define DataDir_MrLCDsControl DDRD
#define LightSwitch 5   //PIND5
#define ReadWrite 7     //PIND7   RW
#define BiPolarMood 2   //PIND2

char firstColumnPositionsForMrLCD[4] = {0, 64, 20, 84};

//void Check_IF_MrLCD_isBusy(void);
//void Peek_A_Boo(void);
//void Send_A_Command(unsigned char command);
//void Send_A_Character(unsigned char character);
//void Send_A_String(char *StringOfCharacters);
//void GotoMrLCDsLocation(uint8_t x, uint8_t y);

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

void GotoMrLCDsLocation(uint8_t x, uint8_t y)
{
	Send_A_Command(0x80 + firstColumnPositionsForMrLCD[y-1] + (x-1));
}

//map(val, 0, 1023, 0, 255);
int map(int input,int input_start,int input_end,int output_start,int output_end)
{
	int output ;
	int input_range = input_end - input_start;
	int output_range = output_end - output_start;

	output = (input - input_start)*output_range / input_range + output_start;
	
	return output;
}

void initPWM()
{
	TCCR0 |= 1 << WGM00 | 1 << WGM01 | 1 << CS00 | 1 << COM01;
	
	DDRB |= 1 << PINB3;
	
	//DDRC |= (1 << PC5) | (1 << PC4);
	
	//DDRD |= 1 << PIND4;
	
	//DDRD |= 1 << PINB3;
}

void setPWMOutput(int duty)
{
	// D3   D5    D6   B3
	OCR0 = duty;
	//INT1 = duty;
	//D3
	//OCR1B = duty;
	//OCR1A = duty;
	//ICP1 = duty;
}

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

void cls()
{
	Send_A_Command(0x01); //Clear Screen 0x01 = 00000001
	_delay_ms(2);
}
 
int main()
{
    uint16_t adc_result0, adc_result1;
    char int_buffer[10];
    //DDRC = 0x01;           // to connect led to PC0
	//DDRB |= 1 << PINB3;
	initPWM();
    // initialize adc and lcd
    adc_init();
    //lcd_init(LCD_DISP_ON_CURSOR);
 
    // display the labels on LCD
    //lcd_puts("left  ADC = ");
    //lcd_gotoxy(0,1);
    //lcd_puts("right ADC = ");
	
	
	//initializing LCD
	DataDir_MrLCDsControl |= 1<<LightSwitch | 1<<ReadWrite | 1<<BiPolarMood;
	_delay_ms(15);

	Send_A_Command(0x01); //Clear Screen 0x01 = 00000001
	_delay_ms(2);
	Send_A_Command(0x38);
	_delay_us(50);
	Send_A_Command(0b00001110);
	_delay_us(50);

	char positionString[4];
 
    _delay_ms(50);
 
    while(1)
    {
        adc_result0 = adc_read(0);      // read adc value at PA0
        adc_result1 = adc_read(1);      // read adc value at PA1
		
		
		Send_A_String(adc_result0);
		Send_A_String("/");
		Send_A_String(adc_result1);
		
		_delay_ms(100);
		cls();
		//map(val, 0, 1023, 0, 255);
		/*
		itoa(x, positionString, 10); // convert integer to string
		GotoMrLCDsLocation(12, 3);
		Send_A_String("X = ");
		Send_A_String(positionString);

		itoa(y, positionString, 10);
		GotoMrLCDsLocation(12, 4);
		Send_A_String("Y = ");
		Send_A_String(positionString);

		GotoMrLCDsLocation(x, y);
		Send_A_String("x");

		_delay_ms(50);

		GotoMrLCDsLocation(x, y);
		Send_A_String(" ");

		itoa(x, positionString, 10);
		GotoMrLCDsLocation(12, 3);
		Send_A_String(" ");
		itoa(y, positionString, 10);
		GotoMrLCDsLocation(12, 4);
		Send_A_String(" ");
		*/
		/*
		if(map(adc_result0,0,1023,0,255) > 10)
		{
			setPWMOutput(map(adc_result0,0,1023,0,255));
		}
		else
		{
			setPWMOutput(map(adc_result1,0,1023,0,255));
		}
		*/
			
        // condition for led to glow
        //if (adc_result0 < LTHRES && adc_result1 < RTHRES)
        //    PORTC = 0x01;
        //else
        //    PORTC = 0x00;
 
        // now display on lcd
        //itoa(adc_result0, int_buffer, 10);
        //lcd_gotoxy(12,0);
        //lcd_puts(int_buffer);
 
        //itoa(adc_result1, int_buffer, 10);
        //lcd_gotoxy(12,1);
        //lcd_puts(int_buffer);
        _delay_ms(50);
    }
}