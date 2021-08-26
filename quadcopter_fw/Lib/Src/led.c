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


// LED2
void led2_on()
{
    HAL_GPIO_WritePin(LED2_PIN_PORT, LED2_PIN_NUMBER, SET);
}

void led2_off()
{
    HAL_GPIO_WritePin(LED2_PIN_PORT, LED2_PIN_NUMBER, RESET);
}

void led2_toggle()
{
    HAL_GPIO_TogglePin(LED2_PIN_PORT, LED2_PIN_NUMBER);
}


// LED3
void led3_on()
{
    HAL_GPIO_WritePin(LED3_PIN_PORT, LED3_PIN_NUMBER, SET);
}

void led3_off()
{
    HAL_GPIO_WritePin(LED3_PIN_PORT, LED3_PIN_NUMBER, RESET);
}

void led3_toggle()
{
    HAL_GPIO_TogglePin(LED3_PIN_PORT, LED3_PIN_NUMBER);
}