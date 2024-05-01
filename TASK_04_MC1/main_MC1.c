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
#include "spi.h"
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
	EXT_INT0_ConfigType EXT_INT0_Conifg =
	{ FALLING_EDGE };

	SPI_ConfigType SPI_Config =
	{ RISING_FIRST, SAMPLE_FIRST, N_16, MSB };

	EXT_INT0_init(&EXT_INT0_Conifg);
	EXT_INT0_setCallBack(EXT_INT0_Func);

	SPI_initMaster(&SPI_Config);

	while (1)
	{
		SPI_sendReceiveByte(x);
		_delay_ms(50);
	}
}

