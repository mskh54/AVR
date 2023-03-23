/*
 * KeyPad liberari
 *
 * Created: 3/22/2023 9:56:05 PM
 * Author : Mohammad sadegh KHodadadi
 */ 

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

#define keypad_pin PINA
#define keypad_port PORTA
#define keypad_ddr DDRA
char key[4][4] = {
	{ '1', '2', '3', 'A'},
	{ '4', '5', '6', 'B'},
	{ '7', '8', '9', 'C'},
	{ '*', '0', '#', 'D'}	
};

char Keypad(){
	unsigned char i;
    keypad_ddr = 0x0F;
	keypad_port = 0xFF;
	while (1){		
		for (i = 0 ; i<4 ; i++){
			keypad_port = ~(1<<i);
			if ( (keypad_pin & (1<<4) ) == 0 ){
				while( (keypad_pin & (1<<4) ) == 0 ){}
				return key[i][0];
			}
			if( (keypad_pin & (1<<5) ) == 0 ){
				while ( (keypad_pin & (1<<5) ) == 0 ){}
				return key[i][1];
			}
			if( (keypad_pin & (1<<6) ) == 0 ){
				while ( (keypad_pin & (1<<6) ) == 0 ){}
				return key[i][2];
			}
			if ( (keypad_pin & (1<<7) ) == 0 ){
				while ( (keypad_pin & (1<<7) ) == 0 ){}
				return key[i][3];
			}
		}
	}
}
