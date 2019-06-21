/******************************************************************************
 *
 *	File Name: control.c
 *
 * 	Description:
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: May 16, 2019
 *
 *******************************************************************************/

#include "includes/externalEEPROM.h"
#include "includes/uart.h"
#include "includes/lcd.h"
#include "includes/DCmotor.h"
#include "includes/timer1.h"
#include "includes/buzzer.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void APP_displayStringLCD(uint8 *baseArray);
void APP_openDoor();
void APP_changePassword ();
void APP_setupPassword();
void APP_openDoorControl ();
void APP_BUZZ();
void APP_BUZZ_CONTROL ();

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define MAXIMUM_PASSWORD_LENGTH 		16
//#define PASSWORD_LENGTH 5 /* temporary */

#define CHANGE_PASSWORD 		0
#define OPEN_DOOR				1
#define SETUP_PASSWORD 			2
#define IS_PASSWORD_SETUP 		3
#define EEPROM_IS_CLEAR 		4
#define EEPROM_IS_SETUP 		5
#define FAILED_PASSWORD 		6
#define SUCCESSFUL_PASSWORD 	7
#define PASSWORDS_DONT_MATCH 	8
#define PASSWORDS_MATCH 		9
#define BUZZ					10
#define STRING_TERMINATOR		'\0'

#define EEPROM_BASE_ADDRESS_PASSWORD 	0x0311
#define EEPROM_DELAY_WRITE 				10



/*******************************************************************************
 *                      Variable declarations                                  *
 *******************************************************************************/
TIMER1_config g_config_open = { F_CPU_256, OVERFLOW, CHANNEL_A, 0};
TIMER1_config g_config_buzzer = { F_CPU_1024, OVERFLOW, CHANNEL_A, 0};
uint8 g_passwordArray[MAXIMUM_PASSWORD_LENGTH] = {0};
uint8 g_requiredOperation = 0;

uint8 g_receivedByteHMI;
UART_config UART_configuration = { DOUBLE };

/*******************************************************************************
*			Functions Definitions
 *******************************************************************************/
void APP_BUZZ()
{
	BUZZER_init ();
	TIMER1_setCallback ( APP_BUZZ_CONTROL ) ;
	TIMER1_init ( &g_config_buzzer );
}

void APP_BUZZ_CONTROL ()
{
	static uint8 ticksCounter = 0;
	ticksCounter++;
	if ( 7 == ticksCounter )
	{
		BUZZER_deinit();
	}
}

void APP_openDoor()
{
	uint8 i = 0;
	uint8 readPassword[MAXIMUM_PASSWORD_LENGTH] = {0};
	LCD_clearScreen();
	LCD_displayStringCoutation ("Opening door");
	LCD_goToRowColumn (1,0);
	UART_receiveString (g_passwordArray);
	APP_displayStringLCD (g_passwordArray);

	/* read old password from EEPROM */
	do
	{
		EEPROM_readByte ( ( i ) , ( readPassword + i ) ) ;
		i++;
	} while ( 0xFF != *(readPassword + i - 1) );

	*(readPassword + i - 1) = '\0'; /* put terminator */

	/* compare old password with received password */
	i = 0; /* reset counter */
	while ( '\0' != ( *( g_passwordArray + i ) ) )
	{
		if ( *( readPassword + i ) != *( g_passwordArray + i) )
		{
			UART_sendByte ( FAILED_PASSWORD );
			return;
		}
		i++;
	}

	UART_sendByte ( SUCCESSFUL_PASSWORD ); /* no failures happen send that password is ok */


	/* open door */
	DC_MOTOR_rotateClockwise(MOTOR_HALF_SPEED);
	TIMER1_setCallback (APP_openDoorControl);
	TIMER1_init (&g_config_open);
}
void APP_openDoorControl ()
{
	static uint8 ticks = 0;
	ticks++;
	if ( 1 == ticks)
	{
		/* leave door open 15 seconds */
			DC_MOTOR_stop();
	}
	else if ( 2 == ticks)
	{
		/* close door */
		DC_MOTOR_rotateAntiClockwise(MOTOR_HALF_SPEED);
	}
	else if ( 3 == ticks)
	{
		TIMER1_deinit ();
		/* stop motor */
		DC_MOTOR_stop();
		ticks = 0;
	}
}
void APP_changePassword ()
{
	uint8 i = 0;
	uint8 readPassword[MAXIMUM_PASSWORD_LENGTH] = {0};
	LCD_clearScreen();
	LCD_displayStringCoutation ("Changing password");
	LCD_goToRowColumn (1,0);
	UART_receiveString (g_passwordArray);
	APP_displayStringLCD (g_passwordArray);

	/* read old password from EEPROM */
	i = 0; /* zero the counter */
	do
	{
		EEPROM_readByte ( ( i ) , ( readPassword + i ) ) ;
		i++;
	} while ( *(readPassword -1) != STRING_TERMINATOR  );
	/* compare old password with received password */
	for ( i = 0; i < PASSWORD_LENGTH; i++)
	{
		if ( *( readPassword + i ) != *( g_passwordArray + i) )
		{
			UART_sendByte ( FAILED_PASSWORD );
			return;
		}
	}
	UART_sendByte ( SUCCESSFUL_PASSWORD );
	APP_setupPassword();
}

void APP_setupPassword()
{
	uint8 passwordArraySecond[PASSWORD_LENGTH + 1] = {0};
	uint8 i = 0;
	LCD_clearScreen();
	LCD_displayStringCoutation ("Setup password");
	UART_receiveString (g_passwordArray);
	LCD_clearScreen();
	APP_displayStringLCD (g_passwordArray);

	UART_receiveString (passwordArraySecond);
	LCD_goToRowColumn(1,0);
	APP_displayStringLCD(passwordArraySecond);

	/* check if 2 passwords don't match */
	for (i = 0; i < PASSWORD_LENGTH; i++)
	{
		if ( *(passwordArraySecond + i) != *(g_passwordArray + i) )
		{
			UART_sendByte ( PASSWORDS_DONT_MATCH );
			return;
		}
	}
	/* if they have are the same send SUCCESS */
	UART_sendByte ( PASSWORDS_MATCH );

	/* save password in EEPROM */
	for ( i = 0; i < PASSWORD_LENGTH; i++)
	{
		EEPROM_writeByte ( ( i ) , *( g_passwordArray + i ) ) ;
		_delay_ms(EEPROM_DELAY_WRITE);
	}
}


void APP_displayStringLCD(uint8 *baseArray)
{
	uint8 i = 0;
	while ( '\0' != *( baseArray + i) )
	{
		if ( (*(baseArray + i) >= 0) && (*(baseArray + i) <= 9) )
		{
			LCD_integerToString ( *(baseArray + i) );
		}
		else
		{
			LCD_displayCharacter ( *(baseArray + i) );
		}
		i++;
	}
}
void APP_EEPROM_check()
{
	uint8 i = 0;
	uint8 readPassword[PASSWORD_LENGTH + 1] = {0};

	for ( i = 0; i < PASSWORD_LENGTH; i++)
	{
		EEPROM_readByte ( ( i ) , ( readPassword + i ) ) ;
	}
	APP_displayStringLCD(readPassword);
	_delay_ms(2000);

	for ( i = 0; i < PASSWORD_LENGTH; i++)
	{
		if ( *( readPassword + i ) != 0xFF )
		{
			UART_sendByte ( EEPROM_IS_SETUP ); /* tell the hmi that the password is setup */
			return;
		}
	}
	UART_sendByte ( EEPROM_IS_CLEAR ); /* tell the hmi that there's no password */
	APP_setupPassword(); /* call function to setup password */
}
int main ()
{
	SREG |= (1<<7); /* enable global interrupt */
	UART_init (&UART_configuration);
	/* initialize UART */

	LCD_init();
	/* initialize LCD */

	EEPROM_init();
	/* initialize EEPROM */

	DC_MOTOR_init ();
	/* initialize motor */

	for(;;)
	{
		g_requiredOperation = UART_receiveByte();
		/* receive the required operation from HMI */

		/* compare to know which operation to do */
		switch ( g_requiredOperation )
		{
		case	IS_PASSWORD_SETUP :
			APP_EEPROM_check();
			break;
		case	SETUP_PASSWORD :
			APP_setupPassword();
			break;
		case	CHANGE_PASSWORD :
			APP_changePassword();
			break;
		case	OPEN_DOOR :
			APP_openDoor();
			break;
		case	BUZZ :
			APP_BUZZ();
			break;
		}
	}
}
