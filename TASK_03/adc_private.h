/*
 ============================================================================
 Name        : adc_private.h
 Module Name : ADC
 Author      : Ahmed Ali
 Date        : 6 Oct 2023
 Description : Private file for the AVR ADC driver
 ============================================================================
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#include "std_types.h"

/*******************************************************************************
 *                  ADC Registers type structure declarations                  *
 *******************************************************************************/

/* Bitmap structure for ADMUX register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 MUX0_Bit  :1;  /* MUX0 bit 0 */
		uint8 MUX1_Bit  :1;  /* MUX1 bit 1 */
		uint8 MUX2_Bit  :1;  /* MUX2 bit 2 */
		uint8 MUX3_Bit  :1;  /* MUX3 bit 3 */
		uint8 MUX4_Bit  :1;  /* MUX4 bit 4 */
		uint8 ADLAR_Bit :1;  /* ADLAR bit 5 */
		uint8 REFS0_Bit :1;  /* REFS0 bit 6 */
		uint8 REFS1_Bit :1;  /* REFS1 bit 7 */
	} Bits;
} ADC_ADMUX_Type;

/* Bitmap structure for ADCSRA register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 ADPS0_Bit :1;  /* MUX0 bit 0 */
		uint8 ADPS1_Bit :1;  /* MUX1 bit 1 */
		uint8 ADPS2_Bit :1;  /* MUX2 bit 2 */
		uint8 ADIE_Bit  :1;  /* MUX3 bit 3 */
		uint8 ADIF_Bit  :1;  /* MUX4 bit 4 */
		uint8 ADATE_Bit :1;  /* ADLAR bit 5 */
		uint8 ADSC_Bit  :1;  /* REFS0 bit 6 */
		uint8 ADEN_Bit  :1;  /* REFS1 bit 7 */
	} Bits;
} ADC_ADCSRA_Type;

/*******************************************************************************
 *                          ADC Registers Definitions                          *
 *******************************************************************************/

/* definition for ADMUX register */
#define ADMUX_REG  (*(volatile ADC_ADMUX_Type * const)  0x27)

/* definition for ADCSR register */
#define ADCSRA_REG (*(volatile ADC_ADCSRA_Type * const) 0x26)

/* definition for ADC Data registers */
#define ADCH_REG   (*(volatile uint8 * const)  0x25)

#define ADCL_REG   (*(volatile uint8 * const)  0x24)

#define ADC_REG    (*(volatile uint16 * const) 0x24)

#endif /* ADC_PRIVATE_H_ */
