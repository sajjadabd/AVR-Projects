/*
 * SevenSegmentPlusTimer_1.c
 *
 * Created: 2/14/2018 9:51:16 PM
 *  Author: sajjad
 */ 

//PORTA Raghame Yekan
#define A1 PINA0
#define B1 PINA1
#define C1 PINA2
#define D1 PINA3
#define E1 PINA4
#define F1 PINA5
#define G1 PINA6

//PORTC Raghame Dahgan
#define A2 PIND0
#define B2 PIND1
#define C2 PIND2
#define D2 PIND3
#define E2 PIND4
#define F2 PIND5
#define G2 PIND6

#define INPUT1 PINB0
#define INPUT2 PINB1

#define START PINB2

#define OUTPUT PINB3



#include <avr/io.h>
#include <util/delay.h>

int counter = 0;

int pressed1 = 0;
int pressed2 = 0;
int pressed3 = 0;

void refresh(int counter2)
{
	clearA();
	clearC();
	switch(counter2)
	{
		case 0:
			show0();
			break;
		case 1:
			show1();
			break;
		case 2:
			show2();
			break;
		case 3:
			show3();
			break;
		case 4:
			show4();
			break;
		case 5:
			show5();
			break;
		case 6:
			show6();
			break;
		case 7:
			show7();
			break;
		case 8:
			show8();
			break;
		case 9:
			show9();
			break;
		case 10:
			show10();
			break;
		case 11:
			show11();
			break;
		case 12:
			show12();
			break;
		case 13:
			show13();
			break;
		case 14:
			show14();
			break;
		case 15:
			show15();
			break;
		case 16:
			show16();
			break;
		case 17:
			show17();
			break;
		case 18:
			show18();
			break;
		case 19:
			show19();
			break;
		case 20:
			show20();
			break;
		case 21:
			show21();
			break;
		case 22:
			show22();
			break;
		case 23:
			show23();
			break;
		case 24:
			show24();
			break;
		case 25:
			show25();
			break;
		case 26:
			show26();
			break;
		case 27:
			show27();
			break;
		case 28:
			show28();
			break;
		case 29:
			show29();
			break;
		case 30:
			show30();
			break;
		case 31:
			show31();
			break;
		case 32:
			show32();
			break;
		case 33:
			show33();
			break;
		case 34:
			show34();
			break;
		case 35:
			show35();
			break;
		case 36:
			show36();
			break;
		case 37:
			show37();
			break;
		case 38:
			show38();
			break;
		case 39:
			show39();
			break;
		case 40:
			show40();
			break;
		case 41:
			show41();
			break;
		case 42:
			show42();
			break;
		case 43:
			show43();
			break;
		case 44:
			show44();
			break;
		case 45:
			show45();
			break;
		case 46:
			show46();
			break;
		case 47:
			show47();
			break;
		case 48:
			show48();
			break;
		case 49:
			show49();
			break;
		case 50:
			show50();
			break;
		case 51:
			show51();
			break;
		case 52:
			show52();
			break;
		case 53:
			show53();
			break;
		case 54:
			show54();
			break;
		case 55:
			show55();
			break;
		case 56:
			show56();
			break;
		case 57:
			show57();
			break;
		case 58:
			show58();
			break;
		case 59:
			show59();
			break;
		case 60:
			show60();
			break;
		case 61:
			show61();
			break;
		case 62:
			show62();
			break;
		case 63:
			show63();
			break;
		case 64:
			show64();
			break;
		case 65:
			show65();
			break;
		case 66:
			show66();
			break;
		case 67:
			show67();
			break;
		case 68:
			show68();
			break;
		case 69:
			show69();
			break;
		case 70:
			show70();
			break;
		case 71:
			show71();
			break;
		case 72:
			show72();
			break;
		case 73:
			show73();
			break;
		case 74:
			show74();
			break;
		case 75:
			show75();
			break;
		case 76:
			show76();
			break;
		case 77:
			show77();
			break;
		case 78:
			show78();
			break;
		case 79:
			show79();
			break;
		case 80:
			show80();
			break;
		case 81:
			show81();
			break;
		case 82:
			show82();
			break;
		case 83:
			show83();
			break;
		case 84:
			show84();
			break;
		case 85:
			show85();
			break;
		case 86:
			show86();
			break;
		case 87:
			show87();
			break;
		case 88:
			show88();
			break;
		case 89:
			show89();
			break;
		case 90:
			show90();
			break;
		case 91:
			show91();
			break;
		case 92:
			show92();
			break;
		case 93:
			show93();
			break;
		case 94:
			show94();
			break;
		case 95:
			show95();
			break;
		case 96:
			show96();
			break;
		case 97:
			show97();
			break;
		case 98:
			show98();
			break;
		case 99:
			show99();
			break;
		default:
			break;
	}
}


void ScanButton1()//plus
{
	
	if(bit_is_clear(PINB, 0))
	{
		if(pressed1 >= 1000)
		{
			pressed1 = 500;
		}
		else
		{
			pressed1++;
		}							
	}	
		
	if(pressed1 >= 400)
	{
		if(bit_is_clear(PINB,0))
		{
			//Do Nothing
		}
		else
		{
			if(counter < 99)
			{
				counter++;
			}
			refresh(counter);
			//Do Something
			//PORTB ^= 1 << INPUT1;
			pressed1 = 0;					
		}
	}
}

void ScanButton2()//minus
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
			//Do Nothing
		}
		else
		{
			if(counter > 0)
			{
				counter--;
			}
			
			refresh(counter);
			//Do Something
			//PORTB ^= 1 << INPUT2;
			pressed2 = 0;					
		}
	}
}


void ScanButton3()//start
{
	
	if(bit_is_clear(PINB, 2))
	{
		if(pressed3 >= 1000)
		{
			pressed3 = 500;
		}
		else
		{
			pressed3++;
		}							
	}	
		
	if(pressed3 >= 400)
	{
		if(bit_is_clear(PINB,2))
		{
			//Do Nothing
		}
		else
		{
			PORTB |=  1 << OUTPUT;
			//_delay_ms(counter * 1000);
			for(int i=counter;i>0;i--)
			{
				refresh(i);
				_delay_ms(1000);
				
			}
			//delay();
			PORTB &=  ~(1 << OUTPUT);
			refresh(counter);
			//Do Something
			//PORTB ^= 1 << INPUT2;
			pressed3 = 0;					
		}
	}
}



void clearA()
{
	PORTA &= ~(1 << PINA0);
	PORTA &= ~(1 << PINA1);
	PORTA &= ~(1 << PINA2);
	PORTA &= ~(1 << PINA3);
	PORTA &= ~(1 << PINA4);
	PORTA &= ~(1 << PINA5);
	PORTA &= ~(1 << PINA6);
	PORTA &= ~(1 << PINA7);
}

void clearC()
{
	PORTD &= ~(1 << PIND0);
	PORTD &= ~(1 << PIND1);
	PORTD &= ~(1 << PIND2);
	PORTD &= ~(1 << PIND3);
	PORTD &= ~(1 << PIND4);
	PORTD &= ~(1 << PIND5);
	PORTD &= ~(1 << PIND6);
	PORTD &= ~(1 << PIND7);
}

void show0_A()
{
	PORTA |= 1 << A1;
	PORTA |= 1 << B1;
	PORTA |= 1 << C1;
	PORTA |= 1 << D1;
	PORTA |= 1 << E1;
	PORTA |= 1 << F1;
}

void show1_A()
{
	PORTA |= 1 << F1;
	PORTA |= 1 << E1;
}

void show2_A()
{
	PORTA |= 1 << A1;
	PORTA |= 1 << B1;
	PORTA |= 1 << G1;
	PORTA |= 1 << E1;
	PORTA |= 1 << D1;
}

void show3_A()
{
	PORTA |= 1 << A1;
	PORTA |= 1 << B1;
	PORTA |= 1 << G1;
	PORTA |= 1 << C1;
	PORTA |= 1 << D1;
}

void show4_A()
{
	PORTA |= 1 << F1;
	PORTA |= 1 << G1;
	PORTA |= 1 << B1;
	PORTA |= 1 << B1;
	PORTA |= 1 << C1;
}

void show5_A()
{
	PORTA |= 1 << A1;
	PORTA |= 1 << F1;
	PORTA |= 1 << G1;
	PORTA |= 1 << C1;
	PORTA |= 1 << D1;
}

void show6_A()
{
	PORTA |= 1 << G1;
	PORTA |= 1 << C1;
	PORTA |= 1 << D1;
	PORTA |= 1 << E1;
	PORTA |= 1 << F1;
	PORTA |= 1 << A1;
}

void show7_A()
{
	PORTA |= 1 << A1;
	PORTA |= 1 << B1;
	PORTA |= 1 << C1;
}

void show8_A()
{
	PORTA |= 1 << A1;
	PORTA |= 1 << B1;
	PORTA |= 1 << C1;
	PORTA |= 1 << D1;
	PORTA |= 1 << E1;
	PORTA |= 1 << F1;
	PORTA |= 1 << G1;
}

void show9_A()
{
	PORTA |= 1 << A1;
	PORTA |= 1 << B1;
	PORTA |= 1 << G1;
	PORTA |= 1 << F1;
	PORTA |= 1 << C1;
	PORTA |= 1 << D1;
}

//----------------------------------

void show0_C()
{
	PORTD |= 1 << A2;
	PORTD |= 1 << B2;
	PORTD |= 1 << C2;
	PORTD |= 1 << D2;
	PORTD |= 1 << E2;
	PORTD |= 1 << F2;
}

void show1_C()
{
	PORTD |= 1 << F2;
	PORTD |= 1 << E2;
}

void show2_C()
{
	PORTD |= 1 << A2;
	PORTD |= 1 << B2;
	PORTD |= 1 << G2;
	PORTD |= 1 << E2;
	PORTD |= 1 << D2;
}

void show3_C()
{
	PORTD |= 1 << A2;
	PORTD |= 1 << B2;
	PORTD |= 1 << G2;
	PORTD |= 1 << C2;
	PORTD |= 1 << D2;
}

void show4_C()
{
	PORTD |= 1 << F2;
	PORTD |= 1 << G2;
	PORTD |= 1 << B2;
	PORTD |= 1 << B2;
	PORTD |= 1 << C2;
}

void show5_C()
{
	PORTD |= 1 << A2;
	PORTD |= 1 << F2;
	PORTD |= 1 << G2;
	PORTD |= 1 << C2;
	PORTD |= 1 << D2;
}

void show6_C()
{
	PORTD |= 1 << G2;
	PORTD |= 1 << C2;
	PORTD |= 1 << D2;
	PORTD |= 1 << E2;
	PORTD |= 1 << F2;
	PORTD |= 1 << A2;
}

void show7_C()
{
	PORTD |= 1 << A2;
	PORTD |= 1 << B2;
	PORTD |= 1 << C2;
}

void show8_C()
{
	PORTD |= 1 << A2;
	PORTD |= 1 << B2;
	PORTD |= 1 << C2;
	PORTD |= 1 << D2;
	PORTD |= 1 << E2;
	PORTD |= 1 << F2;
	PORTD |= 1 << G2;
}

void show9_C()
{
	PORTD |= 1 << A2;
	PORTD |= 1 << B2;
	PORTD |= 1 << G2;
	PORTD |= 1 << F2;
	PORTD |= 1 << C2;
	PORTD |= 1 << D2;
}

//---------------------------------------

void show0()
{
	show0_C();
	show0_A();
}


void show1()
{
	show0_C();
	show1_A();
}

void show2()
{
	show0_C();
	show2_A();
}

void show3()
{
	show0_C();
	show3_A();	
}

void show4()
{
	show0_C();
	show4_A();
}

void show5()
{
	show0_C();
	show5_A();
}

void show6()
{
	show0_C();
	show6_A();
}

void show7()
{
	show0_C();
	show7_A();
}

void show8()
{
	show0_C();
	show8_A();
}

void show9()
{
	show0_C();
	show9_A();
}

void show10()
{
	show1_C();
	show0_A();
}

void show11()
{
	show1_C();
	show1_A();
}

void show12()
{
	show1_C();
	show2_A();
}

void show13()
{
	show1_C();
	show3_A();
}

void show14()
{
	show1_C();
	show4_A();
}

void show15()
{
	show1_C();
	show5_A();
}

void show16()
{
	show1_C();
	show6_A();
}

void show17()
{
	show1_C();
	show7_A();
}

void show18()
{
	show1_C();
	show8_A();
}

void show19()
{
	show1_C();
	show9_A();
}

void show20()
{
	show2_C();
	show0_A();
}

void show21()
{
	show2_C();
	show1_A();
}

void show22()
{
	show2_C();
	show2_A();
}

void show23()
{
	show2_C();
	show3_A();
}


void show24()
{
	show2_C();
	show4_A();
}

void show25()
{
	show2_C();
	show5_A();
}

void show26()
{
	show2_C();
	show6_A();
}

void show27()
{
	show2_C();
	show7_A();
}

void show28()
{
	show2_C();
	show8_A();
}

void show29()
{
	show2_C();
	show9_A();
}

void show30()
{
	show3_C();
	show0_A();
}

void show31()
{
	show3_C();
	show1_A();
}

void show32()
{
	show3_C();
	show2_A();
}

void show33()
{
	show3_C();
	show3_A();
}

void show34()
{
	show3_C();
	show4_A();
}

void show35()
{
	show3_C();
	show5_A();
}

void show36()
{
	show3_C();
	show6_A();
}

void show37()
{
	show3_C();
	show7_A();
}

void show38()
{
	show3_C();
	show8_A();
}

void show39()
{
	show3_C();
	show9_A();
}

void show40()
{
	show4_C();
	show0_A();
}

void show41()
{
	show4_C();
	show1_A();
}

void show42()
{
	show4_C();
	show2_A();
}

void show43()
{
	show4_C();
	show3_A();
}

void show44()
{
	show4_C();
	show4_A();
}

void show45()
{
	show4_C();
	show5_A();
}

void show46()
{
	show4_C();
	show6_A();
}

void show47()
{
	show4_C();
	show7_A();
}

void show48()
{
	show4_C();
	show8_A();
}

void show49()
{
	show4_C();
	show9_A();
}

void show50()
{
	show5_C();
	show0_A();
}

void show51()
{
	show5_C();
	show1_A();
}

void show52()
{
	show5_C();
	show2_A();
}

void show53()
{
	show5_C();
	show3_A();
}

void show54()
{
	show5_C();
	show4_A();
}

void show55()
{
	show5_C();
	show5_A();
}

void show56()
{
	show5_C();
	show6_A();
}

void show57()
{
	show5_C();
	show7_A();
}

void show58()
{
	show5_C();
	show8_A();
}

void show59()
{
	show5_C();
	show9_A();
}

void show60()
{
	show6_C();
	show0_A();
}

void show61()
{
	show6_C();
	show1_A();
}

void show62()
{
	show6_C();
	show2_A();
}

void show63()
{
	show6_C();
	show3_A();
}

void show64()
{
	show6_C();
	show4_A();
}

void show65()
{
	show6_C();
	show5_A();
}

void show66()
{
	show6_C();
	show6_A();
}

void show67()
{
	show6_C();
	show7_A();
}

void show68()
{
	show6_C();
	show8_A();
}

void show69()
{
	show6_C();
	show9_A();
}

void show70()
{
	show7_C();
	show0_A();
}

void show71()
{
	show7_C();
	show1_A();
}

void show72()
{
	show7_C();
	show2_A();
}

void show73()
{
	show7_C();
	show3_A();
}

void show74()
{
	show7_C();
	show4_A();
}

void show75()
{
	show7_C();
	show5_A();
}

void show76()
{
	show7_C();
	show6_A();
}

void show77()
{
	show7_C();
	show7_A();
}

void show78()
{
	show7_C();
	show8_A();
}

void show79()
{
	show7_C();
	show9_A();
}

void show80()
{
	show8_C();
	show0_A();
}

void show81()
{
	show8_C();
	show1_A();
}

void show82()
{
	show8_C();
	show2_A();
}

void show83()
{
	show8_C();
	show3_A();
}

void show84()
{
	show8_C();
	show4_A();
}

void show85()
{
	show8_C();
	show5_A();
}

void show86()
{
	show8_C();
	show6_A();
}

void show87()
{
	show8_C();
	show7_A();
}

void show88()
{
	show8_C();
	show8_A();
}

void show89()
{
	show8_C();
	show9_A();
}

void show90()
{
	show9_C();
	show0_A();
}

void show91()
{
	show9_C();
	show1_A();
}

void show92()
{
	show9_C();
	show2_A();
}

void show93()
{
	show9_C();
	show3_A();
}

void show94()
{
	show9_C();
	show4_A();
}

void show95()
{
	show9_C();
	show5_A();
}

void show96()
{
	show9_C();
	show6_A();
}

void show97()
{
	show9_C();
	show7_A();
}

void show98()
{
	show9_C();
	show8_A();
}

void show99()
{
	show9_C();
	show9_A();
}

void init()
{
	DDRA |= 1 << A1;
	DDRA |= 1 << B1;
	DDRA |= 1 << C1;
	DDRA |= 1 << D1;
	DDRA |= 1 << E1;
	DDRA |= 1 << F1;
	DDRA |= 1 << G1;
	
	DDRD |= 1 << A2;
	DDRD |= 1 << B2;
	DDRD |= 1 << C2;
	DDRD |= 1 << D2;
	DDRD |= 1 << E2;
	DDRD |= 1 << F2;
	DDRD |= 1 << G2;
	
	DDRB |= 1 << OUTPUT;
	
	
	DDRB &= ~(1 << INPUT1);
	DDRB &= ~(1 << INPUT2);
	DDRB &= ~(1 << START);
	
	PORTB |= 1 << INPUT1;
	PORTB |= 1 << INPUT2;
	PORTB |= 1 << START;
}

int main(void)
{
	
	init();
	refresh(counter);
    while(1)
    {
		
		ScanButton1();
		ScanButton2();
		ScanButton3();
        //TODO:: Please write your application code 
    }
}