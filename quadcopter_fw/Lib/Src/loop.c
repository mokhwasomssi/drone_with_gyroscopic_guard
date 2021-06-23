/*
 * loop.c
 *
 *
 *  Created on: 2021. 5. 27.
 *      Author: mokhwasomssi
 *
 */


#include "loop.h"
#include "dshot.h"



void loop_init(uint16_t loop_hz)
{
    uint32_t timer_clock = SystemCoreClock;

    uint16_t prescaler_1us = (timer_clock / 1000000) - 1;
    uint16_t period = (1000000 / loop_hz) - 1;

    __HAL_TIM_SET_PRESCALER(LOOP_TIM, prescaler_1us);  
    __HAL_TIM_SET_AUTORELOAD(LOOP_TIM, period);

    printf("%d Hz loop \n", loop_hz);
    printf("loop initialized \n");
}

uint16_t loop_runtime()
{
    return __HAL_TIM_GET_COUNTER(LOOP_TIM);
}

void loop_start()
{
    HAL_TIM_Base_Start_IT(LOOP_TIM);
}

