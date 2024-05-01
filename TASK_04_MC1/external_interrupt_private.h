/*
 ============================================================================
 Name        : external_interrupt_private.h
 Module Name : EXTERNAL INTERRUPT
 Author      : Ahmed Ali
 Date        : 26 Apr 2024
 Description : Private file for the AVR EXTERNAL INTERRUPT driver
 ============================================================================
 */

#ifndef EXTERNAL_INTERRUPT_PRIVATE_H_
#define EXTERNAL_INTERRUPT_PRIVATE_H_

#include "std_types.h"

/*******************************************************************************
 *          EXTERNAL INTERRUPT Registers type structure declarations           *
 *******************************************************************************/

/* Bitmap structure for MCUCR register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 ISC00_Bit :1; /* Register bit 0 */
		uint8 ISC01_Bit :1; /* Register bit 1 */
		uint8 ISC10_Bit :1; /* Register bit 2 */
		uint8 ISC11_Bit :1; /* Register bit 3 */
		uint8 SM0_Bit :1; /* Register bit 4 */
		uint8 SM1_Bit :1; /* Register bit 5 */
		uint8 SM2_Bit :1; /* Register bit 6 */
		uint8 SE_Bit :1; /* Register bit 7 */
	} Bits;
} EXT_INT_MCUCR_Type;

/* Bitmap structure for MCUCSR register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 PORF_Bit :1; /* Register bit 0 */
		uint8 EXTRF_Bit :1; /* Register bit 1 */
		uint8 BORF_Bit :1; /* Register bit 2 */
		uint8 WDRF_Bit :1; /* Register bit 3 */
		uint8 JTRF_Bit :1; /* Register bit 4 */
		uint8 :1; /* Reserved bit 5 */
		uint8 ISC2_Bit :1; /* Register bit 6 */
		uint8 JTD_Bit :1; /* Register bit 7 */
	} Bits;
} EXT_INT_MCUCSR_Type;

/* Bitmap structure for GICR register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 IVCE_Bit :1; /* Register bit 0 */
		uint8 IVSEL_Bit :1; /* Register bit 1 */
		uint8 :1; /* Reserved bit 2 */
		uint8 :1; /* Reserved bit 3 */
		uint8 :1; /* Reserved bit 4 */
		uint8 INT2_Bit :1; /* Register bit 5 */
		uint8 INT0_Bit :1; /* Register bit 6 */
		uint8 INT1_Bit :1; /* Register bit 7 */
	} Bits;
} EXT_INT_GICR_Type;

/* Bitmap structure for GIFR register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 :1; /* Reserved bit 0 */
		uint8 :1; /* Reserved bit 1 */
		uint8 :1; /* Reserved bit 2 */
		uint8 :1; /* Reserved bit 3 */
		uint8 :1; /* Reserved bit 4 */
		uint8 INTF2_Bit :1; /* Register bit 5 */
		uint8 INTF0_Bit :1; /* Register bit 6 */
		uint8 INTF1_Bit :1; /* Register bit 7 */
	} Bits;
} EXT_INT_GIFR_Type;

/*******************************************************************************
 *                  EXTERNAL INTERRUPT Registers Definitions                   *
 *******************************************************************************/

/* definition for MCUCR register */
#define MCUCR_REG (*(volatile EXT_INT_MCUCR_Type *const) 0x55)

/* definition for MCUCSR register */
#define MCUCSR_REG (*(volatile EXT_INT_MCUCSR_Type *const) 0x54)

/* definition for GICR register */
#define GICR_REG (*(volatile EXT_INT_GICR_Type *const) 0x5B)

/* definition for GIFR register */
#define GIFR_REG (*(volatile EXT_INT_GIFR_Type *const) 0x5A)

#endif /* EXTERNAL_INTERRUPT_PRIVATE_H_ */
