/*
 * lcd_4bit.c
 *
 * Created: 3/17/2023 2:52:34 PM
 * Author : Mohammad Sadegh Khodadadi
 */ 

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

#define LCD_Dir  DDRA			/* Define LCD data port direction */
#define LCD_Port PORTA
#define RS 0
#define RW 1
#define EN 2
#define x_lcd 16
#define y_lcd 2

void lcd_on();
void lcd_clear();
void lcd_home();
void lcd_Newline();
void lcd_right();
void lcd_left();
void lcd_char(char character);
void lcd_puts(char * string);
void lcd_init();
void lcd_goto(char y, char x);
void LCD_terminal(unsigned char cmd);


int main(void)
{
	lcd_init();
	lcd_puts("MOHAMMAD SADEGH");
	lcd_Newline();
	lcd_puts("KHODADADI");
	while(1){

	}
}

void LCD_terminal(unsigned char cmd)
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
	LCD_terminal(0x0c);
}
void lcd_clear(){
	LCD_terminal(0x01);
}
void lcd_init(){
	LCD_Dir = 0xFF;	
	_delay_ms(40);
	PORTA &= ~(1<<RW);
	LCD_terminal(0x33);
	LCD_terminal(0x32);
	LCD_terminal(0x28);
	lcd_on();
	LCD_terminal(0x06);
	lcd_clear();	
}
void lcd_home(){
	LCD_terminal(0x02);
}
void lcd_Newline(){
	LCD_terminal(0xC0);
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
	while( string[i] != 0 ){
		if (i == x_lcd)
			lcd_Newline();
		lcd_char(string[i]);
		i++;
	}

}
void lcd_right(){
	LCD_terminal(0x14);
}
void lcd_left(){
	LCD_terminal(0x10);
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

