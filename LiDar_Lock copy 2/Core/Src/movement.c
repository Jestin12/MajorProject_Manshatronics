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

float v[2] = {0, 0};

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
