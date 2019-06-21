/******************************************************************************
 *
 * 	Module: DC Motor
 *
 *	File Name: DCmotor.c
 *
 * 	Description: source file for DC Motor driver
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: May 14, 2019
 *
 *******************************************************************************/

#include "includes/DCmotor.h"
#include "includes/timer0.h" /* so that it doesn't go to application layer */

/*******************************************************************************
*			Functions Definitions
 *******************************************************************************/
TIMER0_PWM configuration = { F_CPU_8, NON_INVERTING, 0 };

void DC_MOTOR_stop ()
{
	CLEAR_BIT(MOTOR_PORT_OUT,IN1);
	CLEAR_BIT(MOTOR_PORT_OUT,IN2);
}

void DC_MOTOR_init ()
{
	SET_BIT(MOTOR_PORT_DIR,IN1);
	SET_BIT(MOTOR_PORT_DIR,IN2);

	CLEAR_BIT(MOTOR_PORT_OUT,IN1);
	CLEAR_BIT(MOTOR_PORT_OUT,IN2);
}

void DC_MOTOR_rotateClockwise (uint8 speed)
{
	CLEAR_BIT(MOTOR_PORT_OUT,IN1);
	CLEAR_BIT(MOTOR_PORT_OUT,IN2);

	SET_BIT(MOTOR_PORT_OUT,IN2);
	(configuration.compare) = speed;
	TIMER0_CTC_PWM_init (&configuration);
}

void DC_MOTOR_rotateAntiClockwise (uint8 speed)
{
	CLEAR_BIT(MOTOR_PORT_OUT,IN1);
	CLEAR_BIT(MOTOR_PORT_OUT,IN2);

	SET_BIT(MOTOR_PORT_OUT,IN1);
	(configuration.compare) = speed;
	TIMER0_CTC_PWM_init (&configuration);
}
