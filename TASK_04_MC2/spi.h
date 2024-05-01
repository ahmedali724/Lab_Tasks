/*
 ============================================================================
 Name        : spi.h
 Module Name : SPI
 Author      : Ahmed Ali
 Date        : 16 Oct 2023
 Description : Header file for the AVR SPI driver
 ============================================================================
 */

#ifndef SPI_H_
#define SPI_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	RISING_FIRST, FALING_FIRST
} SPI_ClockPolarityType;

typedef enum
{
	SAMPLE_FIRST, SETUP_FIRST
} SPI_ClockPhaseType;

typedef enum
{
	N_4, N_16, N_64, N_128, N_2, N_8, N_32
} SPI_ClockRateType;

typedef enum
{
	MSB, LSB
} SPI_DataOrderType;

typedef struct
{
	SPI_ClockPolarityType polarity;
	SPI_ClockPhaseType phase;
	SPI_ClockRateType rate;
	SPI_DataOrderType order;
} SPI_ConfigType;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/*
 * Default SPI data value used in case we need to receive a byte from the other device,
 * without need to send a data to it
 */
#define SPI_DEFAULT_DATA_VALUE 0xFF

#define SPI_SS_PORT_ID		PORTB_ID
#define SPI_SS_PIN_ID		PIN4_ID

#define SPI_MOSI_PORT_ID	PORTB_ID
#define SPI_MOSI_PIN_ID		PIN5_ID

#define SPI_MISO_PORT_ID	PORTB_ID
#define SPI_MISO_PIN_ID		PIN6_ID

#define SPI_SCK_PORT_ID		PORTB_ID
#define SPI_SCK_PIN_ID		PIN7_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the SPI device as Master.
 */
void SPI_initMaster(const SPI_ConfigType *config_ptr);

/*
 * Description :
 * Initialize the SPI device as Slave.
 */
void SPI_initSlave(const SPI_ConfigType *config_ptr);

/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
uint8 SPI_sendReceiveByte(uint8 data);

/*
 * Description :
 * Send the required string through SPI to the other SPI device.
 */
void SPI_sendString(const uint8 *str);

/*
 * Description :
 * Receive the required string until the '#' symbol through SPI from the other SPI device.
 */
void SPI_receiveString(uint8 *str);

#endif /* SPI_H_ */
