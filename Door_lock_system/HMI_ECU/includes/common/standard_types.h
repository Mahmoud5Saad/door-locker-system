/*
 *  File name : standard_types.h
 *  Created on: Apr 24, 2019
 *  Author    : Mahmoud Saad
 *  Description: data types for ATMEGA16 AVR
 */

#ifndef INCLUDES_COMMON_STANDARD_TYPES_H_
#define INCLUDES_COMMON_STANDARD_TYPES_H_

/* boolean data type */
typedef unsigned char bool;

/* boolean values */
#ifndef TRUE
#define TRUE (0U)
#endif

#ifndef FALSE
#define FALSE (1U)
#endif

#ifndef HIGH
#define HIGH (1U)
#endif

#ifndef LOW
#define LOW (0U)
#endif

#define NULL_PTR ((void *)0)


/* Data types abstraction */
typedef unsigned char		uint8;
typedef signed char			sint8;
typedef unsigned short		uint16;
typedef signed short		sint16;
typedef unsigned long		uint32;
typedef signed long			sint32;
typedef unsigned long long	uint64;
typedef signed long long	sint64;
typedef float				float32;
typedef double				float64;

#endif /* INCLUDES_COMMON_STANDARD_TYPES_H_ */
