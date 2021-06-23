/*
 * buzzer.h
 *
 *
 *  Created on: 2021. 5. 8.
 *      Author: mokhwasomssi
 *
 */

#include "buzzer.h"


void buzzer_on()
{
    HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, SET);

}

void buzzer_off()
{
    HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, RESET);
}

void buzzer_time(uint16_t ms)
{
    HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, SET);
    HAL_Delay(ms);
    HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, RESET);
}