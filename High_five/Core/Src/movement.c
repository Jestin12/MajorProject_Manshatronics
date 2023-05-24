/*
 * movement.c
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

void movement(float v[2], float yaw, float pitch){

	float c = 2700/180;

	if (yaw == 0){
		yaw += 1;
	}
	if (pitch == 0){
		pitch += 1;
	}
	TIM2->CCR1 = c*yaw;
	TIM2->CCR2 = c*pitch;

	v[0] = yaw;
	v[1] = pitch;

}
