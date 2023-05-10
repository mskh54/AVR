#include <stdlib.h>
#include <stdio.h>

int USART_Transmit(char data, FILE *stream)
{
	/* Wait for empty transmit buffer*/
	while (! (UCSRA & (1<<UDRE)));	
	
	UDR = data ;
	return 0;
}

int USART_Receive(FILE *stream)
{
	/* Wait for data to be received */
	while (!(UCSRA & (1<<RXC)));
	
	/* Get and return received data from buffer */
	return UDR;
}


void UART_init(unsigned int USART_BAUDRATE)
{	
	UCSRB |= (1 << RXEN) | (1 << TXEN);/* Turn on transmission and reception */
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);/* Use 8-bit character sizes */
	
	//set UBRR register for config baudrate
	unsigned int set_ubrr = ( ((F_CPU / (USART_BAUDRATE * 16UL) )) - 1);
	UBRRL = (unsigned char)set_ubrr;		/* Load lower 8-bits of the baud rate value */
	UBRRH = (unsigned char)(set_ubrr >> 8);	/* Load upper 8-bits*/
	
	/* set config for use printf function and scanf function*/
	static FILE USART_stream_TX = FDEV_SETUP_STREAM(USART_Transmit, NULL, _FDEV_SETUP_WRITE);
	static FILE USART_stream_RX = FDEV_SETUP_STREAM(NULL, USART_Receive, _FDEV_SETUP_READ);
	stdout = &USART_stream_TX;
	stdin = &USART_stream_RX;
}
