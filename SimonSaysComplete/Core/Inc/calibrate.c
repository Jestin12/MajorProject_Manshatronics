/*
 * calibrate.c
 *
 *  Created on: 19 May 2023
 *      Author: jesti
 */

#include "stm32f3xx_hal.h"
#include "main.h"
#include "user_functions2.h"

void calibrate()
{
	while (Wnum != 0b11111111)
	{
		Wnum |= GPIOD->IDR;
		*led_register = GPIOD->IDR;
		HAL_Delay(20);
	}
}
