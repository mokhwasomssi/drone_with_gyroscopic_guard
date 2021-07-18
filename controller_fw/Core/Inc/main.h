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
#define Stick_Roll_Pin GPIO_PIN_0
#define Stick_Roll_GPIO_Port GPIOA
#define Stick_Pitch_Pin GPIO_PIN_1
#define Stick_Pitch_GPIO_Port GPIOA
#define Stick_Throttle_Pin GPIO_PIN_2
#define Stick_Throttle_GPIO_Port GPIOA
#define Stick_Yaw_Pin GPIO_PIN_3
#define Stick_Yaw_GPIO_Port GPIOA
#define SW1_Pin GPIO_PIN_6
#define SW1_GPIO_Port GPIOA
#define SW2_Pin GPIO_PIN_7
#define SW2_GPIO_Port GPIOA
#define ADC_BAT_Pin GPIO_PIN_0
#define ADC_BAT_GPIO_Port GPIOB
#define nRF24L01_SCK_Pin GPIO_PIN_10
#define nRF24L01_SCK_GPIO_Port GPIOB
#define nRF24L01_CE_Pin GPIO_PIN_12
#define nRF24L01_CE_GPIO_Port GPIOB
#define nRF24L01_CSN_Pin GPIO_PIN_13
#define nRF24L01_CSN_GPIO_Port GPIOB
#define nRF24L01_MISO_Pin GPIO_PIN_14
#define nRF24L01_MISO_GPIO_Port GPIOB
#define nRF24L01_MOSI_Pin GPIO_PIN_15
#define nRF24L01_MOSI_GPIO_Port GPIOB
#define Buzzer_Pin GPIO_PIN_10
#define Buzzer_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
