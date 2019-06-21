/******************************************************************************
 *
 * 	Module: I2C
 *
 *	File Name: i2c.h
 *
 * 	Description: header file for I2C module
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: May 12, 2019
 *
 *******************************************************************************/

#ifndef INCLUDES_I2C_H_
#define INCLUDES_I2C_H_

#include "common/standard_types.h"
#include "common/common_macros.h"
#include "micro_config.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define  I2C_START        0x08
/* start has been sent */

#define I2C_REP_START     0x10
/* repeated start is sent */

#define I2C_M_T_SLA_W_ACK 0x18
/* Master transmit ( slave address + Write request ) to slave + Ack received from slave */

#define I2C_M_T_SLA_R_ACK 0x40
/* Master transmit ( slave address + Read request ) to slave + Ack received from slave */

#define I2C_M_T_DATA_ACK  0x28
/* Master transmit data and ACK has been received from Slave. */

#define I2C_M_R_DATA_ACK  0x50
/* Master received data and send ACK to slave */

#define I2C_M_R_DATA_NACK 0x58
/* Master received data but doesn't send ACK to slave */


#define I2U_FREQ 400000UL
#define TWBR_VALUE (((F_CPU/I2U_FREQ)-16)/2)
#define ECU_ADDRESS (0B0000001)

typedef enum
{
	NO_INTERRUPT, INTERRUPT
}I2C_interrupt;

typedef struct
{
	I2C_interrupt interrupt;
}I2C_config;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/**********************************************************************************************
 * 	Function name: I2C_init
 *
 * 	Brief: initializes the I2C module
 *
 * 	Details: intializes the I2C module to work with 400KHZ speed
 * 	gives the ECU an address of '1' on the bus
 *	interrupts are disabled
 * 	Arguments:
 * 		-none
 *
 * 	Return:
 * 		-none
 **********************************************************************************************/
void I2C_init ();

/**********************************************************************************************
 * 	Function name: I2C_start
 *
 * 	Brief: sends start bit on the bus
 *
 * 	Details: sends the start bit on the I2C bus. then waits by polling and doesn't
 * 	return until the flag TWINT is set
 *
 * 	Arguments:
 * 		-none
 *
 * 	Return:
 * 		-none
 **********************************************************************************************/
void I2C_start ();

/**********************************************************************************************
 * 	Function name: I2C_stop
 *
 * 	Brief: sends the stop bit on the I2C bus
 *
 * 	Details: sends the stop bit on the I2C bus and then returns
 *
 * 	Arguments:
 * 		-none
 *
 * 	Return:
 * 		-none
 **********************************************************************************************/
void I2C_stop ();

/**********************************************************************************************
 * 	Function name: I2C_write
 *
 * 	Brief: writes a byte to the bus
 *
 * 	Details: puts data in TWDR then clears the flag then waits until the flag is set
 * 	meaning it finished transmitting then quits
 *
 * 	Arguments:
 * 		-the byte to be sent
 *
 * 	Return:
 * 		-none
 **********************************************************************************************/
void I2C_write (uint8 data);

/**********************************************************************************************
 * 	Function name: I2C_readWithACK
 *
 * 	Brief: reads a byte and responds with an ACK bit
 *
 * 	Details: clears the flag, puts the TWEA = 1 to send an ACK after receiving,
 * 	then waits by polling until interrupt is set then returns with the TWDR register value
 *
 * 	Arguments:
 * 		-none
 *
 * 	Return:
 * 		-TWDR register value
 **********************************************************************************************/
uint8 I2C_readWithACK ();

/**********************************************************************************************
 * 	Function name: I2C_readWithNACK
 *
 * 	Brief: reads a byte and responds without an ACK bit
 *
 * 	Details: clears the flag, then waits by polling until interrupt is set.
 * 	 then returns with the TWDR register value
 *
 * 	Arguments:
 * 		-none
 *
 * 	Return:
 * 		-TWDR register value
 **********************************************************************************************/
uint8 I2C_readWithNACK ();

/**********************************************************************************************
 * 	Function name: I2C_getStatus
 *
 * 	Brief: fetches the TWSR flags
 *
 * 	Details: gets the value of TWSR register, masks the last 3 bits in it,
 * 	then return it to the caller
 *
 * 	Arguments:
 * 		-none
 *
 * 	Return:
 * 		-flags of TWSR register
 **********************************************************************************************/
uint8 I2C_getStatus();

#endif /* INCLUDES_I2C_H_ */
