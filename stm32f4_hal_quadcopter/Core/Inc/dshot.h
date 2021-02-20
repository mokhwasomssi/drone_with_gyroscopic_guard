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
#include "tim.h"
#include <stdbool.h>


/* User Configuration */
// MOTOR1 : PA2
#define MOTOR_1_TIM             (&htim2)
#define MOTOR_1_TIM_CHANNEL     TIM_CHANNEL_3

// MOTOR2 : PA3
#define MOTOR_2_TIM             (&htim5)
#define MOTOR_2_TIM_CHANNEL     TIM_CHANNEL_4

// MOTOR3 : PA1
#define MOTOR_3_TIM             (&htim5)
#define MOTOR_3_TIM_CHANNEL     TIM_CHANNEL_2

// MOTOR4 : PA0
#define MOTOR_4_TIM             (&htim2)
#define MOTOR_4_TIM_CHANNEL     TIM_CHANNEL_1
/* User Configuration */


#define MOTOR_BIT_0           7
#define MOTOR_BIT_1           14
#define MOTOR_BITLENGTH       20

#define DSHOT_FRAME_SIZE      18

#define NUM_OF_MOTORS          4    // quadcopter

typedef uint32_t dshot_frame;
typedef uint16_t throttle_value;

typedef struct _motors
{
    dshot_frame motor_1[DSHOT_FRAME_SIZE];
    dshot_frame motor_2[DSHOT_FRAME_SIZE];
    dshot_frame motor_3[DSHOT_FRAME_SIZE];
    dshot_frame motor_4[DSHOT_FRAME_SIZE];

} motors_s;

void dshot_init();
void make_dshot600_frame(dshot_frame *motor_x, throttle_value value);
void run_dshot600(motors_s *motors, throttle_value value[]);


#endif /* _DSHOT_H_ */
