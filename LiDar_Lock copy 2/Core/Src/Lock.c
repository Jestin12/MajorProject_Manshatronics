#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "ptu_definitions.h"
#include "ptu_i2c.h"
#include "serial.h"

#include "math.h"

#include "timer.h"
#include "last_period.h"
#include "movement.h"
#include <time.h>
#include "lock.h"

void movement(float v[2], float yaw, float pitch);
uint8_t string_to_send[100] = "This is a string !\r\n";

void lock1(int *y)
{
	srand(time(NULL));

    // Generate a random value within the range [min, max]
    int distance = 200;


	const uint32_t time = TIM3->CNT;


    while (last_period >= (distance - 250) && last_period <= (distance + 250))
    {
    	*led_register = 0b00000010;
		uint32_t delayCounts = 3000; // Assuming timer counts at 1 kHz
		uint32_t targetCount = time + delayCounts;


		if (targetCount > TIM3->ARR +1)
		{
			targetCount = targetCount - (TIM3->ARR+1.5);
		}
	    sprintf(string_to_send,"%u,%u\r\n",TIM3->CNT,*y);
		SerialOutputString(string_to_send, &USART1_PORT);

		if(TIM3->CNT != targetCount)
		{
			// Your code here, or do nothing
		}
		else
		{

			movement(v, 120, 98);
			HAL_Delay(1000);
			*y+=1;
			break;
		}
    }
    *led_register = 0;
}

void lock2(int *y)
{
	srand(time(NULL));

    // Generate a random value within the range [min, max]
    int distance1 = 1200;

	const uint32_t time = TIM3->CNT;

	while (last_period >= (distance1 - 250) && last_period <= (distance1 + 250))
	{
		*led_register = 0b00010000;
		uint32_t delayCounts = 3000; // Assuming timer counts at 1 kHz
		uint32_t targetCount = time + delayCounts;

		if (targetCount > TIM3->ARR +1)
		{
			targetCount = targetCount - (TIM3->ARR+1.5);
		}
		sprintf(string_to_send,"%u,%u penis\r\n",TIM3->CNT,*y);
		SerialOutputString(string_to_send, &USART1_PORT);

		if(TIM3->CNT+1 != targetCount)
		{
			// Your code here, or do nothing
		}
		else
		{

			movement(v, 100, 135);
			*y+=1;
			HAL_Delay(1000);
			break;
		}
	}
	*led_register = 0;
}

void lock3(int *y)
{
	srand(time(NULL));

    // Generate a random value within the range [min, max]
    int distance2 = 2000;

	const uint32_t time = TIM3->CNT;

	while (last_period >= (distance2 - 250) && last_period <= (distance2 + 250))
	{
		*led_register = 0b01000000;
		uint32_t delayCounts = 3000; // Assuming timer counts at 1 kHz
		uint32_t targetCount = time + delayCounts;

		if (targetCount > TIM3->ARR +1)
		{
			targetCount = targetCount - (TIM3->ARR+1.5);
		}
		sprintf(string_to_send,"%u,%u,%u\r\n",TIM3->CNT,*y,last_period);
		SerialOutputString(string_to_send, &USART1_PORT);

		if(TIM3->CNT+1 != targetCount)
		{
			// Your code here, or do nothing
		}
		else
		{
			*led_register = 0;
			movement(v, 96, 98);
			*y+=1;
			HAL_Delay(1000);
			for (int l = 0; l < 8; l++) {
			    int led_mask = 0b00000001 << ((l + 1) % 8);  // Calculate the LED mask for each iteration
			    *led_register |= led_mask;
			    HAL_Delay(500);
			}

			// Turn off LEDs one by one
			for (int l = 0; l < 8; l++) {
			    int led_mask = ~(0b00000001 << ((l + 1) % 8));  // Calculate the LED mask for each iteration
			    *led_register &= led_mask;
			    HAL_Delay(500);
			}
			break;
		}
	}
	*led_register = 0;

}


