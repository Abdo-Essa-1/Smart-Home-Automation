/*
 * adc.h
 *
 *  Created on: Sep 28, 2024
 *      Author: Abdelrahman Essa
 */

#ifndef ADC_H_
#define ADC_H_

#include "../../std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ADC_MAXIMUM_VALUE    (1023u)
#define ADC_REF_VOLT_VALUE   (2.56f)

#define ADC_INT_ON           (1u)
#define ADC_INT_OFF          (0u)
#define ADC_INT_EN           ADC_INT_OFF

/* Enum for the ADC reference voltage */
typedef enum{
	ADC_AREF, ADC_AVCC, ADC_INTERNAL_2_56 = 3
}ADC_VREF;

/* Enum for the ADC Pre-scaler */
typedef enum{
	ADC_PRE_2 = 1, ADC_PRE_4, ADC_PRE_8, ADC_PRE_16, ADC_PRE_32, ADC_PRE_64, ADC_PRE_128
}ADC_PRE;

/* Data type for the ADC Configurations */
typedef struct{
	ADC_VREF VoltRef;
	ADC_PRE Prescaler;
}ADC_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function to Initialize the ADC
 * Input: Constant pointer to ADC Configurations
 * Output: void
 */
void ADC_Init(const ADC_ConfigType* ADC_Configurations);

/*
 * Description :
 * Function to get the ADC reading
 * Input: Channel ID
 * Output: ADC Reading (uint16)
 */
uint16 ADC_ReadChannel(uint8 Ch_Num);

#endif /* ADC_H_ */
