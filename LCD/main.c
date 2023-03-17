/*
 * lcd_4bit.c
 *
 * Created: 3/17/2023 2:52:34 PM
 * Author : mskh4
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
void LCD4bit_cmd(unsigned char cmd);


int main(void)
{
	DDRA = 0xFF; 
	PORTA = 0X00;
	lcd_init(2,16);
	lcd_puts("hello i send 4bit");
	_delay_ms(3000);
	while(1){
			PORTA |= 0xE0;
			_delay_ms(1000);
			PORTA = 0x00;
			_delay_ms(1000);
	}
}

void LCD4bit_cmd(unsigned char cmd)
{
	PORTA = (PORTA & 0x0F) | (cmd & 0xF0); 
	PORTA &= ~ (1<<RS);		
	PORTA |= (1<<EN);
	_delay_ms(1);
	PORTA &= ~ (1<<EN);
_delay_us(200);
	PORTA = (PORTA & 0x0F) | (cmd << 4);
	PORTA |= (1<<EN);
	_delay_ms(1);
	PORTA &= ~ (1<<EN);
	_delay_ms(2);	
}

void lcd_on(){
	LCD4bit_cmd(0x0c);
}

void lcd_clear(){
	LCD4bit_cmd(0x01);
}

void lcd_init(char y,char x){
	_delay_ms(40);
	LCD4bit_cmd(0x02);
	LCD4bit_cmd(0x28);
	lcd_on();
	LCD4bit_cmd(0x06);
	lcd_clear();
	LCD4bit_cmd(0x08);
}

void lcd_home(){
	LCD4bit_cmd(0x02);
}

void lcd_char(char character){
	PORTA = (PORTA & 0x0F) | (character & 0xF0); 
	PORTA |= 1<<RS;		
	PORTA |= (1<<EN);		
	_delay_ms(1);
	PORTA &= ~ (1<<EN);

	_delay_us(200);

	PORTA = (PORTA & 0x0F) | (character << 4); 
	PORTA |= (1<<EN);
	_delay_ms(1);
	PORTA &= ~ (1<<EN);
	_delay_ms(2);
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

