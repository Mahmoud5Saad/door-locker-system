/*
 * timer1.h
 *
 *  Created on: May 30, 2019
 *      Author: Saad
 */

#ifndef INCLUDES_TIMER1_H_
#define INCLUDES_TIMER1_H_

#include "common/standard_types.h"
#include "micro_config.h"
#include "common/common_macros.h"


#define CHANNEL_A 0
#define CHANNEL_B 1

/*******************************************************************************
 *			Enumerations and structures declarations
 *******************************************************************************/
typedef enum
{
	NO_CLOCK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
}TIMER1_clock;

typedef enum
{
	OVERFLOW, COMPARE
}TIMER1_mode;


typedef struct
{
	TIMER1_clock clock;
	TIMER1_mode mode;
	uint8 channel;
	uint16 compareMatch;
}TIMER1_config;

/*******************************************************************************
*			Functions Definitions
 *******************************************************************************/
void TIMER1_init ( const TIMER1_config *config_ptr );
/**********************************************************************************************
 * 	Function name: TIMER1_setCallback
 *
 * 	Brief: get's the address of the caller's function
 *
 * 	Details: stores the caller's function address to be called after finishing in a global
 * 	variable to be used by ISR
 *
 * 	Arguments:
 * 		-address of the caller's function to be called after finishing
 *
 * 	Return:
 * 		-none
 **********************************************************************************************/
void TIMER1_setCallback ( void (*callbackSet_ptr)(void) );

void TIMER1_deinit ();

#endif /* INCLUDES_TIMER1_H_ */
