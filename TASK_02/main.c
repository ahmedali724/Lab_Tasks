/*
 ============================================================================
 Name        : main.c
 Author      : Ahmed Ali
 Date        : 2 Mar 2024
 Description : The Main Function
 ============================================================================
 */

#include "lcd.h"
#include <util/delay.h>

int main(void)
{
	uint8 i = 0;
	/* Configurations and Initialization */
	LCD_init();
	while (1)
	{
		LCD_clearScreen();
		LCD_moveCursor(0, i);
		LCD_displayString("Hello");
		_delay_ms(1000);
		i++;
		if (i == 6)
		{
			i = 0;
		}
	}
}
