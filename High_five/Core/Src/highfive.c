/*
 * highfive.c
 *
 *  Created on: May 24, 2023
 *      Author: neelbagayatkar
 */
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "ptu_definitions.h"
#include "ptu_i2c.h"
#include "serial.h"
#include "last_period.h"
#include "math.h"
#include "movement.h"
#include "highfive.h"

void movement(float v[2], float yaw, float pitch);
uint8_t string_to_send[100] = "This is a string !\r\n";

void highfive(uint32_t time,int *x)
{
	// using output compare to wait for an event to occur
	uint32_t delayCounts = 3000; // Assuming timer counts at 1 kHz
	uint32_t targetCount = time + delayCounts;
	if (targetCount > TIM3->ARR)
	{
		targetCount = targetCount - (TIM3->ARR + 0.5);// target count is manipulated to stay within the auto-reload period
	}


	//Setting led register to light up in circle in occurrence with the specific delay
	//This occurs with equal time spacing.
	int LED_time = time + (delayCounts/8)* (*x);

	if (LED_time > TIM3->ARR)
	{
		LED_time = LED_time - TIM3->ARR + 0.5; // ensuring LED_time is within the Auto-reload period
	}
	if (__HAL_TIM_GET_COUNTER(&htim3) == LED_time)
	{
		*led_register |= (0b00000001 << *x);   // Set the bit corresponding to LED x
		*x+=1;
	}


	sprintf(string_to_send,"%u,%u\r\n", __HAL_TIM_GET_COUNTER(&htim3),targetCount);
	SerialOutputString(string_to_send, &USART1_PORT);

	//IMU detects if hand has been there for 3 seconds an moves to another position
	if(__HAL_TIM_GET_COUNTER(&htim3) == targetCount)
	{
		while (1)
		{
			// Your code here, or do nothing
			movement(v, 120, 120);
			*led_register = 0;
			HAL_Delay(500);
			*led_register = 0b11111111;
			HAL_Delay(500);

		}
	}
}
