/**
 * @file   timer.c
 * @brief  
 * @author mokhwasomssi
 * @date   2021-09-10
 */


#include "timer.h"


void timer_init()
{   
    HAL_TIM_Base_Start(TIMER1);
    HAL_TIM_Base_Start(TIMER2);
}

void timer1_start()
{
    __HAL_TIM_SET_COUNTER(TIMER1, 0);
}

uint16_t timer1_end()
{
    return __HAL_TIM_GET_COUNTER(TIMER1);
}

void tiemr2_start()
{
    __HAL_TIM_SET_COUNTER(TIMER2, 0);
}

uint16_t timer2_end()
{
    return __HAL_TIM_GET_COUNTER(TIMER2);
}

