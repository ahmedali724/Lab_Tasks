/*
 ============================================================================
 Name        : spi.c
 Module Name : SPI
 Author      : Ahmed Ali
 Date        : 16 Oct 2023
 Description : Source file for the AVR SPI driver
 ============================================================================
 */

#include "spi.h"
#include "spi_private.h"
#include "gpio.h"

/*
 * Description :
 * Initialize the SPI device as Master.
 */
void SPI_initMaster(const SPI_ConfigType *config_ptr)
{
	/******** Configure SPI Master Pins *********
	 * SS(PB4)   --> Output
	 * MOSI(PB5) --> Output
	 * MISO(PB6) --> Input
	 * SCK(PB7) --> Output
	 ********************************************/
	GPIO_setupPinDirection(SPI_SS_PORT_ID, SPI_SS_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(SPI_MOSI_PORT_ID, SPI_MOSI_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(SPI_MISO_PORT_ID, SPI_MISO_PIN_ID, PIN_INPUT);
	GPIO_setupPinDirection(SPI_SCK_PORT_ID, SPI_SCK_PIN_ID, PIN_OUTPUT);

	/************************** SPCR Description **************************
	 * SPIE    = 0 Disable SPI Interrupt
	 * SPE     = 1 Enable SPI Driver
	 * MSTR    = 1 Enable Master
	 ***********************************************************************/
	SPCR_REG.Bits.SPIE_Bit = 0;
	SPCR_REG.Bits.MSTR_Bit = 1;

	/*
	 * insert the required Data Order in DORD bit of SPCR Register
	 */
	SPCR_REG.Bits.DORD_Bit = config_ptr->order;

	/*
	 * insert the required Clock Polarity in CPOL bit of SPCR Register
	 */
	SPCR_REG.Bits.CPOL_Bit = config_ptr->polarity;

	/*
	 * insert the required Clock Phase in CPHA bit of SPCR Register
	 */
	SPCR_REG.Bits.CPHA_Bit = config_ptr->phase;

	/*
	 * insert the required Clock Rate in SPR bits (SPR0 and SPR1) of SPCR Register
	 * and SPI2X bit of SPSR Register
	 */
	SPCR_REG.Byte = (SPCR_REG.Byte & 0xFC) | ((config_ptr->rate) & 0x03);

	SPSR_REG.Byte = (SPSR_REG.Byte & 0xFE) | (((config_ptr->rate) & 0x04) >> 2);

	SPCR_REG.Bits.SPE_Bit = 1;
}

/*
 * Description :
 * Initialize the SPI device as Slave.
 */
void SPI_initSlave(const SPI_ConfigType *config_ptr)
{
	/******** Configure SPI Slave Pins *********
	 * SS(PB4)   --> Input
	 * MOSI(PB5) --> Input
	 * MISO(PB6) --> Output
	 * SCK(PB7) --> Input
	 ********************************************/
	GPIO_setupPinDirection(SPI_SS_PORT_ID, SPI_SS_PIN_ID, PIN_INPUT);
	GPIO_setupPinDirection(SPI_MOSI_PORT_ID, SPI_MOSI_PIN_ID, PIN_INPUT);
	GPIO_setupPinDirection(SPI_MISO_PORT_ID, SPI_MISO_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(SPI_SCK_PORT_ID, SPI_SCK_PIN_ID, PIN_INPUT);

	/************************** SPCR Description **************************
	 * SPIE    = 0 Disable SPI Interrupt
	 * SPE     = 1 Enable SPI Driver
	 * MSTR    = 0 Enable Slave
	 ***********************************************************************/
	SPCR_REG.Bits.SPIE_Bit = 0;
	SPCR_REG.Bits.MSTR_Bit = 0;

	/*
	 * insert the required Data Order in DORD bit of SPCR Register
	 */
	SPCR_REG.Bits.DORD_Bit = config_ptr->order;

	/*
	 * insert the required Clock Polarity in CPOL bit of SPCR Register
	 */
	SPCR_REG.Bits.CPOL_Bit = config_ptr->polarity;

	/*
	 * insert the required Clock Phase in CPHA bit of SPCR Register
	 */
	SPCR_REG.Bits.CPHA_Bit = config_ptr->phase;

	/*
	 * insert the required Clock Rate in SPR bits (SPR0 and SPR1) of SPCR Register
	 * and SPI2X bit of SPSR Register
	 */
	SPCR_REG.Byte = (SPCR_REG.Byte & 0xFC) | ((config_ptr->rate) & 0x03);

	SPSR_REG.Byte = (SPSR_REG.Byte & 0xFE) | (((config_ptr->rate) & 0x04) >> 2);

	SPCR_REG.Bits.SPE_Bit = 1;
}

/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
uint8 SPI_sendReceiveByte(uint8 data)
{
	/* Initiate the communication and send data by SPI */
	SPDR_REG = data;

	/* Wait until SPI interrupt flag SPIF = 1 (data has been sent/received correctly) */
	while ((SPSR_REG.Bits.SPIF_Bit) == 0)
	{
	}

	/*
	 * Note: SPIF flag is cleared by first reading SPSR (with SPIF set) which is done in the previous step.
	 * and then accessing SPDR like the below line.
	 */
	return SPDR_REG;
}

/*
 * Description :
 * Send the required string through SPI to the other SPI device.
 */
void SPI_sendString(const uint8 *str)
{
	uint8 i = 0;
	uint8 received_data = 0;

	/* Send the whole string */
	while (str[i] != '\0')
	{
		/*
		 * received_data contains the received data from the other device.
		 * It is a dummy data variable as we just need to send the string to other device.
		 */
		received_data = SPI_sendReceiveByte(str[i]);
		i++;
	}
}

/*
 * Description :
 * Receive the required string until the '#' symbol through SPI from the other SPI device.
 */
void SPI_receiveString(uint8 *str)
{
	uint8 i = 0;

	/* Receive the first byte */
	str[i] = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);

	/* Receive the whole string until the '#' */
	while (str[i] != '#')
	{
		i++;
		str[i] = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	str[i] = '\0';
}
