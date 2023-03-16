/*
 * My_LCD.c
 *
 * Created: 3/8/2023 9:32:23 PM
 * Author : MohammadSadegh Khodadadi
 */ 

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

#define RS 0
#define RW 1
#define EN 2
unsigned char x_lcd;
unsigned char y_lcd;

void lcd_on();
void lcd_clear();
void lcd_home();
void lcd_right();
void lcd_left();
void lcd_char(char character);
void lcd_puts(char * string);
void lcd_init(char y, char x);
void lcd_goto(char y, char x);



int main(void)
{
	DDRD = 0XFF;// lcd on port D
    DDRA = 0xFF; //RS = 0 ; RW = 1 ; EN = 2
    
    PORTD = 0X00;
    PORTA &= ~(1 << RS);
    PORTA &= ~(1 << RW);
    PORTA &= ~(1 << EN);
	lcd_init(2,16);

    while (1) 
    {
		lcd_clear();
		lcd_puts("MOHAMMAD SADEGH KHODADADI");
		_delay_ms(1000);
    }
}

void lcd_on(){
	PORTA &= ~(1 << RS);
    PORTA |= 1 << EN;
    PORTD = 0x0C;
    _delay_ms(1);
    PORTA &= ~(1 << EN);	
}

void lcd_clear(){
    PORTA &= ~(1 << RS);
    PORTA |= 1 << EN;
    PORTD = 0x01;
    _delay_ms(1);
    PORTA &= ~(1 << EN);
	lcd_home();
}

void lcd_init(char y,char x){
	x_lcd = x;
	y_lcd = y;
	lcd_on();
	lcd_clear();
	//Function set: 8-bit/2-line
	if (x ==16 & y == 2){
		PORTA &= ~(1 << RS);
		PORTA |= 1 << EN;
		PORTD = 0x38;
		_delay_ms(1);
		PORTA &= ~(1 << EN);
	}
}

void lcd_home(){
	PORTA &= ~(1 << RS);
	PORTA |= 1 << EN;
    PORTD = 0x02;
    _delay_ms(1);
    PORTA &= ~(1 << EN);
}

void lcd_char(char character){
	PORTA |= 1 << RS;
	PORTA |= 1 << EN;
	PORTD = character;
	_delay_ms(1);
	PORTA &= ~(1 << EN);
}

void lcd_puts( char * string){
	unsigned char i =0;
	for (i = 0 ; i< (x_lcd * y_lcd) ; i++){
		if (string[i] == '\0')
			break;
		else if (i == x_lcd)
			lcd_goto(2,0);
		lcd_char(string[i]);
	}
}

void lcd_right(){
    PORTA &= ~(1 << RS);
    PORTA |= 1 << EN;
    PORTD = 0x14;
    _delay_ms(1);
    PORTA &= ~(1 << EN);
}

void lcd_left(){
    PORTA &= ~(1 << RS);
    PORTA |= 1 << EN;
    PORTD = 0x10;
    _delay_ms(1);
    PORTA &= ~(1 << EN);	
}

void lcd_goto(char y, char x){
	unsigned char i;
	switch(y){
		case 1:
			lcd_home();
			for ( i=0; i<x; i++)
				lcd_right();		
			break;
		case 2:
			PORTA &= ~(1 << RS);
			PORTA |= 1 << EN;
			PORTD = 0xC0;
			_delay_ms(1);
			PORTA &= ~(1 << EN);
			
			for ( i=0; i<x; i++)
				lcd_right();
			break;
	}
	
}


