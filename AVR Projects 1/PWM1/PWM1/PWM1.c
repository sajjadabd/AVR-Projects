#include <avr/io.h>
#include <util/delay.h>

int pressed = 0;
int pressed2 = 0;
//int counterMemory;
int counter = 0;

void initPWM()
{
	TCCR0 |= 1 << WGM00 | 1 << WGM01 | 1 << CS00 | 1 << COM01;
	
	DDRB |= 1 << PINB3;
	
	DDRB &= ~(1 << PINB0);
	DDRB &= ~(1 << PINB1);
	PORTB |= 1 << PINB0;
	PORTB |= 1 << PINB1;
	//PORTB |= 1 << PINB3;
}



void setPWMOutput(int duty)
{
	OCR0 = duty;
}

void wait()
{
	_delay_loop_2(3200);
}



void ScanButton()
{
	
	if(bit_is_clear(PINB, 0))
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
		if(bit_is_clear(PINB,0))
		{
			if(counter < 10)
			{
				//PORTB ^= 1 << PINB3;
				PORTB |= 1 << PINB3;
			}
			
			//When Button in Pressed
			//counterMemory = counter;
			counter++;
			
			if(counter >= 250)
			{
				counter = 255;
			}
			setPWMOutput(counter);
			/*
			if (counter >= 255)
			{
				counter = 0;
			}
			*/
			_delay_ms(5);
		}
		else
		{
			//PORTB ^= 1 << PINB0;
			//Do SomeThing
			
			pressed = 0;					
		}
	}
	/*
	if (counter >= 255)
	{
		counter = 0;
	}
	*/
}

void ScanButton2()
{
	
	if(bit_is_clear(PINB, 1))
	{
		if(pressed2 >= 1000)
		{
			pressed2 = 500;
		}
		else
		{
			pressed2++;
		}							
	}	
		
	if(pressed2 >= 400)
	{
		if(bit_is_clear(PINB,1))
		{
			//When Button in Pressed
			//counterMemory = counter;
			counter--;
			if(counter <= 1)
			{
				counter = 0;
				setPWMOutput(counter);
				PORTB &= ~(1 << PINB3);
			}
			else
			{
				setPWMOutput(counter);
			}
			
			/*
			if (counter >= 255)
			{
				counter = 0;
			}
			*/
			_delay_ms(2);
		}
		else
		{
			//PORTB ^= 1 << PINB0;
			//Do SomeThing
			
			pressed2 = 0;					
		}
	}
	/*
	if (counter >= 255)
	{
		counter = 0;
	}
	*/
}

void increase()
{
	for(int i=0; i<=255; i++)
	{
		setPWMOutput(i);
		wait();
	}
}



void decrease()
{
	for(int i=255; i>=0; i--)
	{
		setPWMOutput(i);
		wait();
	}
}

int main()
{
	//int brightness = 0;
	
	initPWM();
	
	while(1)
	{
		ScanButton();
		ScanButton2();
	}
}