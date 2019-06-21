/******************************************************************************
 *
 * 	Module: I2C
 *
 *	File Name: i2c.c
 *
 * 	Description: source file for I2C module
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: May 12, 2019
 *
 *******************************************************************************/

#include "includes/i2c.h"

/*******************************************************************************
*			Functions Definitions
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
void I2C_init ()
{
	TWBR = (uint8) TWBR_VALUE;
	/* TWBR_VALUE is calculated through (((F_CPU/I2U_FREQ)-16)/2)
	 * depending on ICU_FREQ value */

	TWSR = 0;
	/* TWPS = 0 it is ignored in the calculation of prescalar
	 * (((F_CPU/I2U_FREQ)-16)/2)
	 * because it is not needed to achieve 400KHZ*/

	TWAR = (ECU_ADDRESS<<1);
	/* gives ECU address of 1 on the bus to use when called as slave */

	TWCR = (1<<TWEN);
	/* TWEN = 1 enables I2C
	 * TWIE = 0 disables interrupts
	 */

}

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
void I2C_start ()
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	/* TWSTA = 1 generates start bit on the I2C bus
	 * TWEN = 1 enables I2C
	 * TWIE = 0 disables interrupts
	 * TWINT = 1 clears the flag of I2C
	 * */

	while (BIT_IS_CLEAR(TWCR,TWINT));
	/* Polling until the interrupt flag is set meaning the start bit is
	 * generated on the bus
	 */
}

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
void I2C_stop ()
{
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
	/* TWSTO = 1 generates stop bit on the I2C bus
	 * TWEN = 1 enables I2C
	 * TWIE = 0 disables interrupts
	 * TWINT = 1 clears the flag of I2C
	 */
}

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
void I2C_write (uint8 data)
{
	TWDR = data;
	/* put the next byte to be written in the data register
	 *
	 */
	TWCR = (1<<TWINT) | (1<<TWEN);
	/* TWEN = 1 enables I2C
	 * TWIE = 0 disables interrupts
	 * TWINT = 1 clears the flag of I2C
	 */

	while (BIT_IS_CLEAR(TWCR,TWINT));
	/* Polling until the interrupt flag is set meaning the byte bit is
	 * sent on the bus
	 */
}

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
uint8 I2C_readWithACK ()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	/* TWEN = 1 enables I2C
	 * TWIE = 0 disables interrupts
	 * TWINT = 1 clears the flag of I2C
	 * TWEA = 1 send acknowledgment ACK after receiving the byte
	 */

	while (BIT_IS_CLEAR(TWCR,TWINT));
	/* Polling until the interrupt flag is set meaning the byte bit is
	 * received from the bus
	 */

	return TWDR;
	/* return the data of the TWDR register */
}

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
uint8 I2C_readWithNACK ()
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	/* TWEN = 1 enables I2C
	 * TWIE = 0 disables interrupts
	 * TWINT = 1 clears the flag of I2C
	 */

	while (BIT_IS_CLEAR(TWCR,TWINT));
	/* Polling until the interrupt flag is set meaning the byte bit is
	 * received from the bus
	 */

	return TWDR;
	/* return the data of the TWDR register */
}

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
uint8 I2C_getStatus()
{
	uint8 status;
	status =  TWSR & 0xF8;
	/* mask the last 3 bits of the TWSR register */

	return status;
	/* return the I2C status register with the 3 least significant bits masked */
}
