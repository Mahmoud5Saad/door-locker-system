/*
 * timer1.c
 *
 *  Created on: May 30, 2019
 *      Author: Saad
 */


#include "includes/timer1.h"

/*******************************************************************************
 *			Static global variables
 *******************************************************************************/
/* global : used by all of module
 * volatile : used by ISR and function
 * pointer to function variable initialized to NULL pointer in order to check its value
 * before accessing it. to save the Address the address
 * of the caller's function to be called after finishing the job
 */
static volatile void (*TIMER1_g_callback_Ptr) (void) = NULL_PTR;

/*******************************************************************************
 *			Functions Definitions
 *******************************************************************************/


void TIMER1_init ( const TIMER1_config *config_ptr )
{
	TCCR1A = (1<<FOC1A) | (1<<FOC1B) ;
	/* FOC1A:B = 11 because timer is used in non-PWM mode	 */

	TCNT1 = 0;
	/* clear the timer counter */

	if ( OVERFLOW == (config_ptr->mode) )
	{
		TIMSK |= (1<<TOIE1);
		/* enables the TIMER1 overflow interrupt */
	}
	else if ( COMPARE == (config_ptr->mode)  )
	{
		if ( CHANNEL_A == (config_ptr->channel) )
		{
			TIMSK |= (1<<OCIE1A);
			/* enables the TIMER1 overflow interrupt */
			OCR1A = (config_ptr->compareMatch) ;
			/* puts compare value in register of channel A */
		}
		else if ( CHANNEL_B == (config_ptr->channel) )
		{
			TIMSK |= (1<<OCIE1B);
			/* enables the TIMER1 overflow interrupt */
			OCR1B = (config_ptr->compareMatch) ;
			/* puts compare value in register of channel B */
		}
	}
	TCCR1B = (TCCR1B & 0xF8) | (config_ptr->clock);
	/* puts the desired clock speed for TIMER1 inside the first 3 bits of the TCCR1B register
	 * after clearing them */
}

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
void TIMER1_setCallback ( void (*callbackSet_ptr)(void) )
{
	TIMER1_g_callback_Ptr = callbackSet_ptr;
}

/**********************************************************************************************
 * 	Function name: ISR ( TIMER1_OVF_vect )
 *
 * 	Brief: interrupt function of TIMER1
 *
 * 	Details: function to be executed when the interrupt of TIMER1 is fired
 * 	it calls a function from the caller's layer by its address
 *
 * 	Arguments:
 * 		-none
 *
 * 	Return:
 * 		-none
 **********************************************************************************************/
ISR ( TIMER1_OVF_vect )
{
	if ( NULL_PTR != TIMER1_g_callback_Ptr )
	{
		(*TIMER1_g_callback_Ptr) ();
	}
}

/**********************************************************************************************
 * 	Function name: ISR ( TIMER1_COMPA_vect )
 *
 * 	Brief: interrupt function of TIMER1
 *
 * 	Details: function to be executed when the interrupt of TIMER1 is fired
 * 	it calls a function from the caller's layer by its address
 *
 * 	Arguments:
 * 		-none
 *
 * 	Return:
 * 		-none
 **********************************************************************************************/
ISR ( TIMER1_COMPA_vect )
{
	if ( NULL_PTR != TIMER1_g_callback_Ptr )
	{
		(*TIMER1_g_callback_Ptr) ();
	}
}
/**********************************************************************************************
 * 	Function name: ISR ( TIMER1_COMPB_vect )
 *
 * 	Brief: interrupt function of TIMER1
 *
 * 	Details: function to be executed when the interrupt of TIMER1 is fired
 * 	it calls a function from the caller's layer by its address
 *
 * 	Arguments:
 * 		-none
 *
 * 	Return:
 * 		-none
 **********************************************************************************************/
ISR ( TIMER1_COMPB_vect )
{
	if ( NULL_PTR != TIMER1_g_callback_Ptr )
	{
		(*TIMER1_g_callback_Ptr) ();
	}
}

void TIMER1_deinit ()
{
	TCNT1 = 0;
	TIMSK = 0;
	OCR1A = 0;
	OCR1B = 0;
	TCCR1A = 0;
	TCCR1B = 0;
}
