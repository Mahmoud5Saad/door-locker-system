/******************************************************************************
 *
 * 	Module: USART
 *
 *	File Name: uart.c
 *
 * 	Description: source file for USART module
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: May 6, 2019
 *
 *******************************************************************************/

#include "includes/uart.h"

volatile uint8 g_receivedByte;


uint8 UART_receiveByte ()
{
	while (BIT_IS_CLEAR(UCSRA,RXC));
	return UDR;
}


void UART_init (UART_config *config)
{
	UCSRA = ((config->speed)<<U2X);
	/* U2X = enable or disable double speed */

	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
	/* URSEL = 1 (write inside UCSRC and not UBBRH)
	 * UMSEL = 0 (Asynchronous operation)
	 * UPM 1:0 = 0 (Disable Parity)
	 * USBS = 0 (one stop bit in frame)
	 * UCPOL = 0 (Asynchronous mode)
	 * UCSZ1:0 = 0B11 (8-bit data in frame)
	 * */
	UBRRH = 0;
	/* URSEL = 0 (write in UBRRH)
	 *
	 */
	UBRRL = 12;
	/* set UBRRL to 51 to work on 2400 on double speed
	 * and 1 MHZ clock
	 *
	 */

	UCSRB = (1<<RXEN) | (1<<TXEN);
	/* RXCIE = 0 (do not fire interrupt when data is received)
	 * RXEN = 1 (UART receive enable)
	 * TXEN = 1 (UART transmit enable)
	 * */
}


void UART_sendByte ( uint8 byte)
{
	UDR = byte;
	while (BIT_IS_CLEAR(UCSRA,TXC));
	SET_BIT(UCSRA,TXC);
}


void UART_sendString ( const uint8 *string)
{
	uint8 i = 0;
	while ( *(string + i) != '\0' )
	{
		UART_sendByte( *(string + i) );
		i++;
	}
	UART_sendByte('\0');
}

void UART_receiveString ( uint8 *string)
{
	uint8 i = 0;
	uint8 recievedByte;
	do
	{
		recievedByte = UART_receiveByte();
		*(string + i) = recievedByte;
		i++;
	} while ( recievedByte != '\0' );
}
