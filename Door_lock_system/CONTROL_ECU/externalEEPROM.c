/******************************************************************************
 *
 * 	Module: external EEPROM
 *
 *	File Name: externalEEPROM.c
 *
 * 	Description: source file for external EEPROM that works with I2C
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: May 13, 2019
 *
 *******************************************************************************/



#include "includes/externalEEPROM.h"
#include "includes/i2c.h"

void EEPROM_init()
{
	I2C_init();

	/* external EEPROM working with I2C,
	 * enable I2C to be able to use it.
	 */
}

uint8 EEPROM_writeByte ( uint16 address, uint8 byte)
{
	I2C_start ();
	/* send the start bit */
	if ( I2C_getStatus() != I2C_START)
	{
		return ERROR;
		/* check the status register:
		 * if the start bit is sent correctly continue.
		 * if it is not sent correctly abort and return error.
		 */
	}

	/* external EEPROM of this model has a unique way
	 * of sending the address to be written
	 * it has 2048 bytes, so 11 bits of address are needed
	 * so it send the 11 bits on 2 parts
	 * first part is in the address of the slave by adding 3 bits in tha 7 bit address from
	 * LSB side.
	 * and the rest of the address is sent as 8 bit byte as a whole
	 */
	I2C_write( (uint8)( 0xA0 | ((address & 0x0700) >> 7) ));
	/* send the first byte of the address */
	if ( I2C_getStatus() != I2C_M_T_SLA_W_ACK)
	{
		return ERROR;
		/* check the status register:
		 * if the address is sent correctly continue.
		 * if it is not sent correctly abort and return error.
		 */
	}

	I2C_write( (uint8) ( address & 0x00FF ) );
	/* send the second part of the address */
	if ( I2C_getStatus() != I2C_M_T_DATA_ACK)
	{
		return ERROR;
		/* check the status register:
		 * if the address is sent correctly continue.
		 * if it is not sent correctly abort and return error.
		 */
	}

	I2C_write( byte );
	/* send the data to be written */
	if ( I2C_getStatus() != I2C_M_T_DATA_ACK)
	{
		return ERROR;
		/* check the status register:
		 * if the data is sent correctly continue.
		 * if it is not sent correctly abort and return error.
		 */
	}

	I2C_stop ();
	/* sends stop bit */

	return SUCCESS;
	/* if reaches the end without any errors
	 * return success
	 */
}

uint8 EEPROM_readByte(uint16 address, uint8 *receivedContainer)
{
	I2C_start ();
	/* send the start bit */
	if ( I2C_getStatus() != I2C_START)
	{
		return ERROR;
		/* check the status register:
		 * if the start bit is sent correctly continue.
		 * if it is not sent correctly abort and return error.
		 */
	}

	/* external EEPROM of this model has a unique way
	 * of sending the address to be written
	 * it has 2048 bytes, so 11 bits of address are needed
	 * so it send the 11 bits on 2 parts
	 * first part is in the address of the slave by adding 3 bits in tha 7 bit address from
	 * LSB side.
	 * and the rest of the adress is sent as 8 bit byte as a whole
	 */
	I2C_write( (uint8) ( (0xA0) | ((address & 0x0700) >> 7) ));
	/* send the first byte of the address */
	if ( I2C_getStatus() != I2C_M_T_SLA_W_ACK)
	{
		return ERROR;
		/* check the status register:
		 * if the address is sent correctly continue.
		 * if it is not sent correctly abort and return error.
		 */
	}

	I2C_write( (uint8) (address) );
	/* send the second part of the address */
	if ( I2C_getStatus() != I2C_M_T_DATA_ACK)
	{
		return ERROR;
		/* check the status register:
		 * if the address is sent correctly continue.
		 * if it is not sent correctly abort and return error.
		 */
	}

	I2C_start ();
	/* send the start bit */
	if ( I2C_getStatus() != I2C_REP_START)
	{
		return ERROR;
		/* check the status register:
		 * if the repeated start bit is sent correctly continue.
		 * if it is not sent correctly abort and return error.
		 */
	}

	I2C_write( (uint8) ( (0xA0) | ((address & 0x0700)>>7) | 1 ));
	/* send the first byte of the address */
	if ( I2C_getStatus() != I2C_M_T_SLA_R_ACK)
	{
		return ERROR;
		/* check the status register:
		 * if the address is sent correctly continue.
		 * if it is not sent correctly abort and return error.
		 */
	}

	*receivedContainer = I2C_readWithNACK();
	if ( I2C_getStatus() != I2C_M_R_DATA_NACK)
	{
		return ERROR;
		/* check the status register:
		 * if the byte is read correctly continue.
		 * if it is not sent correctly abort and return error.
		 */
	}

	I2C_stop ();
	/* sends stop bit */

	return SUCCESS;
	/* if reaches the end without any errors
	 * return success
	 */
}

