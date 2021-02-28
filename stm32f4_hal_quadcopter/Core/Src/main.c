/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "icm_20948.h"
#include "dshot.h"
#include "flysky_ibus.h"
#include "pid.h"

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

/* USER CODE BEGIN PV */


// sensor variable
extern uint8_t rx_buffer[6];

uint8_t 			id_icm20948 	= 0;	// 0xEA
uint8_t 			id_ak09916 		= 0;	// 0x09

icm20948_t 			my_icm20948 	= {0, };
angle_t 			my_angle 		= {0, };

uint8_t 			my_dt			= 0;

uint32_t			period_us		= 0;


// motor variable
motors_s 			my_motors;				// dshot data frame structure
throttle_value 		my_value[4]		= {0};	// throttle of entire motors


// rc controller variable
channel 			my_channel[IBUS_USER_CHANNELS] = {0};
uint8_t 			ibus_flag = 0;
extern uint8_t ibus_buffer[32];


// pid variable
target_angle_t 		my_target_angle		 = {0, };	// 0
balancing_force_t 	my_balancing_force	 = {0, };	// output of pid

motor_speed_t		my_motor_speed		 = {0, };	// output of motor mixing algorithm


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)	// timer interrupt 1kHz
{
  if (htim == &htim11)
  {


	  complementary_filter(&my_icm20948, &my_angle);
	  p_control(&my_balancing_force, &my_target_angle, &my_angle);
	  distribute(&my_motor_speed, &my_balancing_force);

	  run_dshot600(&my_motors, my_value);


	  ibus_read_channel(my_channel);
	  period_us = __HAL_TIM_GET_COUNTER(&htim11);


  }
}

// ibus protocol receive interrupt
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	// 7ms period
	if(huart->Instance == IBUS_UART_INSTANCE)
	{
		HAL_UART_Receive_IT(IBUS_UART, ibus_buffer, 32);
	}
}



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
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  MX_TIM5_Init();
  MX_TIM11_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */



  // init rc controller
  ibus_init();

  // check sensor id
  id_icm20948 = whoami_icm20948();
  id_ak09916 = whoami_ak09916();

  // init sensor
  icm20948_init();
  ak09916_init();

  // calibrate sensor
  HAL_Delay(100);

  calibrate_icm20948(&my_icm20948, 100);

  // 1khz loop
  HAL_TIM_Base_Start_IT(&htim11);


  // after init, debug led on

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */



	  //__HAL_TIM_SET_COUNTER(&htim10, 0);
	  //complementary_filter(&my_icm20948, &my_angle);
	  //period_us = __HAL_TIM_GET_COUNTER(&htim11);

	  /*
	  if(my_channel[4] == 2000) // arming
	  {
		  if(my_channel[2] > 1011) // 69
		  {
			  for(int i = 0; i < 4; i++)
				  my_value[i] = (my_channel[2] - 1000) * 2 + 47;
		  }

		  else
		  {
			  for(int i = 0; i < 4; i++)
				  my_value[i] = 69; // minimum value to spin smoothly
		  }
	  }

	  else	// disarming
	  {
		  for(int i = 0; i < 4; i++)
			  my_value[i] = 0;
	  }
	  */

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
