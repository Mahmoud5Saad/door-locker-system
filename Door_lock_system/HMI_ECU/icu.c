/******************************************************************************
 *
 * 	Module: ICU
 *
 *	File Name: icu.c
 *
 * 	Description: source file for ICU module
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: Apr 30, 2019
 *
 *******************************************************************************/


#include "includes\icu.h"

/*******************************************************************************
 *			Static global variables
 *******************************************************************************/
/* global : used by all of module
 * volatile : used by ISR and function
 * pointer to function variable initialized to NULL pointer in order to check its value
 * before accessing it. to save the Address the address
 * of the caller's function to be called after finishing the job
 */
static volatile void (*g_callback_Ptr) (void) = NULL_PTR;

/*******************************************************************************
*			Functions Definitions
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
void ICU_init ( const ICU_config *config_ptr )
{
	CLEAR_BIT(DDRD,PD6);
	/* sets the direction of PD6 as input pin */

	TCCR1A = (1<<FOC1A) | (1<<FOC1B) ;
	/* FOC1A:B = 11 because timer is used in non-PWM mode	 */

	TCCR1B |= (TCCR1B & 0xBF) | ((config_ptr->edge)<<ICES1);
	/* puts the desired edge to work with inside the ICES1 in register TCCR1B  after
	 * clearing it  */

	TCCR1B |= (TCCR1B & 0xF8) | (config_ptr->clock);
	/* puts the desired clock speed for the ICU inside the first 3 bits of the TCCR1B register
	 * after clearing them */

	TCNT1 = 0;
	/* clear the timer counter */

	ICR1 = 0;
	/* clear the ICU */

	TIMSK |= (1<<TICIE1);
	/* enables the ICU interrupt */
}

/**********************************************************************************************
 * 	Function name: ICU_setCallback
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
void ICU_setCallback ( void (*callbackSet_ptr)(void) )
{
	g_callback_Ptr = callbackSet_ptr;
}

/**********************************************************************************************
 * 	Function name: ISR ( TIMER1_CAPT_vect )
 *
 * 	Brief: interrupt function of ICU
 *
 * 	Details: function to be executed whrn the interrupt of ICU is fired
 * 	it calls a function from the caller's layer by its address
 *
 * 	Arguments:
 * 		-none
 *
 * 	Return:
 * 		-none
 **********************************************************************************************/
ISR ( TIMER1_CAPT_vect )
{
	if ( NULL_PTR != g_callback_Ptr )
	{
		(*g_callback_Ptr) ();
	}
}

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
void ICU_setCaptureEdge ( ICU_edge edge)
{
	TCCR1B = ( TCCR1B & ~(1<<ICES1)) | (edge<<ICES1);
}

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
void ICU_deInit()
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;
	TIMSK &= ~(1<<TICIE1);
}

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
void ICU_clearTimerCounter ()
{
	TCNT1 = 0;
	ICR1 = 0;
}

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
uint16 ICU_getInputCaptureUnitValue()
{
	return ICR1;
}
