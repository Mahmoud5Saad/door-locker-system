/*
 * buzzer.c
 *
 *  Created on: Jun 3, 2019
 *      Author: Saad
 */


#include "includes/buzzer.h"
#include "includes/timer0.h" /* so that it doesn't go to app layer */

TIMER0_PWM config = { F_CPU_1024, NON_INVERTING, 128 };

void BUZZER_init ()
{
	TIMER0_CTC_PWM_init(&config);
}

void BUZZER_deinit ()
{
	TIMER0_deinit();
}
