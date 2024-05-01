/*
 ============================================================================
 Name        : main_MC1.c
 Module Name :
 Author      : Ahmed Ali
 Date        : 1 May 2024
 Description :
 ============================================================================
 */

#include "external_interrupt.h"
#include "uart.h"
#include "gpio_private.h"
#include "std_types.h"
#include <util/delay.h>

volatile uint8 x = 0x41;

void EXT_INT0_Func(void)
{
	x++;
	if (x == 0x7B)
	{
		x = 0x41;
	}
}

int main(void)
{
	SREG_REG.Bits.I_Bit = 1;

	UART_ConfigType UART_Config =
	{ ASYNCHRONOUS, DISABLED_PARITY, STOP_1_BIT, DATA_8_BIT, BAUD_RATE_9600 };

	EXT_INT0_ConfigType EXT_INT0_Conifg =
	{ FALLING_EDGE };

	EXT_INT0_init(&EXT_INT0_Conifg);
	EXT_INT0_setCallBack(EXT_INT0_Func);

	UART_init(&UART_Config);

	while (1)
	{
		UART_sendByte(x);
		_delay_ms(50);
	}
}

