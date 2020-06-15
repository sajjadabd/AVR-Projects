//Program to display string on LCD using ATmega16
/*
LCD DATA port----PORT A
signal port------PORT B
    rs-------PD0
    rw-------PD1
    en-------PD2
*/
 
#include<avr/io.h>
#include<util/delay.h>
 
#define lcd_data PORTA    //LCD data port
 
#define ctrl PORTB
#define en PB2        // enable signal
#define rw PB1        // read or write signal
#define rs PB0        // register select signal
 
void lcd_cmd(unsigned char cmd);
void init_lcd(void);
void lcd_write(unsigned char data);

void cls()
{
	lcd_cmd(0x01);        // clear LCD
    _delay_ms(1);
}

int main()
{
    DDRA=0xff;        
    DDRB=0x07;        
    init_lcd();    // initialization of LCD
    _delay_ms(50);    // delay of 50ms
    lcd_write_string("Just Execute It");// prints string on LCD
    return 0;
}
 
void init_lcd(void)
{
    lcd_cmd(0x38);        // LCD initialization 
    _delay_ms(1);
 
    lcd_cmd(0x01);        // clear LCD
    _delay_ms(1);
 
    lcd_cmd(0x0E);        // cursor ON
    _delay_ms(1);
 
    lcd_cmd(0x80);        // ---8 go to first line and --0 is for 0th position
    _delay_ms(1);
    return;
}
 
void lcd_cmd(unsigned char cmd)
{
    lcd_data=cmd;
    ctrl =(0<<rs)|(0<<rw)|(1<<en);    
    _delay_ms(1);
    ctrl =(0<<rs)|(0<<rw)|(0<<en);    
    _delay_ms(50);
    return;
}
 
void lcd_write(unsigned char data)
{
    lcd_data= data;
    ctrl = (1<<rs)|(0<<rw)|(1<<en);    
    _delay_ms(1);
    ctrl = (1<<rs)|(0<<rw)|(0<<en);    
    _delay_ms(50);                
    return ;
}
 
void lcd_write_string(unsigned char *str)//store address value of the string in pointer *str
{
    int i=0;
    while(str[i] != '\0')// loop will go on till the NULL character in the string 
    {
        lcd_write(str[i]);// sending data on LCD byte by byte
        i++;
    }
    return;
}