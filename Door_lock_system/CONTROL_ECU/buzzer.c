/*
 * buzzer.c
 *
 *  Created on: Jun 3, 2019
 *      Author: Saad
 */


#include "includes/buzzer.h"
#include "includes/timer2.h" /* so that it doesn't go to app layer */

TIMER2_PWM config = { F_CPU_1024, NON_INVERTING, 128 };

void BUZZER_init ()
{
	TIMER2_CTC_PWM_init(&config);
}

void BUZZER_deinit ()
{
	TIMER2_deinit();
}
