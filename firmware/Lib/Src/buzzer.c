/*
 * buzzer.c
 *
 *  Created on: Aug 26, 2021
 *      Author: mokhwasomssi
 */


#include "buzzer.h"


void buzzer_on()
{
    HAL_GPIO_WritePin(BUZZER_PIN_PORT, BUZZER_PIN_NUMBER, SET);

}

void buzzer_off()
{
    HAL_GPIO_WritePin(BUZZER_PIN_PORT, BUZZER_PIN_NUMBER, RESET);
}

void buzzer_time(uint16_t ms)
{
    HAL_GPIO_WritePin(BUZZER_PIN_PORT, BUZZER_PIN_NUMBER, SET);
    HAL_Delay(ms);
    HAL_GPIO_WritePin(BUZZER_PIN_PORT, BUZZER_PIN_NUMBER, RESET);
}