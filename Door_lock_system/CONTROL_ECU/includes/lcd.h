/******************************************************************************
 *
 * 	Module: LCD
 *
 *	File Name: lcd.h
 *
 * 	Description: header file for LCD driver
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: Apr 28, 2019
 *
 *******************************************************************************/


#ifndef INCLUDES_LCD_H_
#define INCLUDES_LCD_H_

#include "common/standard_types.h"
#include "common/common_macros.h"
#include "micro_config.h"


/* LCD pins definition */


/*******************************************************************************
 *			Preprocessor Macros
 *******************************************************************************/

/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 8

/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == 4)
//#define UPPER_PORT_PINS
#endif

#define RS PD2
#define RW PD3
#define E  PD4
#define LCD_CTRL_PORT PORTD
#define LCD_CTRL_PORT_DIR DDRD

#define LCD_DATA_PORT PORTA
#define LCD_DATA_PORT_DIR DDRA

/* definitions for LCD commands */

#define CLEAR_SCREEN 0x01
#define TWO_LINE_LCD_EIGHT_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_FOUR_BIT_MODE 0x28


/*******************************************************************************
*			Functions Definitions
 *******************************************************************************/

void LCD_init (void);
void LCD_sendCommand (uint8 command);
void LCD_displayCharacter (const uint8 character);
void LCD_displayString (const uint8 * str);
void LCD_goToRowColumn (uint8 row, uint8 col);
void LCD_displayStringRowColumn ( uint8 row, uint8 col, const uint8 * str);
void LCD_clearScreen (void);
void LCD_integerToString (sint32 data);
void LCD_displayStringCoutation (const char *str);

#endif /* INCLUDES_LCD_H_ */
