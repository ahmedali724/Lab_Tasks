/*
 ============================================================================
 Name        : main.c
 Author      : Ahmed Ali
 Date        : 18 Feb 2024
 Description : The main functions
 ============================================================================
 */

#include "gpio.h"
#include <util/delay.h>
#include "std_types.h"
#include "common_macros.h"

uint8 counter = 0;
uint8 digit7Seg[10] =
{ 0x7E, 0x0C, 0xB6, 0x9E, 0xCC, 0xDA, 0xF8, 0x0E, 0xFE, 0xDE };

void display(uint8 num)
{
	GPIO_writePin(PORTC_ID, PIN6_ID, LOGIC_HIGH);
	GPIO_writePin(PORTC_ID, PIN7_ID, LOGIC_LOW);
	GPIO_writePort(PORTA_ID, digit7Seg[num % 10]);
	_delay_ms(3);
	GPIO_writePin(PORTC_ID, PIN7_ID, LOGIC_HIGH);
	GPIO_writePin(PORTC_ID, PIN6_ID, LOGIC_LOW);
	GPIO_writePort(PORTA_ID, digit7Seg[num / 10]);
	_delay_ms(3);
}

int main(void)
{
	GPIO_setupPinDirection(PORTC_ID, PIN6_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID, PIN7_ID, PIN_OUTPUT);
	GPIO_setupPortDirection(PORTA_ID, PORT_OUTPUT);
	GPIO_setupPinDirection(PORTD_ID, PIN2_ID, PIN_INPUT);
	GPIO_setupPinDirection(PORTD_ID, PIN3_ID, PIN_INPUT);
	GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_INPUT);
	display(0);
	while (1)
	{
		if (GPIO_readPin(PORTD_ID, PIN2_ID) == LOGIC_LOW)
		{
			_delay_ms(30);
			if (GPIO_readPin(PORTD_ID, PIN2_ID) == LOGIC_LOW)
			{
				if (counter == 99)
				{
					counter = 99;
				}
				else
				{
					counter++;
				}
				while (GPIO_readPin(PORTD_ID, PIN2_ID) == LOGIC_LOW)
					;
			}
		}
		if (GPIO_readPin(PORTD_ID, PIN3_ID) == LOGIC_LOW)
		{
			_delay_ms(30);
			if (GPIO_readPin(PORTD_ID, PIN3_ID) == LOGIC_LOW)
			{
				if (counter == 0)
				{
					counter = 0;
				}
				else
				{
					counter--;
				}
				while (GPIO_readPin(PORTD_ID, PIN3_ID) == LOGIC_LOW)
					;
			}
		}
		if (GPIO_readPin(PORTD_ID, PIN4_ID) == LOGIC_LOW)
		{
			_delay_ms(30);
			if (GPIO_readPin(PORTD_ID, PIN4_ID) == LOGIC_LOW)
			{
				counter = 0;
				while (GPIO_readPin(PORTD_ID, PIN4_ID) == LOGIC_LOW)
					;
			}
		}
		display(counter);
	}
}
