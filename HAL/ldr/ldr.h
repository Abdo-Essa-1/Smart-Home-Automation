/*
 * ldr.h
 *
 *  Created on: Oct 8, 2024
 *      Author: Essa
 */

#ifndef LDR_H_
#define LDR_H_

#include "../../std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define LDR_SENSOR_CHANNEL_ID               0
#define LDR_SENSOR_MAX_VOLT_VALUE           (2.56f)
#define LDR_SENSOR_MAX_LIGHT_INTENSITY      (100u)

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function to get the LDR Intensity
 * Input: void
 * Output: Intensity (uint8)
 */
uint8 LDR_getLightIntensity(void);

#endif /* LDR_H_ */
