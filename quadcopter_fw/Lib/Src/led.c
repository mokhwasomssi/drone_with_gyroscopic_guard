/*
 * led.c
 *
 *
 *  Created on: 2021. 5. 8.
 *      Author: mokhwasomssi
 *
 */

#include "led.h"


// LED1
void led1_on()
{
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, RESET);
}

void led1_off()
{
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, SET);
}

void led1_toggle()
{
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
}


// LED2
void led2_on()
{
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, SET);
}

void led2_off()
{
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, RESET);
}

void led2_toggle()
{
    HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
}


// LED3
void led3_on()
{
    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, SET);
}

void led3_off()
{
    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, RESET);
}

void led3_toggle()
{
    HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
}