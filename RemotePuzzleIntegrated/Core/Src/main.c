/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "liquidcrystal_I2c.h"
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

PCD_HandleTypeDef hpcd_USB_FS;

/* USER CODE BEGIN PV */
uint32_t tempCode;
uint8_t bitIndex;
uint8_t cmd;
uint8_t cmdli;
uint32_t code;

uint8_t wor_cord[2] = {10, 10};		//the working coordinate array, used to input and compare
uint8_t cord1[2] = {1, 6};			//one of the coordinates that the magnet will be under
uint8_t cord2[2] = {2, 3};
uint8_t cord3[2] = {6, 4};

uint8_t completion[3] = {0,0,0};	//Array to keep track of which coordinates have been identified

uint8_t input;

uint8_t *led_register = ((uint8_t*)&(GPIOE->ODR)) + 1;
uint8_t *integ_register = ((uint8_t*)&(GPIOD->ODR));
uint8_t mask = 0b0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_USB_PCD_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
void initialise_board();

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USB_PCD_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HD44780_Init(2);


	RCC->AHBENR |= RCC_AHBENR_GPIOEEN | RCC_AHBENR_GPIODEN;
	initialise_board();

	HAL_TIM_Base_Start(&htim2);
	__HAL_TIM_SET_COUNTER(&htim2, 0);

  // Lcd_PortType ports[] = { D4_GPIO_Port, D5_GPIO_Port, D6_GPIO_Port, D7_GPIO_Port };
  Lcd_PortType ports[] = { GPIOB, GPIOB, GPIOB, GPIOB };
  // Lcd_PinType pins[] = {D4_Pin, D5_Pin, D6_Pin, D7_Pin};
  Lcd_PinType pins[] = {GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13};
  Lcd_HandleTypeDef lcd;
  // Lcd_create(ports, pins, RS_GPIO_Port, RS_Pin, EN_GPIO_Port, EN_Pin, LCD_4_BIT_MODE);
  lcd = Lcd_create(ports, pins, GPIOB, GPIO_PIN_15, GPIOB, GPIO_PIN_14, LCD_4_BIT_MODE);

  char lcd_num[10];


  HD44780_Init(2);
  HD44780_Clear();


//  Lcd_cursor(&lcd, 0, 1);
  HD44780_SetCursor(1,0);
//  Lcd_string(&lcd, "Code Input");
  HD44780_PrintStr("Code Input");

//  Lcd_cursor(&lcd, 1, 3);
  HD44780_SetCursor(3,1);
//  Lcd_string(&lcd, "Starting");
  HD44780_PrintStr("Starting");

  HAL_Delay(2000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  for (int i = 0; i < 2; i++)
	  {
//		  Lcd_clear(&lcd);
		  HD44780_Clear();

//		  Lcd_cursor(&lcd, 0, 0);
		  HD44780_SetCursor(0,0);

//		  Lcd_string(&lcd, "Press CH to ");
		  HD44780_PrintStr("Press CH to ");

//		  Lcd_cursor(&lcd, 1, 0);
		  HD44780_SetCursor(0, 0);

//		  Lcd_string(&lcd, "input");
		  HD44780_PrintStr("input");


		  while(code != 16736925){} // "CH"

//		  Lcd_clear(&lcd);
		  HD44780_Clear();

//		  Lcd_cursor(&lcd, 0, 1);
		  HD44780_SetCursor(1, 0);

//		  Lcd_string(&lcd, "Awaiting input");
		  HD44780_PrintStr("Awaiting input");


//		  Lcd_cursor(&lcd, 0, 15);
		  HD44780_SetCursor(15, 0);

//		  Lcd_int(&lcd, i + 1);
		   sprintf(lcd_num, "%d", i +1);
		   HD44780_PrintStr(lcd_num);


		  while(code == 16736925){} // waits for the first input
//		  Lcd_clear(&lcd);
		  HD44780_Clear();


//		  Lcd_cursor(&lcd, 0, 15);	//shows which number in the code your inputting
		  HD44780_SetCursor(15, 0);

//		  Lcd_int(&lcd, i + 1);
		   sprintf(lcd_num, "%d", i +1);
		   HD44780_PrintStr(lcd_num);

//		  Lcd_cursor(&lcd, 0, 0);
		  HD44780_SetCursor(0,0);

//		  Lcd_string(&lcd, "Received!");
		  HD44780_PrintStr("Received");


//		  Lcd_cursor(&lcd, 1, 3);
		  HD44780_SetCursor(3, 1);

//		  Lcd_string(&lcd, "Input: ");
		  HD44780_PrintStr("Input");

//		  Lcd_cursor(&lcd, 1, 10);
		  HD44780_SetCursor(10, 1);

//		  Lcd_int(&lcd, input);		//shows which number is passed as an input
		   sprintf(lcd_num, "%d", input);
		   HD44780_PrintStr(lcd_num);

		  wor_cord[i] = input;

		  HAL_Delay(2000);
	  }

//	  Lcd_clear(&lcd);
	  HD44780_Clear();

//	  Lcd_cursor(&lcd, 0, 1);
	  HD44780_SetCursor(1, 0);

//	  Lcd_string(&lcd, "Co-ord received:   ");
	  HD44780_PrintStr("Co-ord received:   ");


	  int j = 1;
	  for (int i = 0; i < 2; i++)
	  {
//		  Lcd_cursor(&lcd, 1, j);
		  HD44780_SetCursor(j, 1);

//		  Lcd_int(&lcd, wor_cord[i]);
		   sprintf(lcd_num, "%d", wor_cord[i]);
		   HD44780_PrintStr(lcd_num);
		  j += 2;
	  }
//	  Lcd_cursor(&lcd, 1, 2);
	  HD44780_SetCursor(2, 1);

//	  Lcd_string(&lcd, ",");
	  HD44780_PrintStr(",");


	  while(code != 16736925){} // "CH"


//	  uint8_t cord1[2] = {1, 6};			//one of the coordinates that the magnet will be under
//	  uint8_t cord2[2] = {2, 3};
//	  uint8_t cord3[2] = {6, 4};


	  if (compare(wor_cord, cord1) == 1)
	  {
		  *led_register |= 0b00000001 << 0;
		  mask |= 0b00000001 << 0;
	  }
	  else if (compare(wor_cord, cord2) == 1)
	  {
		  *led_register |= 0b00000001 << 1;
		  mask |= 0b00000001 << 1;
	  }
	  else if (compare(wor_cord, cord3) == 1)
	  {
		  *led_register |= 0b00000001 << 2;
		  mask |= 0b00000001 << 2;
	  }
	  else
	  {

	  }
	  if (mask == 0b00000111)
	  {
		  HD44780_Clear();
		  HD44780_SetCursor(0,1);
		  HD44780_PrintStr("Write PD1 HIGH");
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, 1);
		  break;
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_TIM1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  PeriphClkInit.USBClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x0000020B;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_4BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 71;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 71;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USB Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_PCD_Init(void)
{

  /* USER CODE BEGIN USB_Init 0 */

  /* USER CODE END USB_Init 0 */

  /* USER CODE BEGIN USB_Init 1 */

  /* USER CODE END USB_Init 1 */
  hpcd_USB_FS.Instance = USB;
  hpcd_USB_FS.Init.dev_endpoints = 8;
  hpcd_USB_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_FS.Init.battery_charging_enable = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_Init 2 */

  /* USER CODE END USB_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin|LD4_Pin|LD3_Pin|LD5_Pin
                          |LD7_Pin|LD9_Pin|LD10_Pin|LD8_Pin
                          |LD6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pins : DRDY_Pin MEMS_INT3_Pin MEMS_INT4_Pin MEMS_INT1_Pin
                           MEMS_INT2_Pin */
  GPIO_InitStruct.Pin = DRDY_Pin|MEMS_INT3_Pin|MEMS_INT4_Pin|MEMS_INT1_Pin
                          |MEMS_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : CS_I2C_SPI_Pin LD4_Pin LD3_Pin LD5_Pin
                           LD7_Pin LD9_Pin LD10_Pin LD8_Pin
                           LD6_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin|LD4_Pin|LD3_Pin|LD5_Pin
                          |LD7_Pin|LD9_Pin|LD10_Pin|LD8_Pin
                          |LD6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB11 PB12 PB13
                           PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PD1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == GPIO_PIN_9)
  {
    if (__HAL_TIM_GET_COUNTER(&htim2) > 8000)
    {
      tempCode = 0;
      bitIndex = 0;
    }
    else if (__HAL_TIM_GET_COUNTER(&htim2) > 1700)
    {
      tempCode |= (1UL << (31-bitIndex));   // write 1
      bitIndex++;
    }
    else if (__HAL_TIM_GET_COUNTER(&htim2) > 1000)
    {
      tempCode &= ~(1UL << (31-bitIndex));  // write 0
      bitIndex++;
    }
    if(bitIndex == 32)
    {
      cmdli = ~tempCode; // Logical inverted last 8 bits
      cmd = tempCode >> 8; // Second last 8 bits
      if(cmdli == cmd) // Check for errors
      {
        code = tempCode; // If no bit errors
        // Do your main work HERE

        switch (code)
        {
          case (16753245):
//            SSD1306_Puts ("CH-", &Font_16x26, 1);
            break;

          case (16736925):
//            SSD1306_Puts ("CH", &Font_16x26, 1);
            break;

          case (16769565):
//            SSD1306_Puts ("CH+", &Font_16x26, 1);
            break;

          case (16720605):
//            SSD1306_Puts ("|<<", &Font_16x26, 1);
            break;

          case (16712445):
//            SSD1306_Puts (">>|", &Font_16x26, 1);
            break;

          case (16761405):
//            SSD1306_Puts (">||", &Font_16x26, 1);
            break;

          case (16769055):
//            SSD1306_Puts ("-", &Font_16x26, 1);
            break;

          case (16754775):
//            SSD1306_Puts ("+", &Font_16x26, 1);
            break;

          case (16748655):
//            SSD1306_Puts ("EQ", &Font_16x26, 1);
            break;

          case (16738455):
//            SSD1306_Puts ("0", &Font_16x26, 1);
            break;

          case (16750695):
//            SSD1306_Puts ("100+", &Font_16x26, 1);
            break;

          case (16756815):
//            SSD1306_Puts ("200+", &Font_16x26, 1);
            break;

          case (16724175):
//            SSD1306_Puts ("1", &Font_16x26, 1);
			input = 1;
            break;

          case (16718055):
//            SSD1306_Puts ("2", &Font_16x26, 1);
			input = 2;
            break;

          case (16743045):
//            SSD1306_Puts ("3", &Font_16x26, 1);
			input = 3;
            break;

          case (16716015):
//            SSD1306_Puts ("4", &Font_16x26, 1);
			input = 4;
            break;

          case (16726215):
//            SSD1306_Puts ("5", &Font_16x26, 1);
			input = 5;
            break;

          case (16734885):
//            SSD1306_Puts ("6", &Font_16x26, 1);
			input = 6;
            break;

          case (16728765):
//            SSD1306_Puts ("7", &Font_16x26, 1);
			input = 7;
            break;

          case (16730805):
//            SSD1306_Puts ("8", &Font_16x26, 1);
			input = 8;
            break;

          case (16732845):
//            SSD1306_Puts ("9", &Font_16x26, 1);
			input = 9;
            break;

          default :
            break;
        }
      }
    bitIndex = 0;
    }
  __HAL_TIM_SET_COUNTER(&htim2, 0);
  }
}

int compare(uint8_t wor_cord[2], uint8_t comp_cord[2])
{
	int x;
	for (x = 0; x < 2; x++) {
		if (wor_cord[x] != comp_cord[x])
		{
			return 0;	//if not the same coordinate
		}
	}
	return 1;		//if the same coordinate
}

void initialise_board() {
	// get a pointer to the second half word of the MODER register (for outputs pe8-15)
	uint16_t *led_output_registers = ((uint16_t *)&(GPIOE->MODER)) + 1;
	*led_output_registers = 0x5555;
	uint16_t *intgration_registers = ((uint16_t *)&(GPIOD->MODER));
	*intgration_registers = 0x5555;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
