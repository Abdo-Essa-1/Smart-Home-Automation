/*
 * flame.h
 *
 *  Created on: Oct 8, 2024
 *      Author: Essa
 */

#ifndef FLAME_H_
#define FLAME_H_

#include "../../std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define FLAME_PORTID           PORTD_ID
#define FLAME_PINID            PIN2_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function to Initialize the Flame Sensor
 * Input: void
 * Output: void
 */
void FlameSensor_init(void);

/*
 * Description :
 * Function to Reads the value from the flame sensor and returns it.
 * Input: void
 * Output: Flame value (uint8)
 */
uint8 FlameSensor_getValue(void);

#endif /* FLAME_H_ */
