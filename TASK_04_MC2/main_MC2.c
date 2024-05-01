/*
 ============================================================================
 Name        : main_MC2.c
 Module Name :
 Author      : Ahmed Ali
 Date        : 1 May 2024
 Description :
 ============================================================================
 */

#include "spi.h"
#include "lcd.h"
#include "std_types.h"
#include <util/delay.h>

int main(void)
{
	uint8 data_received;
	SPI_ConfigType SPI_Config =
	{ RISING_FIRST, SAMPLE_FIRST, N_16, MSB };

	LCD_init();

	SPI_initSlave(&SPI_Config);

	LCD_displayString("X Value: ");
	while (1)
	{
		data_received = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);

		LCD_moveCursor(0, 9);
		LCD_intgerToString(data_received);
		if (data_received < 100)
		{
			LCD_moveCursor(0, 11);
			LCD_displayCharacter(' ');
		}
		_delay_ms(50);
	}
}
