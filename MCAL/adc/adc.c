/*
 * adc.c
 *
 *  Created on: Sep 28, 2024
 *      Author: Abdelrahman Essa
 */

#include "adc.h"
#include "../../common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h> /* For ADC ISR */
#include <util/delay.h>

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

static uint16 g_adcResult = 0;

/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/

ISR(ADC_vect)
{
	/* Read ADC Data after conversion complete */
	g_adcResult = ADC;
}

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

/*
 * Description :
 * Function to Initialize the ADC
 * Input: Constant pointer to ADC Configurations
 * Output: void
 */
void ADC_Init(const ADC_ConfigType* ADC_Configurations)
{
	/* Setting the ADC Voltage reference */
	ADMUX = ((ADC_Configurations->VoltRef) << REFS0);

	/* Setting the ADC Interrupt enable and the pre-scaler */
	ADCSRA = (ADC_Configurations->Prescaler);

	/* Checking if the ADC interrupt is enabled */
#if ADC_INT_EN == ADC_INT_ON
	SET_BIT(ADCSRA, ADIE);
#endif

	/* Enable the ADC */
	SET_BIT(ADCSRA, ADEN);
}

/*
 * Description :
 * Function to get the ADC reading
 * Input: Channel ID
 * Output: ADC Reading (uint16)
 */
uint16 ADC_ReadChannel(uint8 Ch_Num)
{
	/* Setting the Channel ID for conversion */
	ADMUX = (ADMUX & 0xF8) | (Ch_Num & 0x07);

	/* Start the conversion */
	SET_BIT(ADCSRA, ADSC);

	/* Checking if the ADC interrupt is enabled */
#if ADC_INT_EN == ADC_INT_OFF
	/* Waiting until the conversion ends */
	while(BIT_IS_CLEAR(ADCSRA, ADIF));

	/* Clear the ADC Flag */
	SET_BIT(ADCSRA, ADIF);

	/* Storing the ADC Result */
	g_adcResult = ADC;
#else
	/* Make delay for some time until g_adcResult value is updated with the ADC interrupt */
	_delay_ms(5);
#endif

	return g_adcResult;
}
