/*
 * led.h
 *
 *  Created on: Aug 26, 2021
 *      Author: mokhwasomssi
 */

#ifndef __LED_H__
#define __LED_H__


#include "gpio.h"


#define LED1_PIN_PORT	GPIOC
#define LED1_PIN_NUMBER	GPIO_PIN_13


void led1_on();
void led1_off();
void led1_toggle();


#endif /* __LED_H__ */
