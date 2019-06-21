/******************************************************************************
 *
 * 	Module: Keypad
 *
 *	File Name: keypad.h
 *
 * 	Description: header file for keypad driver
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: Apr25, 2019
 *
 *******************************************************************************/


#ifndef INCLUDES_KEYPAD_H_
#define INCLUDES_KEYPAD_H_

#include "common/standard_types.h"
#include "micro_config.h"
#include "common/common_macros.h"


/*******************************************************************************
 *			Preprocessor Macros
 *******************************************************************************/
/* Keypad configurations for number of rows and columns */
#define COLUMNS 4
#define ROWS 4

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT DATA_WRITE_PORTA
#define KEYPAD_PORT_IN  DATA_READ_PORTA
#define KEYPAD_PORT_DIR DATA_DIRECTION_PORTA

/*******************************************************************************
 *			Functions Prototypes
 *******************************************************************************/

/**********************************************************************************************
 * 	Function name: KEYPAD_getPressedKey
 *
 * 	Brief: returns the pressed key on keypad
 *
 * 	Details: enters an infinite loop until the key is pressed going through the rows row by row
 * 	to set the one row as output and the rest with high impedence then loop on the coulmns
 * 	if any is pressed pass it to the adjust keynumber static function to modify it then
 * 	return the outcome to the caller
 *
 * 	Arguments:
 * 		-none
 *
 * 	Return:
 * 		-pressed key
 **********************************************************************************************/
uint8 KEYPAD_getPressedKey(void);


#endif /* INCLUDES_KEYPAD_H_ */
