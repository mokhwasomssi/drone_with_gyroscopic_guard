/*
 * dshot.h
 *
 *
 *  Created on: 2021. 1. 27.
 *      Author: mokhwasomssi
 *
 */

#include "dshot.h"



void make_dshot600_frame(dshot_frame *motor_x, throttle_value value)
{
  uint16_t packet = value << 1;

  // compute checksum
  int csum = 0;
  int csum_data = packet;
  for (int i = 0; i < 3; i++) {
    csum ^=  csum_data;   // xor data by nibbles
    csum_data >>= 4;
  }
  csum &= 0xf;

  // append checksum
  packet = (packet << 4) | csum;

  // encoding
  int i;
  for (i = 0; i < 16; i++)
  {
      motor_x[i] = (packet & 0x8000) ? MOTOR_BIT_1 : MOTOR_BIT_0;  // MSB first
      packet <<= 1;
  }

  motor_x[i++] = 0;
  motor_x[i++] = 0;
}

void run_dshot600(motors_s *motors, throttle_value value[])
{
  // prepare dshot frame
  make_dshot600_frame(motors->motor_1, value[0]);
  make_dshot600_frame(motors->motor_2, value[1]);
  make_dshot600_frame(motors->motor_3, value[2]);
  make_dshot600_frame(motors->motor_4, value[3]);

  // and send
  HAL_TIM_PWM_Start_DMA(MOTOR_1_TIM, MOTOR_1_TIM_CHANNEL, motors->motor_1, DSHOT_FRAME_SIZE);
  HAL_TIM_PWM_Start_DMA(MOTOR_2_TIM, MOTOR_2_TIM_CHANNEL, motors->motor_2, DSHOT_FRAME_SIZE);

  // commit : a0fc3be487dbd174be31abf8ce6e4e3b70c7a07b
  __HAL_TIM_RESET_HANDLE_STATE(&htim5);
  __HAL_TIM_RESET_HANDLE_STATE(&htim2);

  HAL_TIM_PWM_Start_DMA(MOTOR_3_TIM, MOTOR_3_TIM_CHANNEL, motors->motor_3, DSHOT_FRAME_SIZE);
  HAL_TIM_PWM_Start_DMA(MOTOR_4_TIM, MOTOR_4_TIM_CHANNEL, motors->motor_4, DSHOT_FRAME_SIZE);
}

