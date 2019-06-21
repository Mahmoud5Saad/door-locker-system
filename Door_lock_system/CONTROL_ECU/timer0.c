/******************************************************************************
 *
 * 	Module: Timer 0
 *
 *	File Name: timer0.c
 *
 * 	Description: source file for Timer 0 driver
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: May 14, 2019
 *
 *******************************************************************************/

#include "includes/timer0.h"

void TIMER0_CTC_PWM_init ( TIMER0_PWM *config )
{

	DDRB |= (1<<PB3);
	/* set PB3 pin as output */

	PORTB &= ~(1<<PB3);
	/* get 0 out on it in the beginning */

	TCCR0 = ( 1<<WGM01 ) | (1<<WGM00) | ((config->edge)<<COM00) | (1<<COM01);
	/* FOC0 = 0 PWM mood
	 * WGMO01:0 = 11 fast PWM mood
	 * COM01:0 = 10 clear 0C0 on compare match, set 0C0 at BOTTOM.
	 * (non-inverting mood)
	 * CS02:0 = 010 prescalar F_CPU/8 125 KHZ
	 */

	TCCR0 = (TCCR0 & 0xF8 ) | ((config->clock) & 0x07);

	TCNT0 = 0;
	/* clear timer0 counter */

	OCR0 = (config->compare);
	/*  put the value of compare register in OCR0 */
}

void TIMER0_deinit ()
{
	OCR0 = 0;
	TCNT0 = 0;
	TCCR0 = 0;
}
