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
void led_on()
{
    HAL_GPIO_WritePin(LED_PIN_PORT, LED_PIN_NUMBER, RESET);
}

void led_off()
{
    HAL_GPIO_WritePin(LED_PIN_PORT, LED_PIN_NUMBER, SET);
}

void led_toggle()
{
    HAL_GPIO_TogglePin(LED_PIN_PORT, LED_PIN_NUMBER);
}
