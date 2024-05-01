/*
 ============================================================================
 Name        : main_MC2.c
 Module Name :
 Author      : Ahmed Ali
 Date        : 1 May 2024
 Description :
 ============================================================================
 */

#include "uart.h"
#include "lcd.h"
#include "std_types.h"
#include <util/delay.h>

int main(void)
{
	uint8 data_received;

	UART_ConfigType UART_Config =
	{ ASYNCHRONOUS, DISABLED_PARITY, STOP_1_BIT, DATA_8_BIT, BAUD_RATE_9600 };

	LCD_init();

	UART_init(&UART_Config);

	LCD_displayString("X Value: ");
	while (1)
	{
		data_received = UART_recieveByte();

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
