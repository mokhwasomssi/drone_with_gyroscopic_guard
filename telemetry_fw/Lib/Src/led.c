/*
 * led.c
 *
 *  Created on: Aug 26, 2021
 *      Author: mokhwasomssi
 */

#include "led.h"


// LED BLUE
void led_blue_on()
{
    HAL_GPIO_WritePin(LED_BLUE_PIN_PORT, LED_BLUE_PIN_NUMBER, RESET);
}

void led_blue_off()
{
    HAL_GPIO_WritePin(LED_BLUE_PIN_PORT, LED_BLUE_PIN_NUMBER, SET);
}

void led_blue_toggle()
{
    HAL_GPIO_TogglePin(LED_BLUE_PIN_PORT, LED_BLUE_PIN_NUMBER);
}