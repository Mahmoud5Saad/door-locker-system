/******************************************************************************
 *	File Name: my_stdlib.h
 *
 * 	Description: header file for my_itoa function
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: Apr 29, 2019
 *
 *******************************************************************************/


#ifndef INCLUDES_MY_STDLIB_H_
#define INCLUDES_MY_STDLIB_H_

#include "common/standard_types.h"

#ifndef NULL
#define NULL (*void)0
#endif

#define BASE_10 10
#define BASE_16 16
#define BASE_8  8
#define BASE_2  2

/*******************************************************************************
 *			Functions Prototypes
 *******************************************************************************/

void my_itoa(sint32 data, char * ptr, uint32 base);


#endif /* INCLUDES_MY_STDLIB_H_ */
