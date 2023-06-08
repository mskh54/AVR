void SPI_Master_Init(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB |= (1<< PORTB5)|(1<< PORTB7 )|(1<< PORTB4);
	DDRB &= ~(1<<PORTB6);
	
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	
}
void SPI_Master_Transmit(char Data)
{
	/* Start transmission */
	SPDR = Data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}

char SPI_Master_Receive(void)
{
	SPDR = 0x00;
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)));

	/* Return data register */
	return SPDR;
}

void SPI_Slave_Init(void)
{
	/* Set MISO output, all others input */
	DDRB |= (1<<PORTB6);
	DDRB &= ~((1<<PORTB5)|(1<<PORTB7)|(1<<PORTB4));
	
	/* Enable SPI */
	SPCR = (1<<SPE);
}
char SPI_Slave_Receive(void)
{
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)));
	
	/* Return data register */
	return SPDR;
}
void SPI_Slave_Transmit(char Data)
{
	/* Start transmission */
	SPDR = Data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}