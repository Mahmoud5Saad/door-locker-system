/******************************************************************************
 *
 * 	Module: SPI
 *
 *	File Name: spi.c
 *
 * 	Description: source file for SPI module
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: May 6, 2019
 *
 *******************************************************************************/

#include "includes/spi.h"

void SPI_initMaster()
{
	SPI_PORT_DIR |= (1<<SS) | (1<<MOSI) | (1<<SCK);
	/*
	 * set up necessary pins for SPI:
	 * Output because this is the master:
	 * 1-Slave Select
	 * 2-Master Output Slave Input
	 * 3-Synchronous Clock
	 */
	SPI_PORT_DIR &= ~(1<<MISO);
	/*
	 * set up necessary pins for SPI:
	 * Input to master:
	 * 1-Master Input Slave Output
	 */

	SPSR |= (1<<SPI2X);
	/* bit 7:1 are flags not affected by what I write
	 * SPIX = 1
	 * SPR1 = 0, SPR0 = 0, and SPI2X in SPSR = 1
	 * (clock is equal to half frequency of CPU Fosc/2)
	 */
	SPCR = (1<<SPE) | (1<<MSTR);
	/*
	 * SPIE = 0 (interrupt disabled)
	 * SPE = 1 (spi module enabled)
	 * DORD = 0 (MSB is transferred first)
	 * MSTR = 1 (spi is enabled in master mode)
	 * CPOL = 0 (clock polarity is rising with leading edge,
	 * and falling with trailing edge)
	 * CPHA = 0 (data is sampled in the trailing edge of SCK)
	 * SPR1 = 0, SPR0 = 0, and SPI2X in SPSR = 1
	 * (clock is equal to half frequency of CPU Fosc/2)
	 */
}

void SPI_initSlave()
{
	SPI_PORT_DIR &= ~((1<<SS) | (1<<MOSI) | (1<<SCK));
	/*
	 * set up necessary pins for SPI:
	 * Input because it is slave:
	 * 1-Slave Select
	 * 2-Master Output Slave Input
	 * 3-Synchronous Clock
	 */
	SPI_PORT_DIR |= (1<<MISO);
	/*
	 * set up necessary pins for SPI:
	 * Output to slave:
	 * 1-Master Input Slave Output
	 */

	SPSR |= (1<<SPI2X);
	/* bit 7:1 are flags not affected by what I write
	 * SPIX = 1
	 * SPR1 = 0, SPR0 = 0, and SPI2X in SPSR = 1
	 * (clock is equal to half frequency of CPU Fosc/2)
	 */
	SPCR = (1<<SPE);
	/*
	 * SPIE = 0 (interrupt disabled)
	 * SPE = 1 (spi module enabled)
	 * DORD = 0 (MSB is transferred first)
	 * MSTR = 0 (spi is enabled in slave mode)
	 * CPOL = 0 (clock polarity is rising with leading edge,
	 * and falling with trailing edge)
	 * CPHA = 0 (data is sampled in the trailing edge of SCK)
	 * SPR1 = 0, SPR0 = 0, and SPI2X in SPSR = 1
	 * (clock is equal to half frequency of CPU Fosc/2)
	 */
}

void SPI_sendByte ( const uint8 byte)
{
	SPDR = byte;
	while (BIT_IS_CLEAR(SPSR,SPIF));
}

uint8 SPI_receiveByte ()
{
	while (BIT_IS_CLEAR(SPSR,SPIF));
	return SPDR;
}

void SPI_sendString (const char *string)
{
	uint8 i = 0;
	while ( *( string + i ) != '\0' )
	{
		SPI_sendByte( *(string +i) );
		i++;
	}
	SPI_sendByte('\0');
}

void SPI_receiveString(char * string)
{
	uint8 i = 0;
	char receivedByte;
	do
	{
		receivedByte = SPI_receiveByte();
		*(string + i) = receivedByte;
		i++;
	} while (receivedByte != '\0');
}
