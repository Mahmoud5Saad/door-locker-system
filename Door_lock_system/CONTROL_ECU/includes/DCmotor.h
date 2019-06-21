/******************************************************************************
 *
 * 	Module: DC Motor
 *
 *	File Name: DCmotor.h
 *
 * 	Description: header file for DC Motor driver
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: May 14, 2019
 *
 *******************************************************************************/

#ifndef INCLUDES_DCMOTOR_H_
#define INCLUDES_DCMOTOR_H_

#include "common/standard_types.h"
#include "common/common_macros.h"
#include "micro_config.h"

#define MOTOR_PORT_DIR DDRB
#define MOTOR_PORT_OUT PORTB

#define IN1 PB0
#define IN2 PB1
#define MOTOR_HALF_SPEED 128

void DC_MOTOR_rotateAntiClockwise (uint8 speed);
void DC_MOTOR_rotateClockwise (uint8 speed);
void DC_MOTOR_init ();
void DC_MOTOR_stop ();


#endif /* INCLUDES_DCMOTOR_H_ */
