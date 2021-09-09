/**
 * @file   timer.c
 * @brief  
 * @author mokhwasomssi
 * @date   2021-09-10
 */


#include "timer.h"


void timer_init()
{   
    HAL_TIM_Base_Start(TIMER_1);
    HAL_TIM_Base_Start(TIMER_2);
}

uint16_t get_timer_1_counter()
{
    return __HAL_TIM_GET_COUNTER(TIMER_1);
}

void set_timer_1_counter_zero()
{
    __HAL_TIM_SET_COUNTER(TIMER_1, 0);
}

uint16_t get_timer_2_counter()
{
    return __HAL_TIM_GET_COUNTER(TIMER_2);
}

void set_timer_2_counter_zero()
{
    __HAL_TIM_SET_COUNTER(TIMER_2, 0);
}
