/*
 ============================================================================
 Name        : main.c
 Author      : Ahmed Ali
 Date        : 8 Apr 2024
 Description : The main function
 ============================================================================
 */

#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"
#include "adc.h"
#include "common_macros.h"

volatile uint16 adcValue = 0;

int main(void)
{
	uint8 i = 0, direction = 0;
	ADC_ConfigType ADC_config =
	{ AVCC, PRESCALER_32 };
	SET_BIT(MCUCR, ISC01);
	SET_BIT(GICR, INT0);
	CLEAR_BIT(DDRD, PD2);
	/* Configurations and Initialization */
	LCD_init();
	ADC_init(&ADC_config);
	SREG |= (1 << 7);
	while (1)
	{
		LCD_clearScreen();
		LCD_moveCursor(0, i);
		LCD_displayString("Hello");
		_delay_ms(1000);
		if (direction == 0)
		{
			i++;
		}
		else
		{
			i--;
		}
		if (i == 5)
		{
			direction = 1;
		}
		if (i == 0)
		{
			direction = 0;
		}
	}
}

ISR(INT0_vect)
{
	adcValue = ADC_readChannel(0);
	LCD_clearScreen();
	LCD_displayString("ADC READ = ");
	LCD_intgerToString(adcValue);
	_delay_ms(2000);
}
