/*
 * timer2.c
 *
 *  Created on: Jun 3, 2019
 *      Author: Saad
 */

#include "includes/timer2.h"

void TIMER2_CTC_PWM_init ( TIMER2_PWM *config )
{

	DDRD |= (1<<PD7);
	/* set PD7 pin as output */

	PORTD &= ~(1<<PD7);
	/* get 0 out on it in the beginning */

	TCCR2 = ( 1<<WGM21 ) | (1<<WGM20) | ((config->edge)<<COM20) | (1<<COM21);
	/* FOC2 = 0 PWM mood
	 * WGMO21:0 = 11 fast PWM mood
	 * COM01:0 = 10 clear 0C0 on compare match, set 0C0 at BOTTOM.
	 * COM20 (non-inverting mood)
	 * CS22:0 = 010 prescalar F_CPU/8 125 KHZ
	 */

	TCCR2 = (TCCR2 & 0xF8 ) | ((config->clock) & 0x07);

	TCNT2 = 0;
	/* clear timer0 counter */

	OCR2 = (config->compare);
	/*  put the value of compare register in OCR0 */
}

void TIMER2_deinit ()
{
	OCR2 = 0;
	TCNT2 = 0;
	TCCR2 = 0;
}
