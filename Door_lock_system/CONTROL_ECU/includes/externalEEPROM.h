/******************************************************************************
 *
 * 	Module: external EEPROM
 *
 *	File Name: externalEEPROM.h
 *
 * 	Description: header file for external EEPROM that works with I2C
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: May 13, 2019
 *
 *******************************************************************************/

#ifndef INCLUDES_EXTERNALEEPROM_H_
#define INCLUDES_EXTERNALEEPROM_H_

#include "common/standard_types.h"
#include "common/common_macros.h"
#include "micro_config.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

void EEPROM_init();
uint8 EEPROM_writeByte ( uint16 address, uint8 byte);
uint8 EEPROM_readByte(uint16 address, uint8 *receivedContainer);

#endif /* INCLUDES_EXTERNALEEPROM_H_ */
