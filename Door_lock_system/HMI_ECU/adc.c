/******************************************************************************
 *
 * 	Module: ADC
 *
 *	File Name: adc.c
 *
 * 	Description: source file for ADC driver
 *
 * 	Author: Mahmoud Saad
 *
 *	Created on: Apr 29, 2019
 *
 *******************************************************************************/


#include "includes/adc.h"

/*******************************************************************************
*			Functions Definitions
 *******************************************************************************/
#ifdef ADC_INTERRUPT

/* in case ADC_INTERRUPT is defined,
 * define functions to enable it with interrupts */

volatile uint16 g_ADC_value = 0;

/**********************************************************************************************
 * 	Function name: ISR(ADC_vect)
 *
 * 	Brief: interrupt function for ADC
 *
 * 	Details: when the ISR is fired this function takes the value of ADC register and puts it in
 * 	ADC_value variable
 *
 * 	Arguments:
 * 		-none
 *
 * 	Return:
 * 		-none
 **********************************************************************************************/
ISR(ADC_vect)
{
	g_ADC_value = ADC;
}

/**********************************************************************************************
 * 	Function name: initializes the ADC in case it works with interrupts
 *
 * 	Brief: initialize ADC to work with interrupts
 *
 * 	Details:
 *
 * 	Arguments:
 * 		-none
 *
 * 	Return:
 * 		-none
 **********************************************************************************************/
void ADC_init(void)
{
	ADMUX = 0;
	/* REFS1:0 = 0 internal ref Vref turned off
	 * ADLAR = 0 the result of conversion is right adjusted
	 */
	ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0) | (1<<ADIE);
	/* ADEN = 1 ADC enable
	 * ADPS1:0 = 11 (set the ADPS2:0 011 to get a division factor of 8 for
	 * prescaler selection bits
	 * ADIE = 1 enables ADC interrupt
	 */
}

/**********************************************************************************************
 * 	Function name: ADC_readChannel_int
 *
 * 	Brief: initializes a read channel request to the ADC
 *
 * 	Details: masks the channel number then puts it in the ADMUX register then
 * 	initializes a read request
 *
 * 	Arguments:
 * 		-channel
 *
 * 	Return:
 * 		-none
 **********************************************************************************************/
void ADC_readChannel_int (uint8 channel)
{
	channel &= 0x07;
	/* get only the first 3 bits of the address and mask the rest*/

	ADMUX &= 0xE0;
	/* clear the last 5 bits of the ADMUX register */

	ADMUX = ADMUX | channel;
	/* put channel number inside ADMUX register */

	SET_BIT(ADCSRA,ADSC);
	/* ADSC = 1 tells ADC start converstion */
}


#else

/* in case ADC_INTERRUPT is not defined,
 * define functions to enable it with polling */


/**********************************************************************************************
 * 	Function name: initializes the ADC in case it works with interrupts
 *
 * 	Brief: initialize ADC to work with polling
 *
 * 	Details:
 *
 * 	Arguments:
 * 		-none
 *
 * 	Return:
 * 		-none
 **********************************************************************************************/

void ADC_init(void)
{
	ADMUX = 0;
	/* REFS1:0 = 0 internal ref Vref turned off
	 * ADLAR = 0 the result of conversion is right adjusted
	 */
	ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);
	/* ADEN = 1 ADC enable
	 * ADPS1:0 = 11 (set the ADPS2:0 011 to get a division factor of 8 for
	 * prescaler selection bits
	 */
}

/**********************************************************************************************
 * 	Function name: ADC_readChannel_int
 *
 * 	Brief: initializes a read channel request to the ADC
 *
 * 	Details: masks the channel number then puts it in the ADMUX register then
 * 	initializes a read request
 *
 * 	then it waits by polling on flag until the ADC finishes conversion
 * 	then clears the flag and returns the value of ADC register
 *
 * 	Arguments:
 * 		-channel
 *
 * 	Return:
 * 		-ADC value after conversion
 **********************************************************************************************/

uint16 ADC_readChannel (uint8 channel)
{
	channel &= 0x07;
	/* get only the first 3 bits of the address and mask the rest*/

	ADMUX &= 0xE0;
	/* clear the last 5 bits of the ADMUX register */

	ADMUX = ADMUX | channel;
	/* put channel number inside ADMUX register */

	SET_BIT(ADCSRA,ADSC);
	/* ADSC = 1 tells ADC start conversion */

	while (BIT_IS_CLEAR(ADCSRA,ADIF));
	/* polling until the ADC finishes conversion and sets the flag to 1 */

	SET_BIT(ADCSRA,ADIF);
	/* clear the flag by writing 1 to it */

	return ADC;
	/* return the value of the ADC register */
}
#endif
