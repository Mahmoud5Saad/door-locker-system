/*
 * timer2.h
 *
 *  Created on: Jun 3, 2019
 *      Author: Saad
 */

#ifndef INCLUDES_TIMER2_H_
#define INCLUDES_TIMER2_H_

#include "common/standard_types.h"
#include "common/common_macros.h"
#include "micro_config.h"

typedef enum
{
	NO_CLOCK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
}TIMER2_clock;

typedef enum
{
	NON_INVERTING, INVERTING
}TIMER2_edge;

typedef struct
{
	TIMER2_clock clock;
	TIMER2_edge edge;
	uint8 compare;
}TIMER2_PWM;

void TIMER2_CTC_PWM_init ( TIMER2_PWM *config );
void TIMER2_deinit();


#endif /* INCLUDES_TIMER2_H_ */
