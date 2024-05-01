/*
 ============================================================================
 Name        : spi_private.h
 Module Name : SPI
 Author      : Ahmed Ali
 Date        : 16 Oct 2023
 Description : Private file for the AVR SPI driver
 ============================================================================
 */

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

#include "std_types.h"

/*******************************************************************************
 *                 SPI Registers type structure declarations                  *
 *******************************************************************************/

/* Bitmap structure for SPCR register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 SPR0_Bit :1; /* Register bit 0 */
		uint8 SPR1_Bit :1; /* Register bit 1 */
		uint8 CPHA_Bit :1; /* Register bit 2 */
		uint8 CPOL_Bit :1; /* Register bit 3 */
		uint8 MSTR_Bit :1; /* Register bit 4 */
		uint8 DORD_Bit :1; /* Register bit 5 */
		uint8 SPE_Bit :1; /* Register bit 6 */
		uint8 SPIE_Bit :1; /* Register bit 7 */
	} Bits;
} SPI_SPCR_Type;

/* Bitmap structure for SPSR register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 SPI2X_Bit :1; /* Register bit 0 */
		uint8 :1; /* Reserved bit 1 */
		uint8 :1; /* Reserved bit 2 */
		uint8 :1; /* Reserved bit 3 */
		uint8 :1; /* Reserved bit 4 */
		uint8 :1; /* Reserved bit 5 */
		uint8 WCOL_Bit :1; /* Register bit 6 */
		uint8 SPIF_Bit :1; /* Register bit 7 */
	} Bits;
} SPI_SPSR_Type;

/*******************************************************************************
 *                         SPI Registers Definitions                          *
 *******************************************************************************/

/* definition for SPCR registers */
#define SPCR_REG (*(volatile SPI_SPCR_Type *const)0x2D)

/* definition for SPSR registers */
#define SPSR_REG (*(volatile SPI_SPSR_Type *const)0x2E)

/* definition for SPDR registers */
#define SPDR_REG (*(volatile uint8 *const)0x2F)

#endif /* SPI_PRIVATE_H_ */
