/******************************************************************************
 *
 * 	Module: USART
 *
 *	File Name: uart.h
 *
 * 	Description: header file for USART module
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: May 6, 2019
 *
 *******************************************************************************/

#ifndef INCLUDES_UART_H_
#define INCLUDES_UART_H_

#include "common/atmega_16_registers.h"


#ifndef COMMON_INCLUDES
#define COMMON_INCLUDES
#include "common/standard_types.h"
#include "micro_config.h"
#include "common/common_macros.h"
#endif

extern volatile uint8 g_receivedByte;


typedef enum
{
	NORMAL, DOUBLE
}UART_speed;

typedef struct
{
	UART_speed speed;
}UART_config;

void UART_init (UART_config *config);
void UART_sendByte ( uint8 byte);
uint8 UART_receiveByte ();
void UART_sendString ( const uint8 *string);
void UART_receiveString ( uint8 *string);

#endif /* INCLUDES_UART_H_ */
