/**
 * @file   led.h
 * @brief  led on/off and toggle functions
 * @author mokhwasomssi
 * @date   2021-08-26
 */


#ifndef __LED_H__
#define __LED_H__


#include "gpio.h"


#define LED_BLUE_PIN_PORT	    GPIOC
#define LED_BLUE_PIN_NUMBER	    GPIO_PIN_13

#define LED_GREEN_PIN_PORT	    GPIOB
#define LED_GREEN_PIN_NUMBER	GPIO_PIN_1

#define LED_YELLOW_PIN_PORT	GPIOB
#define LED_YELLOW_PIN_NUMBER	GPIO_PIN_2


// LED BLUE
void led_blue_on();
void led_blue_off();
void led_blue_toggle();

// LED GREEN
void led_green_on();
void led_green_off();
void led_green_toggle();

// LED YELLOW
void led_yellow_on();
void led_yellow_off();
void led_yellow_toggle();


#endif /* __LED_H__ */
