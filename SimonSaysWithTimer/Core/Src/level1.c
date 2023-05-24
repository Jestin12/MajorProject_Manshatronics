/*
 * level1.c
 *
 *  Created on: May 18, 2023
 *      Author: jesti
 */
#include "stm32f3xx_hal.h"
#include "main.h"
#include "user_functions2.h"
#include "lcd.h"

int level1()
{
	// Lcd_PortType ports[] = { D4_GPIO_Port, D5_GPIO_Port, D6_GPIO_Port, D7_GPIO_Port };
	Lcd_PortType ports[] = { GPIOB, GPIOB, GPIOB, GPIOB };
	// Lcd_PinType pins[] = {D4_Pin, D5_Pin, D6_Pin, D7_Pin};
	Lcd_PinType pins[] = {GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13};
	Lcd_HandleTypeDef lcd;
	// Lcd_create(ports, pins, RS_GPIO_Port, RS_Pin, EN_GPIO_Port, EN_Pin, LCD_4_BIT_MODE);
	lcd = Lcd_create(ports, pins, GPIOB, GPIO_PIN_15, GPIOB, GPIO_PIN_14, LCD_4_BIT_MODE);

	uint8_t test = 0b00000000;
	Wnum = 0b00000000;
	*led_register = 0b0;

	//************************************************************************************
	int delay = 650;					//************************************************
	int num_levels = 7;					//************************************************
	//************************************************************************************



	for (int i = 0; i < 8; i++)		//circle of death to signal that the level has started
	{
		*led_register = 1 << i;
		HAL_Delay(200);
	}

	*led_register = 0b00000000;
	HAL_Delay(1000);

	Lcd_cursor(&lcd, 0,1);
	Lcd_string(&lcd, "Simon Says LVL1");
	Lcd_cursor(&lcd, 1,1);
	Lcd_string(&lcd, "Match Pattern");
	HAL_Delay(1000);
	Lcd_clear(&lcd);
	Lcd_cursor(&lcd, 0,1);
	Lcd_string(&lcd, "Simon Says LVL1");

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

		uint32_t targetCount = 7200;

		__HAL_TIM_SET_COUNTER(&htim4, 0);

		while (Wnum == 0b0)
		{
			uint32_t ctime = __HAL_TIM_GET_COUNTER(&htim4);
			Wnum = GPIOD->IDR;

			Lcd_cursor(&lcd, 1,5);
			Lcd_int(&lcd, ctime);

			if ( (ctime < targetCount) & (ctime > (targetCount - 100) ))
			{
				Lcd_cursor(&lcd, 1,1);
				Lcd_string(&lcd, "                 ");
				Lcd_string(&lcd, "   Timeout      ");
				HAL_Delay(1500);
				return 0;
			}
		}		//code waits while the input data register reads no inputs
		*led_register = Wnum;

		if ((Wnum & test) > 0)			//checks if the IDR reads an input that isn't
		{
			*led_register = 0b00001111;
			HAL_Delay(1000);
		}
		else
		{
			*led_register = 0b01010101;
			HAL_Delay(1000);
			*led_register = 0b0;
			return 0;
		}
	}

	return 1;
}
