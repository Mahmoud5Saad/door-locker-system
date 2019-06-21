/******************************************************************************
 *
 * 	Module: Timer 0
 *
 *	File Name: timer0.h
 *
 * 	Description: header file for Timer 0 driver
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: May 14, 2019
 *
 *******************************************************************************/

#ifndef INCLUDES_TIMER0_H_
#define INCLUDES_TIMER0_H_

#include "common/standard_types.h"
#include "micro_config.h"
#include "common/common_macros.h"

typedef enum
{
	NO_CLOCK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
}TIMER0_clock;

typedef enum
{
	NON_INVERTING, INVERTING
}TIMER0_edge;

typedef struct
{
	TIMER0_clock clock;
	TIMER0_edge edge;
	uint8 compare;
}TIMER0_PWM;

void TIMER0_CTC_PWM_init ( TIMER0_PWM *config );
void TIMER0_deinit();

#endif /* INCLUDES_TIMER0_H_ */
