/******************************************************************************
 *
 *	File Name: hmi.c
 *
 * 	Description:
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: May 16, 2019
 *
 *******************************************************************************/


#include "includes/lcd.h"
#include "includes/keypad.h"
#include "includes/uart.h"
#include "includes/timer1.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void APP_setupPassword ();
void APP_openDoor ();
void APP_readString();
void APP_changePassword ();
void APP_deafult();
void APP_openDoorLCDNotification ();
void APP_BUZZ_CONTROL ();
void APP_setupPasswordInit();

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define MAXIMUM_PASSWORD_LENGTH 		16

#define CHANGE_PASSWORD 		0
#define OPEN_DOOR				1
#define SETUP_PASSWORD			2
#define IS_PASSWORD_SETUP 		3
#define EEPROM_IS_CLEAR 		4
#define EEPROM_IS_SETUP 		5
#define FAILED_PASSWORD 		6
#define SUCCESSFUL_PASSWORD 	7
#define PASSWORDS_DONT_MATCH 	8
#define PASSWORDS_MATCH 		9
#define BUZZ					10
#define STRING_TERMINATOR		'\0'

#define HUMAN_CLICK 400
#define HUMAN_EYE_VISION 3000

/*******************************************************************************
 *                      Variable declarations                                  *
 *******************************************************************************/
uint8 g_disableDefaultFlag = 0;
uint8 g_pressedKey = 0;
uint8 g_passwordArray[MAXIMUM_PASSWORD_LENGTH] = {0};
TIMER1_config g_config_buzzer = { F_CPU_1024, OVERFLOW, CHANNEL_A, 0};
UART_config UART_configuration = { DOUBLE };
TIMER1_config g_config_open = { F_CPU_256, OVERFLOW, CHANNEL_A, 0};

/*******************************************************************************
 *			Functions Definitions
 *******************************************************************************/
void APP_readString()
{
	uint8 i = 0;
	do
	{
		/* read a password with PASSWORD_LENGTH */
		_delay_ms(HUMAN_CLICK);
		/* delay 400 milliseconds to avoid multiple presses */
		*(g_passwordArray + i) = KEYPAD_getPressedKey();
		/* put any input key inside an array */
		LCD_displayCharacter('*');
		/* give the user indication that he entered a digit */
		i++;
	} while ( 13 != *(g_passwordArray + (i - 1)) );
	*(g_passwordArray + i - 1 ) = '\0';
	/* write a NULL after the last digit to indicate end of string */
}

void APP_changePassword ()
{
	static uint8 failureCount = 0;
	uint8 checkByte = 0;
	UART_sendByte (CHANGE_PASSWORD);
	/* inform control_ECU that we will change password */
	LCD_clearScreen();
	/* clears screen */
	LCD_displayStringCoutation ("Enter Old Pass:");
	/* display message to guide user */
	LCD_goToRowColumn (1,0);
	/* lower cursor to second line */
	APP_readString();
	/* read string of input from user */
	UART_sendString(g_passwordArray);
	/* send string using UART */
	checkByte = UART_receiveByte ();

	if ( checkByte == FAILED_PASSWORD )
	{
		failureCount++;
		if ( 3 == failureCount)
		{
			UART_sendByte (BUZZ);
			LCD_clearScreen();
			/* clears screen */
			LCD_displayStringCoutation ("Fail! wait 1 m");
			g_disableDefaultFlag = 1;
			TIMER1_setCallback ( APP_BUZZ_CONTROL ) ;
			TIMER1_init ( &g_config_buzzer );
			failureCount = 0;
		}
		else
		{
			LCD_clearScreen();
			LCD_displayStringCoutation("FAILED!");
			_delay_ms(HUMAN_EYE_VISION);
			return;
		}
	}
	else if ( checkByte == SUCCESSFUL_PASSWORD)
	{
		failureCount = 0;
		APP_setupPasswordInit();
	}
}

void APP_BUZZ_CONTROL ()
{
	static uint8 ticksCounter = 0;
	ticksCounter++;
	if ( 7 == ticksCounter )
	{
		g_disableDefaultFlag = 0;
	}
}

void APP_setupPassword ()
{
	uint8 checkByte = 0;
	UART_sendByte (SETUP_PASSWORD);
	/* inform control_ECU that we will change password */
	LCD_clearScreen();
	/* clears screen */
	LCD_displayStringCoutation ("Setup a password:");
	/* display message to guide user */
	LCD_goToRowColumn (1,0);
	/* lower cursor to second line */
	APP_readString();
	/* read string of input from user */
	UART_sendString(g_passwordArray);
	/* send string using UART */

	/* second entry of password */
	LCD_clearScreen();
	/* clears screen */
	LCD_displayStringCoutation ("Enter pass again:");
	/* display message to guide user */
	LCD_goToRowColumn (1,0);
	APP_readString();
	/* read string of input from user */
	UART_sendString(g_passwordArray);
	/* send string using UART */

	checkByte = UART_receiveByte ();

	if ( checkByte == PASSWORDS_DONT_MATCH )
	{
		LCD_clearScreen();
		LCD_displayStringCoutation("FAILED!");
		_delay_ms(HUMAN_EYE_VISION);
		APP_setupPassword();
	}
	else if ( checkByte == PASSWORDS_MATCH )
	{
		LCD_clearScreen();
		LCD_displayStringCoutation("Password changed");
		LCD_goToRowColumn (1,0);
		LCD_displayStringCoutation("successfully");
		_delay_ms(HUMAN_EYE_VISION);
	}
}

void APP_setupPasswordInit ()
{
	/* without UART_sendByte (SETUP_PASSWORD); like normal setup */
	uint8 checkByte = 0;
	/* inform control_ECU that we will change password */
	LCD_clearScreen();
	/* clears screen */
	LCD_displayStringCoutation ("Setup a password:");
	/* display message to guide user */
	LCD_goToRowColumn (1,0);
	/* lower cursor to second line */
	APP_readString();
	/* read string of input from user */
	UART_sendString(g_passwordArray);
	/* send string using UART */

	/* second entry of password */
	LCD_clearScreen();
	/* clears screen */
	LCD_displayStringCoutation ("Enter pass again:");
	/* display message to guide user */
	LCD_goToRowColumn (1,0);
	APP_readString();
	/* read string of input from user */
	UART_sendString(g_passwordArray);
	/* send string using UART */

	checkByte = UART_receiveByte ();

	if ( checkByte == PASSWORDS_DONT_MATCH )
	{
		LCD_clearScreen();
		LCD_displayStringCoutation("FAILED!");
		_delay_ms(HUMAN_EYE_VISION);
		APP_setupPassword();
	}
	else if ( checkByte == PASSWORDS_MATCH )
	{
		LCD_clearScreen();
		LCD_displayStringCoutation("Password changed");
		LCD_goToRowColumn (1,0);
		LCD_displayStringCoutation("successfully");
		_delay_ms(HUMAN_EYE_VISION);
	}
}

void APP_openDoor ()
{
	static uint8 failureCount = 0;
	uint8 checkByte = 0;
	UART_sendByte (OPEN_DOOR);
	/* inform control_ECU that we will open door */
	LCD_clearScreen();
	/* clears screen */
	LCD_displayStringCoutation ("Enter Pass:");
	/* display message to guide user */
	LCD_goToRowColumn (1,0);
	/* lower cursor to second line */
	APP_readString();
	/* read string of input from user */
	UART_sendString(g_passwordArray);
	/* send string using UART */

	checkByte = UART_receiveByte (); /* receive byte of password check */

	if (checkByte == FAILED_PASSWORD)
	{
		failureCount++;
		if ( 3 == failureCount)
		{
			UART_sendByte (BUZZ);
			LCD_clearScreen();
			/* clears screen */
			LCD_displayStringCoutation ("Fail! wait 1 m");
			g_disableDefaultFlag = 1;
			TIMER1_setCallback ( APP_BUZZ_CONTROL ) ;
			TIMER1_init ( &g_config_buzzer );
			failureCount = 0;
		}
		else
		{
			LCD_clearScreen();
			LCD_displayStringCoutation("FAILED!");
			_delay_ms(HUMAN_EYE_VISION);
			return;
		}
	}
	else if ( SUCCESSFUL_PASSWORD == checkByte )
	{
		LCD_clearScreen();
		/* clears screen */
		LCD_displayStringCoutation ("Door is opening!");
		TIMER1_setCallback (APP_openDoorLCDNotification);
		TIMER1_init (&g_config_open);
		failureCount = 0;
		g_disableDefaultFlag = 1;
	}
}

void APP_openDoorLCDNotification ()
{
	static uint8 ticks = 0;
	ticks++;
	if ( 1 == ticks)
	{
		LCD_clearScreen();
		/* clears screen */
		LCD_displayStringCoutation ("Door is open!");
	}
	else if ( 2 == ticks)
	{
		LCD_clearScreen();
		/* clears screen */
		LCD_displayStringCoutation ("Door is closing!");
	}
	else if ( 3 == ticks)
	{
		TIMER1_deinit ();
		g_disableDefaultFlag = 0;
		ticks = 0;
	}
}
void APP_deafult()
{
	_delay_ms(HUMAN_CLICK); /* to not take wrong input from previous process */
	LCD_clearScreen();
	/* clears screen of lcd */
	LCD_displayStringCoutation ("+ : Change Pass");
	LCD_goToRowColumn (1,0);
	LCD_displayStringCoutation ("- : Open Door");
	/* display default options */
	g_pressedKey = KEYPAD_getPressedKey();
	/* get pressed key from keypad */

	if ( '+' == g_pressedKey )
	{
		APP_changePassword();
		/* if + change password code */
	}
	else if ( '-' == g_pressedKey)
	{
		APP_openDoor();
		/* if - open the door */
	}
	else
	{
		LCD_clearScreen();
		LCD_displayStringCoutation ("Wrong input !");
		_delay_ms (HUMAN_EYE_VISION);
		APP_deafult();
		/* clear screen and display error message for 2 seconds the recall the APP_deafult function
		 * to get the right input
		 */
	}
}

void APP_checkOnInit()
{
	uint8 checkByte = 0;
	LCD_displayStringCoutation ("Welcome to the");
	LCD_goToRowColumn (1,0);
	LCD_displayStringCoutation ("door lock sys.");
	_delay_ms(HUMAN_EYE_VISION); /* so user can see welcome message */

	UART_sendByte (IS_PASSWORD_SETUP); /* ask control to check EEPROM */

	checkByte = UART_receiveByte (); /* receive response from control ECU */

	if ( checkByte == EEPROM_IS_CLEAR )
	{
		APP_setupPasswordInit ();
	}
}
int main ()
{
	SREG |= (1<<7); /* enable global interrupt */
	UART_init (&UART_configuration); /* initialize UART */
	LCD_init(); /* initialize LCD */

	APP_checkOnInit();
	/* setup for first time */

	for (;;)
	{
		/* checks if default routine is allowed to run or not */
		if ( 0 == g_disableDefaultFlag )
		{
			APP_deafult(); /* default behavior waiting for input from keypad */
		}
	}
}
