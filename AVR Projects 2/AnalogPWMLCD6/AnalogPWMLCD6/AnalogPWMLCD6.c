#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h>

#define soft_reset()        \
do                          \
{                           \
    wdt_enable(WDTO_15MS);  \
    for(;;)                 \
    {                       \
    }                       \
} while(0)



#define F_CPU 16000000UL
//#include "lcd.h"

#define control_bus PORTC
#define controlbus_direction DDRC

#define data_bus PORTC
#define databus_direction DDRC

#define rs 7 // PINB2
#define en 6 // PINB3
//RW --> GND

#define d4 5 // PIND4
#define d5 4 // PIND5
#define d6 3 // PIND6
#define d7 2 // PIND7

//rs PINC7
//en PINC6

//D4 PINC5
//D5 PINC4
//D6 PINC3
//D7 PINC2

int counterLifeTime = 0;

int counter = 0;

int offCounter = 0;

char firstColumnPositionsForMrLCD[4] = {0, 64, 20, 84};

//void Check_IF_MrLCD_isBusy(void);
//void Peek_A_Boo(void);
//void Send_A_Command(unsigned char command);
//void Send_A_Character(unsigned char character);
//void Send_A_String(char *StringOfCharacters);
//void GotoMrLCDsLocation(uint8_t x, uint8_t y);

// LCD Connection
// D0 --> PINB0
// D1 --> PINB1
// D2 --> PINB2
// D3 --> PINB3
// D4 --> PINB4
// D5 --> PINB5
// D6 --> PINB6
// D7 --> PINB7
// V0 (3rd Pin) --> Potentiometer 10K
// RS --> PIND2 // Register Select
// RW --> PIND7 // Read Write
// EN --> PIND5 // ENABLE

void LCD_CmdWrite( char a)
{
	if(a & 0x80) data_bus|=(1<<d7); else data_bus&= ~(1<<d7);
	if(a & 0x40) data_bus|=(1<<d6); else data_bus&= ~(1<<d6);
	if(a & 0x20) data_bus|=(1<<d5); else data_bus&= ~(1<<d5);
	if(a & 0x10) data_bus|=(1<<d4); else data_bus&= ~(1<<d4);
	control_bus &=~(1<<rs);control_bus |=(1<<en);
	_delay_ms(2);
	control_bus &=~(1<<en);
	
	_delay_ms(2);
	
	if(a & 0x08) data_bus|=(1<<d7); else data_bus&= ~(1<<d7);
	if(a & 0x04) data_bus|=(1<<d6); else data_bus&= ~(1<<d6);
	if(a & 0x02) data_bus|=(1<<d5); else data_bus&= ~(1<<d5);
	if(a & 0x01) data_bus|=(1<<d4); else data_bus&= ~(1<<d4);
	control_bus &=~(1<<rs);control_bus |=(1<<en);
	_delay_ms(2);
	control_bus &=~(1<<en);
	
	_delay_ms(2);
}




void LCD_DataWrite( char a)
{
	
	if(a & 0x80) data_bus|=(1<<d7); else data_bus&= ~(1<<d7);
	if(a & 0x40) data_bus|=(1<<d6); else data_bus&= ~(1<<d6);
	if(a & 0x20) data_bus|=(1<<d5); else data_bus&= ~(1<<d5);
	if(a & 0x10) data_bus|=(1<<d4); else data_bus&= ~(1<<d4);
	control_bus |=(1<<rs)|(1<<en);
	_delay_ms(2);
	control_bus &=~(1<<en);
	_delay_ms(2);
	
	if(a & 0x08) data_bus|=(1<<d7); else data_bus&= ~(1<<d7);
	if(a & 0x04) data_bus|=(1<<d6); else data_bus&= ~(1<<d6);
	if(a & 0x02) data_bus|=(1<<d5); else data_bus&= ~(1<<d5);
	if(a & 0x01) data_bus|=(1<<d4); else data_bus&= ~(1<<d4);
	control_bus |=(1<<rs)|(1<<en);
	_delay_ms(2);
	control_bus &=~(1<<en);
	_delay_ms(2);
	
}


void cls()
{
	LCD_CmdWrite(0x01); // clear display
	LCD_CmdWrite(0x80); // force cursor to begin at line1
}


void LCD_Init()
{
	controlbus_direction |= ((1<<rs)|(1<<en));
	databus_direction |= ((1<<d7)|(1<<d6)|(1<<d5)|(1<<d4));
	_delay_ms(2);
	LCD_CmdWrite(0x01); // clear display
	LCD_CmdWrite(0x02); // back to home	
	LCD_CmdWrite(0x28); // 4bit,2line,5x7 pixel
	LCD_CmdWrite(0x06); // entry mode,cursor increments by cursor shift
	LCD_CmdWrite(0x0c); // display ON,cursor OFF
	LCD_CmdWrite(0x80); // force cursor to begin at line1

}

void LCD_Disp(const char *p)
{
	while(*p!='\0')
	{
		LCD_DataWrite(*p);
		p++; _delay_ms(2);
	}
}

void LCD_setCursor(int a, int b)
{
	int i=0;
	switch(b)
	{
		case 0:LCD_CmdWrite(0x80);break;
		case 1:LCD_CmdWrite(0xC0);break;
		case 2:LCD_CmdWrite(0x94);break;
		case 3:LCD_CmdWrite(0xd4);break;
	}
	for(i=0;i<a;i++)
		LCD_CmdWrite(0x14);
}


//map(val, 0, 1023, 0, 255);
uint16_t map(uint16_t input,uint16_t input_start,uint16_t input_end,uint16_t output_start,uint16_t output_end)
{
	float output = input;
	uint16_t input_range = input_end - input_start;
	uint16_t output_range = output_end - output_start;

	//output = (input - input_start)*output_range / input_range + output_start;
	//output = (input*255) / 1023;
	output /= (float)input_range;
	output *= output_range;
	
	return (uint16_t)output;
}

void initPWM()
{
	TCCR0 |= 1 << WGM00 | 1 << WGM01 | 1 << CS00 | 1 << COM01;
	
	//DDRB |= 1 << PINB3;
	
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

/*
void cls()
{
	Send_A_Command(0x01); //Clear Screen 0x01 = 00000001
	_delay_ms(2);
}
*/



//PC1 , PC0 , PD7 --> DOWN L6203 --> Left Motor
//PD4 , PD5 , PD6 --> TOP L6203 ---> Right Motor

void LeftMotorOff()
{
	PORTC &= ~(1 << PINC0);
	PORTC &= ~(1 << PINC1);
}		

void LeftMotorForward()
{
	PORTC |= (1 << PINC0);
	PORTC &= ~(1 << PINC1);
}	

void LeftMotorBackward()
{
	PORTC &= ~(1 << PINC0);
	PORTC |= (1 << PINC1);
}	

void enableLeftMotor()
{
	PORTD |= 1 << PIND7; // ENABLE ON // LEFT MOTOR
}

void disableLeftMotor()
{
	PORTD &= ~(1 << PIND7); // ENABLE OFF// LEFT MOTOR	
}	


//------------------------------
//------------------------------
//------------------------------
//------------------------------

void RightMotorOff()
{
	PORTD &= ~(1 << PIND4);
	PORTD &= ~(1 << PIND5);
}	

void RightMotorForward()
{
	PORTD |= (1 << PIND4);
	PORTD &= ~(1 << PIND5);
}	

void RightMotorBackward()
{
	PORTD &= ~(1 << PIND4);
	PORTD |= (1 << PIND5);
}

void enableRightMotor()
{
	PORTD |= 1 << PIND6; // ENABLE ON // RIGHT MOTOR
}

void disableRightMotor()
{
	PORTD &= ~(1 << PIND6); // ENABLE OFF // RIGHT MOTOR
}

//--------------------

void GoToForward()
{
	//enableLeftMotor();
	//enableRightMotor();
	
	RightMotorBackward();
	LeftMotorBackward();
}

void GoToBack()
{
	//enableLeftMotor();
	//enableRightMotor();
	
	RightMotorForward();
	LeftMotorForward();
}	

void turnRight()
{
	//enableLeftMotor();
	//enableRightMotor();
	
	RightMotorForward();
	LeftMotorBackward();
}	

void turnLeft()
{
	//enableLeftMotor();
	//enableRightMotor();
	
	LeftMotorForward();
	RightMotorBackward();
}	

void turnOff()
{
	//disableLeftMotor();
	//disableRightMotor();
	
	LeftMotorOff();
	RightMotorOff();
}	

uint16_t findMax(uint16_t x[])
{
	uint16_t max = x[0];
	uint16_t max2 = x[0];
	
	uint16_t index = 0;
	uint16_t secondIndex = 0;
	
	for (int i=0;i<7;i++)
	{
		if ( x[i] >= max )
		{
			secondIndex = index;
			
			max = x[i];
			index = i;
		}
	}
	
	if ( max >= 1000 )
	{
		//soft_reset();
	}
	
	/*
	if(x[index]-x[secondIndex] < 1)
	{
		offCounter++;
	}
	*/
	
	
	/*
	if( x[index]-x[secondIndex] >= 1 )
		return index;
	else
		return -1;
	*/
	
	return index;
}

void printLCD(uint16_t adc_result[])
{
	char positionString[4];
	
	for(int i=0;i<4;i++)
	{
		itoa(adc_result[i], positionString, 10); // convert integer to string
		LCD_Disp(positionString);
		LCD_Disp("/");
	}
	LCD_setCursor(0,1); // this means x = 0 , y = 1
	for(int i=4;i<8;i++)
	{
		itoa(adc_result[i], positionString, 10); // convert integer to string
		LCD_Disp(positionString);
		LCD_Disp("/");
	}
}	
 
int main()
{
	//PC1 , PC0 , PD7 --> DOWN L6203 --> Left Motor
	//PD4 , PD5 , PD6 --> TOP L6203 ---> Right Motor
	DDRC |= 1 << PINC0; // INPUT1  // DOWN --> Left Motor
	DDRC |= 1 << PINC1; // INPUT2  // DOWN --> Left Motor
	DDRD |= 1 << PIND7; // ENABLE  // DOWN --> Left Motor
	LeftMotorOff();
	
	PORTD |= 1 << PIND7; // ENABLE ON // LEFT MOTOR
	
	DDRD |= 1 << PIND4; // INPUT1  // TOP --> Right Motor
	DDRD |= 1 << PIND5; // INPUT2  // TOP --> Right Motor
	DDRD |= 1 << PIND6; // ENABLE  // TOP --> Right Motor
	RightMotorOff();
	
	PORTD |= 1 << PIND6; // ENABLE ON // RIGHT MOTOR
	
	//disable JTAG
	MCUCSR = (1 << JTD);
	MCUCSR = (1 << JTD);

	//uint16_t temp0 = 0;
	//uint16_t temp1 = 0;
	
	//uint16_t adc0;
	//uint16_t adc1;
	//uint16_t adc2;
	//uint16_t adc3;
	//uint16_t adc4;
	//uint16_t adc5;
	//uint16_t adc6;
	//uint16_t adc7;
	
	
    uint16_t adc_result[7] = {0,0,0,0,0,0,0};
	
	
    char int_buffer[10];
    //DDRC = 0x01;           // to connect led to PC0
	//DDRB |= 1 << PINB3;
	//initPWM();
    // initialize adc and lcd
	
	
    adc_init();
	
	
	
    //lcd_init(LCD_DISP_ON_CURSOR);
 
    // display the labels on LCD
    //lcd_puts("left  ADC = ");
    //lcd_gotoxy(0,1);
    //lcd_puts("right ADC = ");
	
	
	//initializing LCD
	
	
	LCD_Init();
	
	//LCD_Disp("Amozeshgah");
	//LCD_setCursor(4,1); // this means x = 0 , y = 1
	//LCD_Disp("Chamran");
	
	char positionString[4];
 
    //_delay_ms(1000);
	
	cls();
	
	uint16_t maxIndex;
	
	//enableLeftMotor();
	//enableRightMotor();
 
    while(1)
    {
        //adc_result[0] = adc_read(0);      // read adc value at PA0
		
		//adc_result0 *= 255; // the problem is here can not calculate number*255 (overload happen)
		//adc_result0 /= 1023;
		//adc0 = map(adc_result0,0,1023,0,255);
		
		//adc_result[1] = adc_read(1);      // read adc value at PA1
		
		//adc_result1 *= 255; // the problem is here can not calculate number*255 (overload happen)
		//adc_result1 /= 1023;
		
		//adc1 = map(adc_result1,0,1023,0,255);
		
		/*
		adc_result[0] = adc_read(0);//Diode F // Go To Forward
		adc_result[1] = adc_read(1);//Diode H // Go To Left
		adc_result[2] = adc_read(2);//Diode E // Go To Forward
		adc_result[3] = adc_read(3);//Diode D // Go To Forward
		adc_result[4] = adc_read(4);//Diode G // Go To Right
		adc_result[5] = adc_read(5);//Diode C // Go to Back
		adc_result[6] = adc_read(6);//Diode B // Go to Back
		adc_result[7] = adc_read(7);//Diode A // Go to Back
		*/
		
		adc_result[0] = map(adc_read(0),0,1023,0,900);
		adc_result[1] = map(adc_read(1),0,1023,0,900);
		adc_result[2] = map(adc_read(2),0,1023,0,900);
		adc_result[3] = map(adc_read(3),0,1023,0,900);
		adc_result[4] = map(adc_read(4),0,1023,0,900);
		adc_result[5] = map(adc_read(5),0,1023,0,900);
		adc_result[6] = map(adc_read(6),0,1023,0,900);
		adc_result[7] = map(adc_read(7),0,1023,0,900);
		
		
		//printLCD(adc_result);
		
		
		
		maxIndex = findMax(adc_result);
		
		//itoa(maxIndex, positionString, 10); // convert integer to string
		//LCD_Disp("max Index : ");
		//LCD_Disp(positionString);
		
		
		if( maxIndex == 6  || maxIndex == 0 || maxIndex == 3 ) // Go to Back // B
		{
			//GoToForward();
			GoToBack();
			LCD_Disp("Go To Back     ");
		}
		else if ( maxIndex == 2 || maxIndex == 7 || maxIndex == 5 ) // Go To Forward // E
		{
			GoToForward();
			//GoToBack();
			LCD_Disp("Go To Forward  ");
		}
		else if( maxIndex == 1  ) // Go To Left // H,A,F
		{
			turnLeft();
			LCD_Disp("Turn Left      ");
		}
		else if( maxIndex == 4 ) // Go To Right // G,C,D
		{
			turnRight();
			LCD_Disp("Turn Right     ");
		} 
		else if ( maxIndex == -1 )
		{
			//turnOff();
			LCD_Disp("Turn Off       ");
		}
		
		
		/*
		if( maxIndex == 6 ) // Go to Back // B
		{
			GoToBack();
			LCD_Disp("Go To Back     ");
		}
		else if ( maxIndex == 2 ) // Go To Forward // E
		{
			GoToForward();
			LCD_Disp("Go To Forward  ");
		}
		else if( maxIndex == 1 || maxIndex == 0 || maxIndex == 7 ) // Go To Left // H,A,F
		{
			turnLeft();
			LCD_Disp("Turn Left      ");
		}
		else if( maxIndex == 4 || maxIndex == 3 || maxIndex == 5 ) // Go To Right // G,C,D
		{
			turnRight();
			LCD_Disp("Turn Right     ");
		} 
		else if ( maxIndex == -1 )
		{
			//turnOff();
			LCD_Disp("Turn Off       ");
		}
		*/
		
		/*
		if(offCounter > 20)
		{
			//turnOff();
			offCounter = 0;
		}			
		*/
		
		_delay_ms(50);
		//cls();
		LCD_setCursor(0,0);
		
		
		counterLifeTime++;
		
		if(counterLifeTime > 1000)
		{
			soft_reset();
		}
		
		
		
		/*
		if ( adc_result0 != temp0 )
		{
			temp0 = adc_result0;
			
			cls();
			
			itoa(adc_result0, positionString, 10); // convert integer to string
			//Send_A_String(positionString);
			//Send_A_String("/");
			LCD_Disp(positionString);
			LCD_Disp("/");
			itoa(adc_result1, positionString, 10);
			//Send_A_String(positionString);
			LCD_Disp(positionString);
			
			//GotoMrLCDsLocation(64, 0);
			//LCD_setCursor(1,0); // this means x = 1 , y = 0
			LCD_setCursor(0,1); // this means x = 0 , y = 1
			
			
			itoa(adc0, positionString, 10); // convert integer to string
			//Send_A_String(positionString);
			//Send_A_String("/");
			LCD_Disp(positionString);
			LCD_Disp("/");
			itoa(adc1, positionString, 10);
			//Send_A_String(positionString);
			LCD_Disp(positionString);
		}			

		if ( adc_result1 != temp1 )
		{
			temp1 = adc_result1;
			
			cls();
			
			itoa(adc_result0, positionString, 10); // convert integer to string
			//Send_A_String(positionString);
			//Send_A_String("/");
			LCD_Disp(positionString);
			LCD_Disp("/");
			itoa(adc_result1, positionString, 10);
			//Send_A_String(positionString);
			LCD_Disp(positionString);
			
			//GotoMrLCDsLocation(64, 0);
			//LCD_setCursor(1,0); // this means x = 1 , y = 0
			LCD_setCursor(0,1); // this means x = 0 , y = 1
			
			itoa(adc0, positionString, 10); // convert integer to string
			//Send_A_String(positionString);
			//Send_A_String("/");
			LCD_Disp(positionString);
			LCD_Disp("/");
			itoa(adc1, positionString, 10);
			//Send_A_String(positionString);
			LCD_Disp(positionString);
		}	
		
		*/
				
		//_delay_ms(100);
		
		//cls();
		
		
		
		/*
		GotoMrLCDsLocation(64, 0); // go to Next Line
		
		//adc_result0 = adc_read(0);      // read adc value at PA0
        //adc_result1 = adc_read(1);      // read adc value at PA1
		adc0 = map(adc_result0, 0, 1023, 0, 255);
		adc1 = map(adc_result1, 0, 1023, 0, 255);
		
		itoa(adc0, positionString, 10); // convert integer to string
		Send_A_String(positionString);
		Send_A_String("/");
		
		itoa(adc1, positionString, 10);
		Send_A_String(positionString);
		*/

		
		
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
        
    }
}