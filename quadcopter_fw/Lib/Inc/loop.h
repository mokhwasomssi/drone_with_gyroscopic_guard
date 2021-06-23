/*
 * loop.h
 *
 *
 *  Created on: 2021. 5. 27.
 *      Author: mokhwasomssi
 *
 */


#ifndef _LOOP_H_
#define _LOOP_H_


#include "tim.h"    // header from stm32cubemx code generate


/* user pin setting */
#define LOOP_TIM    (&htim11)


/* functions */
void loop_init(uint16_t loop_hz); // // ex : 1Khz loop -> loop_init(1000);

uint16_t loop_runtime(); // unit : us

void loop_start();


#endif /* _LOOP_H_ */ 