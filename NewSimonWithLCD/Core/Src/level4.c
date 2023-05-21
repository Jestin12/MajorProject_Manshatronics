/*
 * level4.c
 *
 *  Created on: May 18, 2023
 *      Author: jesti
 */
#include "stm32f3xx_hal.h"
#include "main.h"
#include "user_functions2.h"

int level4()
{
	uint8_t test = 0b00000000;
	Wnum = 0b00000000;
	*led_register = 0b0;

	//************************************************************************************
	int delay = 550;					//************************************************
	int num_levels = 9;					//************************************************
	//************************************************************************************


	for (int i = 0; i < 8; i++)		//circle of death to signal that the level has started
	{
		*led_register = 1 << i;
		HAL_Delay(200);
	}

	*led_register = 0b00000000;

	for (int i = 0; i < num_levels; i++)		//iterates seven patterns, only seven patterns need to be replicated for level 1
	{
		Wnum = 0b0;
		int pattern = rand() % 8;
		test = 1 << pattern;		//produces the bitmask that has to be replicated

		*led_register = test;	//shows the pattern to be replicated


		//***************************************************************************************
		HAL_Delay(delay);			//determines how long the pattern to be displayed will be displayed
		//***************************************************************************************


		*led_register = 0b0;

		while (Wnum == 0b0)
		{
			Wnum = GPIOD->IDR;
		}		//code waits while the input data register reads no inputs
		*led_register = Wnum;

		if ((Wnum & test) > 0)			//checks if the IDR reads an input that isn't
		{
			*led_register = 0b00001111;
			HAL_Delay(1000);
		}
		else
		{
			*led_register = 0b01100110;
			HAL_Delay(1000);
			return 0;
		}
	}

	return 1;
}
