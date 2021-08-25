/*
 * led.h
 *
 *
 *  Created on: 2021. 5. 8.
 *      Author: mokhwasomssi
 *
 */

#ifndef __LED_H__
#define __LED_H__


#include "gpio.h"


#define LED_PIN_PORT	GPIOC
#define LED_PIN_NUMBER	GPIO_PIN_13


void led_on();
void led_off();
void led_toggle();


#endif /* __LED_H__ */
