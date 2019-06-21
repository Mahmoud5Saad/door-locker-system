/******************************************************************************
 *
 * 	Module: ICU
 *
 *	File Name: icu.h
 *
 * 	Description: header file for ICU module
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: Apr 30, 2019
 *
 *******************************************************************************/

#ifndef INCLUDES_ICU_H_
#define INCLUDES_ICU_H_

#include "common/standard_types.h"
#include "common/common_macros.h"
#include "micro_config.h"

/*******************************************************************************
 *			Enumerations and structures declarations
 *******************************************************************************/
typedef enum
{
	FALLING, RISING
}ICU_edge;

typedef enum
{
	NO_CLOCK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
}ICU_clock;

typedef struct
{
	ICU_edge edge;
	ICU_clock clock;
}ICU_config;

/*******************************************************************************
 *			Functions Prototypes
 *******************************************************************************/
/**********************************************************************************************
 * 	Function name: ICU_init
 *
 * 	Brief: a function the initializes the ICU module
 *
 * 	Details: function the initializes the ICU module based on configurations
 * 	given by the means of a pointer to structure as an argument:
 *
 * 	Arguments:
 * 		-pointer to structure
 *
 * 	Return:
 * 		-none
 **********************************************************************************************/
void ICU_init ( const ICU_config *config_ptr );

/**********************************************************************************************
 * 	Function name: ICU_setCallback
 *
 * 	Brief: get's the address of the caller's function
 *
 * 	Details: stores the caller's function address to be called after finisihing in a global
 * 	variable to be used by ISR
 *
 * 	Arguments:
 * 		-address of the caller's function to be called after finishing
 *
 * 	Return:
 * 		-none
 **********************************************************************************************/
void ICU_setCallback ( void (*callbackSet_ptr)(void) );

/**********************************************************************************************
 * 	Function name: ICU_setCaptureEdge
 *
 * 	Brief: sets the edge that the ICU should capture
 *
 * 	Details: takes value from the enum edge and stores it in ICES1 in TCCR1B. on which basis
 * 	ICU is invoked
 *
 * 	Arguments:
 * 		-edge enum
 *
 * 	Return:
 * 		-none
 **********************************************************************************************/
void ICU_setCaptureEdge ( ICU_edge edge);

/**********************************************************************************************
 * 	Function name: ICU_deInit
 *
 * 	Brief: disables ICU module
 *
 * 	Details: clears out all the module registers
 *
 * 	Arguments:
 * 		-none
 *
 * 	Return:
 * 		-none
 **********************************************************************************************/
void ICU_deInit();

/**********************************************************************************************
 * 	Function name: ICU_clearTimerCounter
 *
 * 	Brief: clear timer counter
 *
 * 	Details: clears TCNT1 and ICR1
 *
 * 	Arguments:
 * 		-none
 *
 * 	Return:
 * 		-none
 **********************************************************************************************/
void ICU_clearTimerCounter ();

/**********************************************************************************************
 * 	Function name: ICU_getInputCaptureUnitValue
 *
 * 	Brief: gets the value in ICU register
 *
 * 	Details: returns ICR1 register value
 *
 * 	Arguments:
 * 		-none
 *
 * 	Return:
 * 		-returns 16 bit value inside ICR1 register
 **********************************************************************************************/
uint16 ICU_getInputCaptureUnitValue();

#endif /* INCLUDES_ICU_H_ */
