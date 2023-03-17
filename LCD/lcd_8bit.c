#include "lcd.h"
#define x_lcd 16;
#define y_lcd 2;

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

void lcd_Newline(){
	PORTA &= ~(1 << RS);
	PORTA |= 1 << EN;
	PORTD = 0xC0;
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
	while( string[i] != 0 ){
		if (i == x_lcd)
			lcd_Newline();
		lcd_char(string[i]);
		i++;
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
		default:
			for(i = 1 ; i<y ; i++)
				lcd_Newline();
			for ( i=0; i<x; i++)
				lcd_right();
			break;
	}
}