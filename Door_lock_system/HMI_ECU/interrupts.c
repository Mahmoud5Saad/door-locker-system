/*
 * interrupts.c
 *
 *  Created on: May 14, 2019
 *      Author: Saad
 */

#include "includes/interrupts.h"
#include "includes/DCmotor.h"

ISR ( INT1_vect )
{

}

void INTERRUPT1_init ()
{
	GICR |= (1<<INT1);
	/* INT1 = 1 enable interrupt 1 */

	MCUCR |= (1<<ISC11) | (1<<ISC10);
	/* ISC11:0 = 11 generate interrupt request on rising edge */
}
