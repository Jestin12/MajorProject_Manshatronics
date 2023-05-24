/*
 * lock2.c
 *
 *  Created on: May 23, 2023
 *      Author: neelbagayatkar
 */
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
//uint8_t string_to_send[100] = "This is a string !\r\n";

//void lock2()
//{
//	srand(time(NULL));
//
//    // Generate a random value within the range [min, max]
//    int distance1 = 2000;
//
//    sprintf(string_to_send,"%u,%u\r\n",distance1,last_period);
//	SerialOutputString(string_to_send, &USART1_PORT);
//
//	const uint32_t time = TIM3->CNT;
//
//	while (last_period >= (distance1 - 250) && last_period <= (distance1 + 250))
//	    {
//
//			uint32_t delayCounts = 3000; // Assuming timer counts at 1 kHz
//			uint32_t targetCount = time + delayCounts;
//
//	//	    sprintf(string_to_send,"%u,%u\r\n",TIM3->CNT,targetCount);
//	//		SerialOutputString(string_to_send, &USART1_PORT);
//
//			if (targetCount > TIM3->ARR +1)
//			{
//				targetCount = targetCount - (TIM3->ARR+1.5);
//			}
//		    sprintf(string_to_send,"%u,%u\r\n",TIM3->CNT,targetCount);
//			SerialOutputString(string_to_send, &USART1_PORT);
//
//			if(TIM3->CNT != targetCount)
//			{
//				// Your code here, or do nothing
//			}
//			else
//			{
//				while(1)
//				{
//					movement(v, 96, 135);
//				}
//			}
//	//		sprintf(string_to_send,"%u,%u\r\n",TIM3->CNT,last_period);
//	//		SerialOutputString(string_to_send, &USART1_PORT);
//	    }
//
//}
