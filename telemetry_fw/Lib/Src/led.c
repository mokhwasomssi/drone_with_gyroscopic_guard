/*
 * led.c
 *
 *  Created on: Aug 26, 2021
 *      Author: mokhwasomssi
 */

#include "led.h"


// LED1
void led1_on()
{
    HAL_GPIO_WritePin(LED1_PIN_PORT, LED1_PIN_NUMBER, RESET);
}

void led1_off()
{
    HAL_GPIO_WritePin(LED1_PIN_PORT, LED1_PIN_NUMBER, SET);
}

void led1_toggle()
{
    HAL_GPIO_TogglePin(LED1_PIN_PORT, LED1_PIN_NUMBER);
}
