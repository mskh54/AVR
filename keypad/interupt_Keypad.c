/*
 * keypad_int.c
 *
 * Created: 4/14/2023 6:59:16 PM
 * Author : mskh4
 */ 

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd_4bit.c"

#define keypad_pin PINA
#define keypad_port PORTA
#define keypad_ddr DDRA

char key[4][4] = {
	{ '1', '2', '3', 'A'},
	{ '4', '5', '6', 'B'},
	{ '7', '8', '9', 'C'},
	{ '*', '0', '#', 'D'}
};




volatile char Read_key = '\0';
volatile unsigned char i;
ISR(INT0_vect){
	//lcd_clear();
	//lcd_puts("int");
	for (i = 0 ; i<4 ; i++){
		keypad_port = ~(1<<i);
		if ( (keypad_pin & (1<<4) ) == 0 ){
			while( (keypad_pin & (1<<4) ) == 0 ){}
			Read_key = key[i][0];
		}
		if( (keypad_pin & (1<<5) ) == 0 ){
			while ( (keypad_pin & (1<<5) ) == 0 ){}
			Read_key = key[i][1];
		}
		if( (keypad_pin & (1<<6) ) == 0 ){
			while ( (keypad_pin & (1<<6) ) == 0 ){}
			Read_key = key[i][2];
		}
		if ( (keypad_pin & (1<<7) ) == 0 ){
			while ( (keypad_pin & (1<<7) ) == 0 ){}
			Read_key = key[i][3];
		}
	}
	keypad_port = 0xF0;
}

int main(void)
{
	keypad_ddr = 0x0F;
	keypad_port = 0xF0;
	DDRB = 0xFF;
	PORTB = 0x00;
	
	GICR = 0x40;
	MCUCR = 0x04;
	GIFR = 0x40;
	sei();
	lcd_init();
	
	PORTC &= ~(1<<3);

	char id[10] = "983110283\0";
	char password[11] = "4420984058\0";
	char your_id[10];
	char your_Password[11];
	
	//char enter_key;
	char flag;
	char flag_start = 0;
	char flag_id = 1;
	char flag_output = 0;
	unsigned char i ;
	char counter = 0;
	
	while (1){
		if(flag_start == 0){
			lcd_clear();
			lcd_puts("PLEASE ENTER \"A\"KEY FOR START:");
			flag_start = 2;	
		}
		
		if (Read_key != '\0'){
			if (flag_start == 2 && Read_key == 'A'){
				flag_start = 1;
				Read_key = '\0';
				lcd_clear();
				lcd_puts("ID:");
				counter = 0;
			}
			else if(flag_start){
				if(flag_id){
					your_id[counter] = Read_key;
					lcd_char(your_id[counter]);
					Read_key = '\0';
					counter++;
					if(counter ==9){
						your_id[counter] = '\0';
						counter = 0;
						flag_id = 0;
						
						lcd_Newline();
						lcd_puts("pass:");
					}
				}
				else{//got id and ready to get pass
					your_Password[counter] = Read_key;
					lcd_char(your_Password[counter]);
					Read_key = '\0';
					counter++;
					if(counter == 10){
						your_Password[10] = '\0';
						counter = 0;
						flag_id = 1;
						flag_output = 2;
					}
				}
			}
		}
					 
		if(flag_output == 2){
			
			lcd_Newline();
			lcd_puts(your_Password);
			_delay_ms(2000);
			flag =1;
			for(i =0 ; i<10 ; i++){
				if(your_Password[i] != password[i]){
					flag = 0;
					break;
				}
				else if(your_id[i] != id[i]){
					if (i == 9)
						break;
					else{
						flag = 0;
						break;
					}
				}
			}
			flag_output = 1;
		}
		if(flag_output){
			if (flag){
				lcd_clear();
				lcd_puts("WELLCOME");
				PORTC |= 1<<3;
				_delay_ms(2000);
				PORTC &= ~(1<<3);
				flag_start = 0;
				flag_output = 0;
			}
			else{
				lcd_clear();
				lcd_puts("incorrect ID OR password");
				_delay_ms(2000);
				flag_start = 0;
				flag_output = 0;
			}
		}
		PORTB ++;
	}
}
 
