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

#define LED2_PIN_PORT	GPIOB
#define LED2_PIN_NUMBER	GPIO_PIN_1

#define LED3_PIN_PORT	GPIOB
#define LED3_PIN_NUMBER	GPIO_PIN_2


void led1_on();
void led1_off();
void led1_toggle();

void led2_on();
void led2_off();
void led2_toggle();

void led3_on();
void led3_off();
void led3_toggle();


#endif /* __LED_H__ */
