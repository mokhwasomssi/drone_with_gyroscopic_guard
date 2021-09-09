/**
 * @file   interrupt.h
 * @brief  
 * @author mokhwasomssi
 * @date   2021-09-10
 */


#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__


#include "usart.h"
#include "gpio.h"
#include "ibus.h"
#include "led.h"
#include "timer.h"
#include "nrf24l01p.h"
#include "icm20948.h"


extern us imu_sampling_time;
extern us telemetry_time;
extern bool imu_ready;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);


#endif /* __INTERRUPT_H__ */