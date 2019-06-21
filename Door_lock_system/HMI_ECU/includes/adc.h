/******************************************************************************
 *
 * 	Module: ADC
 *
 *	File Name: adc.h
 *
 * 	Description: header file for ADC driver
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: Apr 29, 2019
 *
 *******************************************************************************/


#ifndef INCLUDES_ADC_H_
#define INCLUDES_ADC_H_

#include "common/standard_types.h"
#include "micro_config.h"
#include "common/common_macros.h"

/* ADC port definitions */
#define CHANNEL_ZER0 PA0
#define CHANNEL_TWO PA2
#define ADC_PORT PORTA
#define ADC_PORT_DIR DDRA

/* #define ADC_INTERRUPT */


#ifdef ADC_INTERRUPT
	extern volatile uint16 g_ADC_value;
	void ADC_readChannel_int (uint8 channel);
#else
	uint16 ADC_readChannel(uint8 channel);
#endif

/*******************************************************************************
 *			Functions Prototypes
 *******************************************************************************/

/**********************************************************************************************
 * 	Function name: initializes the ADC
 *
 * 	Brief: initialize ADC to work with interrupts or pulling dependent on wether
 * 	the macro ADC_INTERRUPT is defined or not
 *
 * 	Details:
 *
 * 	Arguments:
 * 		-none
 *
 * 	Return:
 * 		-none
 **********************************************************************************************/
void ADC_init(void);

#endif /* INCLUDES_ADC_H_ */
