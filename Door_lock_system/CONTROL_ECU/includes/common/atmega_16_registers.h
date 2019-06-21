/*
 * file name:   atmega_16_registers.h
 * Description: definition for all ports of atmega 16, for portability reasons
 *  Created on: Apr 25, 2019
 *      Author: Mahmoud Saad
 */

#ifndef INCLUDES_COMMON_ATMEGA_16_REGISTERS_H_
#define INCLUDES_COMMON_ATMEGA_16_REGISTERS_H_

#include "standard_types.h"

/* data direction register, input and output ports
 * for port A */
#define DATA_WRITE_PORTA		(*(volatile uint8 * const)0x003B)
#define DATA_DIRECTION_PORTA 	(*(volatile uint8 * const)0x003A)
#define DATA_READ_PORTA 		(*(volatile const uint8 * const)0x0039)

/* data direction register, input and output ports
 * for port B */
#define DATA_WRITE_PORTB 		(*(volatile uint8 * const)0x0038)
#define DATA_DIRECTION_PORTB 	((*(volatile uint8 * const)0x0037)
#define DATA_READ_PORTB 		((*(volatile const uint8 * const))0x0036)

/* data direction register, input and output ports
 * for port C */
#define DATA_WRITE_PORTC 		(*(volatile uint8 * const)0x0035)
#define DATA_DIRECTION_PORTC 	(*(volatile uint8 * const)0x0034)
#define DATA_READ_PORTC 		(*(volatile const uint8 * const)0x0033)

/* data direction register, input and output ports
 * for port D */
#define DATA_WRITE_PORTD 		(*(volatile uint8 * const)0x0032)
#define DATA_DIRECTION_PORTD 	(*(volatile uint8 * const)0x0031)
#define DATA_READ_PORTD 		(*(volatile const uint8 * const)0x0030)


#endif /* INCLUDES_COMMON_ATMEGA_16_REGISTERS_H_ */
