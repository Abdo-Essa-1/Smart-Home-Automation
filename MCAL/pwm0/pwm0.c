/*
 * pwm0.c
 *
 *  Created on: Oct 12, 2023
 *      Author: Ahmed Tarek
 */


#include <avr\io.h>
#include "pwm0.h"


/*
 * Description:
 * Generate a PWM signal with frequency 60Hz
 * Timer0 will be used with pre-scaler F_CPU/1024
 * F_PWM=(F_CPU)/(256*N) = (16*10^6)/(256*1024) = 60Hz
 * Duty Cycle can be changed by updating the value
 * in The Compare Register
 */
void PWM_Timer0_Init(unsigned char set_duty_cycle)
{

	TCNT0 = 0; //Set Timer Initial value


	uint8 duty = (uint8)(((float32) set_duty_cycle / 100) * 255);

	OCR0  = (uint8)duty; // Set Compare Value

	DDRB  |= (1<<PB3); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00) | (1<<CS02);
}
