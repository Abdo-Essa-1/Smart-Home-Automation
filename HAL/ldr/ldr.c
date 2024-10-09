/*
 * ldr.c
 *
 *  Created on: Oct 8, 2024
 *      Author: Essa
 */

#include "../../MCAL/adc/adc.h"
#include "ldr.h"

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

/*
 * Description :
 * Function to get the LDR Intensity
 * Input: void
 * Output: Intensity (uint8)
 */
uint8 LDR_getLightIntensity(void)
{
	/* Reading the ADC Value from the LDR Pin */
	uint16 reading = ADC_ReadChannel(LDR_SENSOR_CHANNEL_ID);

	/* Changing the value of the reading to the percentage of the intensity */
	reading = (uint16)(((uint32)LDR_SENSOR_MAX_LIGHT_INTENSITY * reading)/(ADC_MAXIMUM_VALUE));

	return (uint8)reading;
}
