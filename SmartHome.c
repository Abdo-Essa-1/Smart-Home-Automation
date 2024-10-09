/*
 ============================================================================
 Name        : SmartHome.c
 Author      : Abdelrahman Essa
 Date        : 11/8/2024
 Description : Smart home automation
 ============================================================================
 */

/************** Includes **************/
#include "std_types.h"
#include "MCAL/gpio/gpio.h"
#include "MCAL/adc/adc.h"
#include "HAL/lcd/lcd.h"
#include "HAL/lm35_sensor/lm35_sensor.h"
#include "HAL/led/led.h"
#include "HAL/ldr/ldr.h"
#include "HAL/motor/motor.h"
#include "HAL/flame/flame.h"
#include "HAL/buzzer/buzzer.h"

int main()
{
	/********** Initializations **********/

	/* LCD Initialization */
	LCD_init();
	LCD_displayStringRowColumn(0, 3, "FAN is ");
	LCD_displayStringRowColumn(1, 0, "Temp=   LDR=   %");

	/* Initialize the LEDs */
	LEDs_init();

	/* ADC Initialization */
	ADC_ConfigType conf = {ADC_INTERNAL_2_56, ADC_PRE_128};
	ADC_Init(&conf);

	/* Motor Initialization */
	DcMotor_Init();

	/* Flame Initialization */
	FlameSensor_init();

	/* Buzzer Initialization */
	Buzzer_init();

	/* Variable to store the intensity */
	uint8 intensity = 0;

	/* Variable to store the Temperature */
	uint8 temp = 0;

	/* Variable to store the Flame Emergency */
	boolean flame = FALSE;

	/************** Program **************/
	for(;;)
	{
		/* Checking for flame emergency */
		flame = FlameSensor_getValue();
		if(flame)
		{
			/* Displaying alert and turning on the buzzer */
			LCD_clearScreen();
			LCD_displayString("Critical alert!");
			Buzzer_on();

			/* Waiting for the flame to end */
			while(flame)
			{
				flame = FlameSensor_getValue();
			}

			/* Turn the emergency state off */
			Buzzer_off();
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 3, "FAN is ");
			LCD_displayStringRowColumn(1, 0, "Temp=   LDR=   %");
		}
		/* Get the intensity value and display it in the LCD */
		intensity = LDR_getLightIntensity();
		LCD_moveCursor(1, 12);
		LCD_intgerToString(intensity);
		if(intensity < 100)
		{
			LCD_displayCharacter(' ');
		}

		/* Check the LEDs condition */
		if(intensity < 16)
		{
			/* Turn All LEDs ON */
			LED_ON(LEDR_ID);
			LED_ON(LEDG_ID);
			LED_ON(LEDB_ID);
		}
		else if(intensity < 51)
		{
			/* All 3 LEDs turn ON */
			LED_ON(LEDR_ID);
			LED_ON(LEDG_ID);
			LED_OFF(LEDB_ID);
		}
		else if(intensity < 71)
		{
			/* Only the Red LED turns ON */
			LED_ON(LEDR_ID);
			LED_OFF(LEDG_ID);
			LED_OFF(LEDB_ID);
		}
		else
		{
			/* All LEDs are turned OFF */
			LED_OFF(LEDR_ID);
			LED_OFF(LEDG_ID);
			LED_OFF(LEDB_ID);
		}

		/* Get the Temperature value and display it in the LCD */
		temp = LM35_getTemperature();
		LCD_moveCursor(1, 5);
		LCD_intgerToString(temp);
		if(temp < 100)
		{
			LCD_displayCharacter(' ');
		}

		/* Check the fan condition */
		if(temp < 25)
		{
			/* FAN OFF */
			LCD_displayStringRowColumn(0, 10, "OFF");
			DcMotor_Rotate(MOTOR_STOP, 0);
		}
		else
		{
			/* FAN ON */
			LCD_displayStringRowColumn(0, 10, "ON ");
			if(temp < 30)
			{
				/* FAN at 25% speed */
				DcMotor_Rotate(MOTOR_CW, 25);
			}
			else if(temp < 35)
			{
				/* FAN at 50% speed */
				DcMotor_Rotate(MOTOR_CW, 50);
			}
			else if(temp < 40)
			{
				/* FAN at 75% speed */
				DcMotor_Rotate(MOTOR_CW, 75);
			}
			else
			{
				/* FAN at 100% speed */
				DcMotor_Rotate(MOTOR_CW, 100);
			}
		}
	}
}
