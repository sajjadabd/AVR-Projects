#include <avr/io.h>
#include <util/delay.h>
 
//#include "lcd.h"
 
#define LTHRES 500
#define RTHRES 500

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
 
    _delay_ms(50);
 
    while(1)
    {
        adc_result0 = adc_read(0);      // read adc value at PA0
        adc_result1 = adc_read(1);      // read adc value at PA1
		
		//map(val, 0, 1023, 0, 255);
		
		if(map(adc_result0,0,1023,0,255) > 10)
		{
			setPWMOutput(map(adc_result0,0,1023,0,255));
		}
		else
		{
			setPWMOutput(map(adc_result1,0,1023,0,255));
		}
			
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