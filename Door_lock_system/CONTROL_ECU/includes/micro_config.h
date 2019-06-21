/******************************************************************************
 *
 *	File Name: micro_config.h
 *
 * 	Description: file that holds the configurations dependant on the microcontroller.
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: Apr 25, 2019
 *
 *******************************************************************************/

#ifndef INCLUDES_MICRO_CONFIG_H_
#define INCLUDES_MICRO_CONFIG_H_

#ifndef F_CPU
#define F_CPU 8000000UL /* 8 MHZ CPU freq to be able to run I2C protocol */
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "common/atmega_16_registers.h"

#define SPI_PORT_DIR DDRB
#define SS PB4
#define MOSI PB5
#define MISO PB6
#define SCK PB7

#endif /* INCLUDES_MICRO_CONFIG_H_ */
