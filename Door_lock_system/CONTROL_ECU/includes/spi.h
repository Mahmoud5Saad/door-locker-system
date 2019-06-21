/******************************************************************************
 *
 * 	Module: SPI
 *
 *	File Name: spi.h
 *
 * 	Description: header file for SPI module
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: May 6, 2019
 *
 *******************************************************************************/

#ifndef INCLUDES_SPI_H_
#define INCLUDES_SPI_H_

#include "common/standard_types.h"
#include "common/common_macros.h"
#include "micro_config.h"

void SPI_initMaster();
void SPI_initSlave();
void SPI_sendByte ( const uint8 byte);
uint8 SPI_receiveByte ();
void SPI_sendString (const char * string);
void SPI_receiveString(char * string);


#endif /* INCLUDES_SPI_H_ */
