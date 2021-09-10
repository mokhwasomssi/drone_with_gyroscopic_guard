/**
 * @file   interrupt.h
 * @brief  define interrupt callback functions.
 * @author mokhwasomssi
 * @date   2021-09-10
 */


#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__


#include <stdbool.h>
#include "nrf24l01p.h"
#include "led.h"
#include "telemetry.h"


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);


#endif /* __INTERRUPT_H__ */