/*
 * buzzer.h
 *
 *  Created on: Aug 26, 2021
 *      Author: mokhwasomssi
 */


#ifndef __BUZZER_H__
#define __BUZZER_H__


#include "gpio.h"


#define BUZZER_PIN_PORT	    GPIOA
#define BUZZER_PIN_NUMBER	GPIO_PIN_10


void buzzer_on();
void buzzer_off();
void buzzer_time(uint16_t ms);


#endif /* __BUZZER_H__ */