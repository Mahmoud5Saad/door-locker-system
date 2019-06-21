/******************************************************************************
 *
 * 	Module: Keypad
 *
 *	File Name: kaypad.c
 *
 * 	Description: source file for keypad driver
 *
 * 	Author: Mahmoud Saad
 *
 * 	Created on: Apr 25, 2019
 *
 *******************************************************************************/

#include "includes/keypad.h"

/* function prototypes of private functions */

#if (COLUMNS == 3)
/**********************************************************************************************
 * 	Function name: KeyPad_4x3_adjustKeyNumber
 *
 * 	brief: returns the pressed key.
 *
 * 	Details: Function responsible for mapping the switch number in the keypad to its
 * 	corresponding functional number in the Proteus for 4x3 keypad. it does this by the use of a
 * 	simple formula which maps the buttons starting from the top left starting from 0 to 12.
 * 	Then calculate its number by this formula: (row*N_col)+col+1.
 *
 * 	Arguments :
 * 		-The pressed button as it appears to the user.
 *
 * 	Return:
 * 		-number itself in case of 0-9.
 * 		-ASCII of character in case of '*' or '#'.
 **********************************************************************************************/
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number);
#elif (COLUMNS == 4)

/**********************************************************************************************
 * 	Function name: KeyPad_4x4_adjustKeyNumber.
 * 	brief: returns the pressed key.
 * 	Details: Function responsible for mapping the switch number in the keypad to its
 * 	corresponding functional number in the Proteus for 4x3 keypad. it does this by the use of a
 * 	simple formula which maps the buttons starting from the top left starting from 0 to 15.
 * 	Then calculate its number by this formula: (row*N_col)+col+1.
 *
 * 	Arguments :
 * 		-The pressed button as it appears to the user.
 *
 * 	Return:
 * 		-number itself in case of 0-9.
 * 		-ASCII of character in case of '*', '#', '%', '-', '=', or '+'.
 **********************************************************************************************/
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);
#endif



/*******************************************************************************
 *			Functions Definitions
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
uint8 KEYPAD_getPressedKey(void)
{
	uint8 col, row;
	for (;;)
	{
		for ( col = 0; col < COLUMNS; col++)
		{
			KEYPAD_PORT_DIR = (0B00010000<<col);
			KEYPAD_PORT_OUT = (~(0B00010000<<col));
			for ( row = 0; row < ROWS; row++)
			{
				if (BIT_IS_CLEAR(KEYPAD_PORT_IN,row))
				{
					#if (COLUMNS == 3)
						return KEYPAD_4x3_adjustKeyNumber((row*COLUMNS)+col+1);
					#elif (COLUMNS == 4)
						return KEYPAD_4x4_adjustKeyNumber((row*COLUMNS)+col+1);
					#endif
				}
			}
		}
	}
}

#if (COLUMNS == 3)

/**********************************************************************************************
 * 	Function name: KeyPad_4x3_adjustKeyNumber
 *
 * 	brief: returns the pressed key.
 *
 * 	Details: Function responsible for mapping the switch number in the keypad to its
 * 	corresponding functional number in the Proteus for 4x3 keypad. it does this by the use of a
 * 	simple formula which maps the buttons starting from the top left starting from 0 to 12.
 * 	Then calculate its number by this formula: (row*N_col)+col+1.
 *
 * 	Arguments :
 * 		-The pressed button as it appears to the user.
 *
 * 	Return:
 * 		-number itself in case of 0-9.
 * 		-ASCII of character in case of '*' or '#'.
 **********************************************************************************************/
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number)
{
	switch(button_number)
	{
	case 10: return '*'; // ASCII Code of *
	break;
	case 11: return 0;
	break;
	case 12: return '#'; // ASCII Code of #
	break;
	default: return button_number;
	}
}

#elif (COLUMNS == 4)

/**********************************************************************************************
 * 	Function name: KeyPad_4x4_adjustKeyNumber.
 * 	brief: returns the pressed key.
 * 	Details: Function responsible for mapping the switch number in the keypad to its
 * 	corresponding functional number in the Proteus for 4x3 keypad. it does this by the use of a
 * 	simple formula which maps the buttons starting from the top left starting from 0 to 15.
 * 	Then calculate its number by this formula: (row*N_col)+col+1.
 *
 * 	Arguments :
 * 		-The pressed button as it appears to the user.
 *
 * 	Return:
 * 		-number itself in case of 0-9.
 * 		-ASCII of character in case of '*', '#', '%', '-', '=', or '+'.
 **********************************************************************************************/
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number)
{
	switch(button_number)
	{
	case 1: return 7;
	break;
	case 2: return 8;
	break;
	case 3: return 9;
	break;
	case 4: return '%'; // ASCII Code of %
	break;
	case 5: return 4;
	break;
	case 6: return 5;
	break;
	case 7: return 6;
	break;
	case 8: return '*'; /* ASCII Code of '*' */
	break;
	case 9: return 1;
	break;
	case 10: return 2;
	break;
	case 11: return 3;
	break;
	case 12: return '-'; /* ASCII Code of '-' */
	break;
	case 13: return 13;  /* ASCII of Enter */
	break;
	case 14: return 0;
	break;
	case 15: return '='; /* ASCII Code of '=' */
	break;
	case 16: return '+'; /* ASCII Code of '+' */
	break;
	default: return button_number;
	}
}

#endif
