/*
 * flame.c
 *
 *  Created on: Oct 8, 2024
 *      Author: Essa
 */

#include "flame.h"
#include "../../MCAL/gpio/gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

/*
 * Description :
 * Function to Initialize the Flame Sensor
 * Input: void
 * Output: void
 */
void FlameSensor_init(void)
{
	GPIO_setupPinDirection(FLAME_PORTID, FLAME_PINID, PIN_INPUT);
}

/*
 * Description :
 * Function to Reads the value from the flame sensor and returns it.
 * Input: void
 * Output: Flame value (uint8)
 */
uint8 FlameSensor_getValue(void)
{
	return GPIO_readPin(FLAME_PORTID, FLAME_PINID);
}
