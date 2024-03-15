#include "main.h"
#include "stm32f1xx_hal.h"
#include <string.h>
#include "st7735.h"
#include "fonts.h"

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;


void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_RTC_Init(void);





int main(void)
{
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_RTC_Init();

  ST7735_Init();

  	RTC_TimeTypeDef time;
    RTC_DateTypeDef date;

  	time.Hours = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1);
    time.Minutes = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR2);
    time.Seconds = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR3);

    HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);

    date.Year = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR4);
    date.Month = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR5);
    date.Date = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR6);
    date.WeekDay = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR7);

    HAL_RTC_SetDate(&hrtc, &date, RTC_FORMAT_BIN);



    uint8_t wkday = date.WeekDay;
    uint8_t month = date.Month;


    char sec_arry[2];
    char min_arry[2];
    char hrs_arry[2];

    char day_arry[10];
    char month_arry[4];
    char date_arry[2];
    char year_arry[5]={'2','0'};



  while (1)
  {
	  HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
	  HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);

	  if(month!=date.Month)
	  {
		  month=date.Month;
		  switch(month)
		  {
		  case RTC_MONTH_JANUARY:
		      strcpy(month_arry, "Jan");
		      break;

		  case RTC_MONTH_FEBRUARY:
		      strcpy(month_arry, "Feb");
		      break;

		  case RTC_MONTH_MARCH:
		      strcpy(month_arry, "Mar");
		      break;

		  case RTC_MONTH_APRIL:
		      strcpy(month_arry, "Apr");
		      break;

		  case RTC_MONTH_MAY:
		      strcpy(month_arry, "May");
		      break;

		  case RTC_MONTH_JUNE:
		      strcpy(month_arry, "Jun");
		      break;

		  case RTC_MONTH_JULY:
		      strcpy(month_arry, "Jul");
		      break;

		  case RTC_MONTH_AUGUST:
		      strcpy(month_arry, "Aug");
		      break;

		  case RTC_MONTH_SEPTEMBER:
		      strcpy(month_arry, "Sep");
		      break;

		  case RTC_MONTH_OCTOBER:
		      strcpy(month_arry, "Oct");
		      break;

		  case RTC_MONTH_NOVEMBER:
		      strcpy(month_arry, "Nov");
		      break;

		  case RTC_MONTH_DECEMBER:
		      strcpy(month_arry, "Dec");
		      break;

		  }
	  }
	  if(wkday!=date.WeekDay)
	  {
		  wkday=date.WeekDay;

		  switch(wkday)
		  {
		  	case RTC_WEEKDAY_FRIDAY:
		  	 	 	 	 	 strcpy(day_arry,"Friday");
		  	 	 	 	 	 break;

		  	case RTC_WEEKDAY_SATURDAY:
		  		 	 	 	 strcpy(day_arry,"Saturday");
		  		 	 	 	 break;

		  	case RTC_WEEKDAY_SUNDAY:
		  			  	 	 strcpy(day_arry,"Sunday");
		  			  	 	 break;

		  	case RTC_WEEKDAY_MONDAY:
		  			  	 	 strcpy(day_arry,"Monday");
		  			  	 	 break;

		  	case RTC_WEEKDAY_TUESDAY:
		  			  	 	 strcpy(day_arry,"Tuesday");
		  			  	 	 break;

		  	case RTC_WEEKDAY_WEDNESDAY:
		  			  	 	 strcpy(day_arry,"Wednesday");
		  			  	 	 break;

		  	case RTC_WEEKDAY_THURSDAY:
		  			  	 	 strcpy(day_arry,"Thursday");
		  			  	 	 break;

		  	 }
	  }
	  sec_arry[0]='0'+(time.Seconds/10);
	  sec_arry[1]='0'+(time.Seconds%10);

	  min_arry[0]='0'+(time.Minutes/10);
	  min_arry[1]='0'+(time.Minutes%10);

	  hrs_arry[0]='0'+(time.Hours/10);
	  hrs_arry[1]='0'+(time.Hours%10);

	  date_arry[0]='0'+(date.Date/10);
	  date_arry[1]='0'+(date.Date%10);

	  year_arry[2]='0'+(date.Year/10);
	  year_arry[3]='0'+(date.Year%10);
	  year_arry[4]='\0';

	  ST7735_WriteString(20, 10, "Digital Clock", Font_7x10, ST7735_BLACK, ST7735_WHITE);

	  ST7735_WriteString(20, 40, hrs_arry,Font_11x18 , ST7735_BLACK, ST7735_WHITE);
	  ST7735_WriteString(40, 40, ":",Font_11x18 , ST7735_BLACK, ST7735_WHITE);
	  ST7735_WriteString(50, 40, min_arry,Font_11x18 , ST7735_BLACK, ST7735_WHITE);
	  ST7735_WriteString(70, 40, ":",Font_11x18 , ST7735_BLACK, ST7735_WHITE);
	  ST7735_WriteString(80, 40, sec_arry,Font_11x18 , ST7735_BLACK, ST7735_WHITE);

	  ST7735_WriteString(5, 80, date_arry, Font_11x18, ST7735_BLACK, ST7735_WHITE);
	  ST7735_WriteString(35, 80, month_arry, Font_11x18, ST7735_BLACK, ST7735_WHITE);
	  ST7735_WriteString(75, 80, year_arry, Font_11x18, ST7735_BLACK, ST7735_WHITE);



	  ST7735_WriteString(20, 120,day_arry,Font_11x18 , ST7735_BLACK, ST7735_WHITE);



	  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, time.Hours);
	  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR2, time.Minutes);
	  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR3, time.Seconds);

	  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR4, date.Year);
	  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR5, date.Month);
	  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR6, date.Date);
	  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR7, date.WeekDay);

	  HAL_Delay(500);
  }

}








void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 22;
  sTime.Minutes = 30;
  sTime.Seconds = 0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_THURSDAY;
  DateToUpdate.Month = RTC_MONTH_MARCH;
  DateToUpdate.Date = 14;
  DateToUpdate.Year = 24;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

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
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB0 PB1 PB11 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
