/*
 * buzzer.h
 *
 *
 *  Created on: 2021. 5. 8.
 *      Author: mokhwasomssi
 *
 */

#ifndef _BUZZER_H_
#define _BUZZER_H_


#include "gpio.h"


void buzzer_on();
void buzzer_off();

void buzzer_time(uint16_t ms);


#endif /* _BUZZER_H_ */