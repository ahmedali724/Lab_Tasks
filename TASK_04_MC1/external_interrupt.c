/*
 ============================================================================
 Name        : external_interrupt.c
 Module Name : EXTERNAL INTERRUPT
 Author      : Ahmed Ali
 Date        : 26 Apr 2024
 Description : Source file for the AVR EXTERNAL INTERRUPT driver
 ============================================================================
 */

#include "external_interrupt.h"
#include "external_interrupt_private.h"
#include "gpio.h"
#include <avr/interrupt.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtrExtInt0)(void) = NULL_PTR;
static volatile void (*g_callBackPtrExtInt1)(void) = NULL_PTR;
static volatile void (*g_callBackPtrExtInt2)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(INT0_vect)
{
	if (g_callBackPtrExtInt0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrExtInt0)();
	}
}

ISR(INT1_vect)
{
	if (g_callBackPtrExtInt1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrExtInt1)();
	}
}

ISR(INT2_vect)
{
	if (g_callBackPtrExtInt2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtrExtInt2)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize the EXT INT0 driver.
 */
void EXT_INT0_init(const EXT_INT0_ConfigType *Config_Ptr)
{
	/************************** MCUCR Description **************************
	 * ISC01, ISC00   	Interrupt Sense Control 0 , selected in configuration
	 ***********************************************************************/
	MCUCR_REG.Byte = (MCUCR_REG.Byte & 0xFC) | ((Config_Ptr->mode) & 0x03);

	/* Setup the INT0 pin as input */
	GPIO_setupPinDirection(INT0_PORTID, INT0_PINID, PIN_INPUT);

	/* Enable External Interrupt Request 0 */
	GICR_REG.Bits.INT0_Bit = 1;
}

/*
 * Description :
 * Function to initialize the EXT INT1 driver.
 */
void EXT_INT1_init(const EXT_INT1_ConfigType *Config_Ptr)
{
	/************************** MCUCR Description **************************
	 * ISC11, ISC10   	Interrupt Sense Control 1 , selected in configuration
	 ***********************************************************************/
	MCUCR_REG.Byte = (MCUCR_REG.Byte & 0xF3)
			| (((Config_Ptr->mode) & 0x03) << 2);

	/* Setup the INT1 pin as input */
	GPIO_setupPinDirection(INT1_PORTID, INT1_PINID, PIN_INPUT);

	/* Enable External Interrupt Request 1 */
	GICR_REG.Bits.INT1_Bit = 1;
}

/*
 * Description :
 * Function to initialize the EXT INT2 driver.
 */
void EXT_INT2_init(const EXT_INT2_ConfigType *Config_Ptr)
{
	/************************** MCUCSR Description *************************
	 * ISC2 		Interrupt Sense Control 2 , selected in configuration
	 ***********************************************************************/
	if (Config_Ptr->mode == EXT_INT2_FALLING_EDGE)
	{
		MCUCSR_REG.Bits.ISC2_Bit = 0;
	}
	else
	{
		MCUCSR_REG.Bits.ISC2_Bit = 1;
	}

	/* Setup the INT2 pin as input */
	GPIO_setupPinDirection(INT2_PORTID, INT2_PINID, PIN_INPUT);

	/* Enable External Interrupt Request 2 */
	GICR_REG.Bits.INT2_Bit = 1;
}

/*
 * Description :
 * Function to set the Call Back function address.
 */
void EXT_INT0_setCallBack(void (*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtrExtInt0 = a_ptr;
}

/*
 * Description :
 * Function to set the Call Back function address.
 */
void EXT_INT1_setCallBack(void (*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtrExtInt1 = a_ptr;
}

/*
 * Description :
 * Function to set the Call Back function address.
 */
void EXT_INT2_setCallBack(void (*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtrExtInt2 = a_ptr;
}
