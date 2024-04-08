/*
 ============================================================================
 Name        : adc.h
 Module Name : ADC
 Author      : Ahmed Ali
 Date        : 6 Oct 2023
 Description : Header file for the AVR ADC driver
 ============================================================================
 */

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	AREF = 0, AVCC = 1, INTERNAL_REFERENCE = 3
} ADC_ReferenceType;

typedef enum
{
	PRESCALER_2 = 1,
	PRESCALER_4 = 2,
	PRESCALER_8 = 3,
	PRESCALER_16 = 4,
	PRESCALER_32 = 5,
	PRESCALER_64 = 6,
	PRESCALER_128 = 7
} ADC_PrescalerType;

typedef struct
{
	ADC_ReferenceType reference;
	ADC_PrescalerType prescaler;
} ADC_ConfigType;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   5

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType *Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num);

#endif /* ADC_H_ */
