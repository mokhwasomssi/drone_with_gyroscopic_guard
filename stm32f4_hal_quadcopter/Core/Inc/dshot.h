/*
 * dshot.h
 *
 *
 *  Created on: 2021. 1. 27.
 *      Author: mokhwasomssi
 * 
 */

#ifndef _DSHOT_H_
#define _DSHOT_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>


/* User Configuration */
// MOTOR1 : PA2
#define MOTOR_1_TIM             (&htim2)
#define MOTOR_1_TIM_CHANNEL     hdma_tim2_ch3_up

// MOTOR2 : PA3
#define MOTOR_2_TIM             (&htim5)
#define MOTOR_2_TIM_CHANNEL     hdma_tim5_ch4_trig

// MOTOR3 : PA1
#define MOTOR_3_TIM             (&htim5)
#define MOTOR_3_TIM_CHANNEL     hdma_tim5_ch2

// MOTOR4 : PA0
#define MOTOR_4_TIM             (&htim2)
#define MOTOR_4_TIM_CHANNEL     hdma_tim2_ch1
/* User Configuration */


#define MOTOR_BIT_0           7
#define MOTOR_BIT_1           14
#define MOTOR_BITLENGTH       20

#define DSHOT_FRAME_SIZE      18

#define NUM_OF_MOTORS          4

typedef uint32_t dshot_frame;

typedef uint16_t throttle_value;

void dshot600_single(dshot_frame *motor, throttle_value value);


#endif /* _DSHOT_H_ */
