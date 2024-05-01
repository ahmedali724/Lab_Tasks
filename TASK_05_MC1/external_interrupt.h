/*
 ============================================================================
 Name        : external_interrupt.h
 Module Name : EXTERNAL INTERRUPT
 Author      : Ahmed Ali
 Date        : 26 Apr 2024
 Description : Header file for the AVR EXTERNAL INTERRUPT driver
 ============================================================================
 */

#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define INT0_PORTID		PORTD_ID
#define INT0_PINID 		PIN2_ID

#define INT1_PORTID		PORTD_ID
#define INT1_PINID 		PIN3_ID

#define INT2_PORTID		PORTB_ID
#define INT2_PINID 		PIN2_ID

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	LOW_LEVEL, ANY_CHANGE, FALLING_EDGE, RISING_EDGE
} EXT_INT_ModeType;

typedef enum
{
	EXT_INT2_FALLING_EDGE, EXT_INT2_RISING_EDGE
} EXT_INT2_ModeType;

typedef struct
{
	EXT_INT_ModeType mode;
} EXT_INT0_ConfigType;

typedef struct
{
	EXT_INT_ModeType mode;
} EXT_INT1_ConfigType;

typedef struct
{
	EXT_INT2_ModeType mode;
} EXT_INT2_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize the EXT INT0 driver.
 */
void EXT_INT0_init(const EXT_INT0_ConfigType *Config_Ptr);

/*
 * Description :
 * Function to initialize the EXT INT1 driver.
 */
void EXT_INT1_init(const EXT_INT1_ConfigType *Config_Ptr);

/*
 * Description :
 * Function to initialize the EXT INT2 driver.
 */
void EXT_INT2_init(const EXT_INT2_ConfigType *Config_Ptr);

/*
 * Description :
 * Function to set the Call Back function address.
 */
void EXT_INT0_setCallBack(void (*a_ptr)(void));

/*
 * Description :
 * Function to set the Call Back function address.
 */
void EXT_INT1_setCallBack(void (*a_ptr)(void));

/*
 * Description :
 * Function to set the Call Back function address.
 */
void EXT_INT2_setCallBack(void (*a_ptr)(void));

#endif /* EXTERNAL_INTERRUPT_H_ */
