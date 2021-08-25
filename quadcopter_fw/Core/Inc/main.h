/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define Dshot_4_Pin GPIO_PIN_0
#define Dshot_4_GPIO_Port GPIOA
#define Dshot_3_Pin GPIO_PIN_1
#define Dshot_3_GPIO_Port GPIOA
#define Dshot_2_Pin GPIO_PIN_2
#define Dshot_2_GPIO_Port GPIOA
#define Dshot_1_Pin GPIO_PIN_3
#define Dshot_1_GPIO_Port GPIOA
#define ICM20948_CS_Pin GPIO_PIN_4
#define ICM20948_CS_GPIO_Port GPIOA
#define ICM20948_SCK_Pin GPIO_PIN_5
#define ICM20948_SCK_GPIO_Port GPIOA
#define ICM20948_MISO_Pin GPIO_PIN_6
#define ICM20948_MISO_GPIO_Port GPIOA
#define ICM20948_MOSI_Pin GPIO_PIN_7
#define ICM20948_MOSI_GPIO_Port GPIOA
#define nRF24L01__IRQ_Pin GPIO_PIN_2
#define nRF24L01__IRQ_GPIO_Port GPIOB
#define nRF24L01__IRQ_EXTI_IRQn EXTI2_IRQn
#define nRF24L01__SCK_Pin GPIO_PIN_10
#define nRF24L01__SCK_GPIO_Port GPIOB
#define nRF24L01__CE_Pin GPIO_PIN_12
#define nRF24L01__CE_GPIO_Port GPIOB
#define nRF24L01__CSN_Pin GPIO_PIN_13
#define nRF24L01__CSN_GPIO_Port GPIOB
#define nRF24L01__MISO_Pin GPIO_PIN_14
#define nRF24L01__MISO_GPIO_Port GPIOB
#define nRF24L01__MOSI_Pin GPIO_PIN_15
#define nRF24L01__MOSI_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
