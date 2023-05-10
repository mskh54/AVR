/*
 * software UART.c
 *
 * Created: 4/25/2023 2:20:51 AM
 * Author : mskh4
 */ 

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>

#define ddr_uart DDRB
#define uart_port PORTB
#define uart_pin PINB

#define RX_pin 0
#define TX_pin 1

void uart_begin(unsigned int baudrate);
void transmiter(char data);
void print(char *string);
void prime_number(char n);
int get_number();

unsigned int Baud_Rate;
volatile char result_RX = 0x00;
volatile unsigned char i;

ISR (INT0_vect){
	result_RX = 0x00;
	_delay_us(156);
	for(i = 0 ; i<=7 ; i++){
		result_RX |= ( (uart_pin & (1<<RX_pin) ) << i ) ;
		_delay_us(104);
	}
	_delay_us(104);
}

int main(void)
{
    ddr_uart = 0xff;
	uart_port = 0xff;
	DDRA = 0xff;
	PORTA = 0x00;

	GICR = 0x40;
	MCUCR = 0X04;
	GIFR = 0x40;
	sei();
	
	uart_begin(9600);
    while (1) 
    {
		if(result_RX != 0){
			//transmiter(0x7F);
			transmiter(result_RX);
			transmiter(':');
			//print("hello\n");
			prime_number(result_RX - 48);
			result_RX = 0;
		}
    }
}

int get_number(){
	char flag = 1;
	while(flag){
		
	}
	
}
void uart_begin(unsigned int baudrate){
	ddr_uart &= ~(1 << RX_pin); 
	ddr_uart |= (1 << TX_pin); 
	uart_port |= (1<< RX_pin);
	uart_port |= (1<< TX_pin); 
	Baud_Rate = baudrate;
}

void transmiter(char data){
	uart_port = 0x00;
	_delay_us(104);
	for (i =0 ; i<8 ; i++){
		if((data & 0x01) == 0x01)
			uart_port |= (1<<TX_pin);
		else
			uart_port &= ~(1<<TX_pin);
		data = data >> 1;
		_delay_us(104);
	}
	uart_port |= (1<<TX_pin);
	_delay_us(104);
}
void print( char * string){
	unsigned char i =0;
	while( string[i] != 0 ){
		transmiter(string[i]);
		i++;
	}
}
void prime_number(char n){
	char flag = 1;
	for (i = 2 ; i<= n/2 ; i++)
	{
		if(n%i == 0){
			print("number is not prim");
			flag = 0;
		}
	}
	if(flag)
		print("number is prim");
}
