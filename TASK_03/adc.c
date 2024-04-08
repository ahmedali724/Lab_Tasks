/*
 ============================================================================
 Name        : adc.c
 Module Name : ADC
 Author      : Ahmed Ali
 Date        : 6 Oct 2023
 Description : Source file for the AVR ADC driver
 ============================================================================
 */

#include "adc.h"
#include "adc_private.h"

void ADC_init(const ADC_ConfigType *Config_Ptr)
{
	/*
	 * insert the required reference voltage in the last two bits (REFS0 and REFS1)
	 * of ADMUX Register
	 */
	ADMUX_REG.Byte = (ADMUX_REG.Byte & 0x3F) | ((Config_Ptr->reference) << 6);

	/* ADMUX Register Bits Description:
	 * REFS1:0 = the reference voltage inserted has been inserted in previous step
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX_REG.Byte &= 0xC0;

	/*
	 * insert the required prescaler in the first three bits (ADPS0, ADPS1 and ADPS2)
	 * of ADCSRA Register
	 */
	ADCSRA_REG.Byte = (ADCSRA_REG.Byte & 0xF8) | (Config_Ptr->prescaler);

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = the prescaler has been inserted in previous step and ADC must operate in range 50-200Khz
	 */
	ADCSRA_REG.Bits.ADEN_Bit = 1;
	ADCSRA_REG.Bits.ADIE_Bit = 0;
	ADCSRA_REG.Bits.ADATE_Bit = 0;
}

uint16 ADC_readChannel(uint8 channel_num)
{
	/* Choose the correct channel by setting the channel number in MUX4:0 bits */
	ADMUX_REG.Byte = (ADMUX_REG.Byte & 0xE0) | (channel_num & 0x07);

	/* Start conversion write '1' to ADSC */
	ADCSRA_REG.Bits.ADSC_Bit = 1;

	/* Wait for conversion to complete, ADIF becomes '1' */
	while (ADCSRA_REG.Bits.ADIF_Bit == 0)
		;
	/* Clear ADIF by write '1' to it */
	ADCSRA_REG.Bits.ADIF_Bit = 1;

	/* Read the digital value from the data register */
	return ADC_REG;
}
