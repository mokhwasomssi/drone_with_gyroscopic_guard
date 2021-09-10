/*
 * led.h
 *
 *  Created on: Aug 26, 2021
 *      Author: mokhwasomssi
 */

#ifndef __LED_H__
#define __LED_H__


#include "gpio.h"


#define LED_BLUE_PIN_PORT	    GPIOC
#define LED_BLUE_PIN_NUMBER	    GPIO_PIN_13


// LED BLUE
void led_blue_on();
void led_blue_off();
void led_blue_toggle();


#endif /* __LED_H__ */
