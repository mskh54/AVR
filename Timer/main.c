/*
 * creat_pulse.c
 *
 * Created: 5/22/2023 12:11:11 AM
 * Author : mskh4
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include "interupt_Keypad.c"


int main(void)
{
	DDRB = 0xff;
	PORTB = 0x00;
	DDRA = 0xff;
	PORTA = 0x00;
	//set clk = Foc/64 and normal pwm afther 1us tcnt0++ 
	TCCR0 |= (1<<WGM01) | (1<<COM00) | (1<<CS01)|(1<<CS00);

	// defult frequncy is 1k
	OCR0 = 62;

    keypad_init();
    while (1)
    {
		if (Read_key != '\0'){
			switch(Read_key){
				case '1':
					OCR0 = 62;
					PORTA = 1;
					break;
			
				case '2':
					OCR0 = 31;
					PORTA = 2;
					break;
			
				case '3':
					OCR0 = 21;
					PORTA = 3;
					break;
			
				case '4':
					OCR0 = 16;
					PORTA = 4;
					break;
			
				case '5':
					OCR0 = 12;
					PORTA = 5;
					break;
			
				case '6':
					OCR0 = 10;
					PORTA = 6;
					break;
			
				case '7':
					OCR0 = 9;
					PORTA = 7;
					break;

				case '8':
					OCR0 = 7;
					PORTA = 8;
					break;

				case '9':
					OCR0 = 6;
					PORTA = 9;
					break;
		
			}
		}
    }
}














































	
	//case '*':
	//if (OCR0>10)
	//{
	//OCR0 -=10;
	//Read_key = '\0';
	//}
	//else{
	//OCR0 = 0;
	//Read_key = '\0';
	//}
	//break;
	//
	//case '#':
	//if (OCR0<245)
	//{
	//OCR0 +=10;
	//Read_key = '\0';
	//}
	//else{
	//OCR0 = 255;
	//Read_key = '\0';
	//}
	//
	//break;
	//
	//