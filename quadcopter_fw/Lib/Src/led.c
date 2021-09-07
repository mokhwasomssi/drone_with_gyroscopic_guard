/**
 * @file   led.c
 * @brief  led on/off and toggle functions
 * @author mokhwasomssi
 * @date   2021-08-26
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


// LED GREEN
void led_green_on()
{
    HAL_GPIO_WritePin(LED_GREEN_PIN_PORT, LED_GREEN_PIN_NUMBER, SET);
}

void led_green_off()
{
    HAL_GPIO_WritePin(LED_GREEN_PIN_PORT, LED_GREEN_PIN_NUMBER, RESET);
}

void led_green_toggle()
{
    HAL_GPIO_TogglePin(LED_GREEN_PIN_PORT, LED_GREEN_PIN_NUMBER);
}


// LED YELLOW
void led_yellow_on()
{
    HAL_GPIO_WritePin(LED_YELLOW_PIN_PORT, LED_YELLOW_PIN_NUMBER, SET);
}

void led_yellow_off()
{
    HAL_GPIO_WritePin(LED_YELLOW_PIN_PORT, LED_YELLOW_PIN_NUMBER, RESET);
}

void led_yellow_toggle()
{
    HAL_GPIO_TogglePin(LED_YELLOW_PIN_PORT, LED_YELLOW_PIN_NUMBER);
}