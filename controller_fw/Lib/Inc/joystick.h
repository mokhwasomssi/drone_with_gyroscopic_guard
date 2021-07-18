/*
 * joystick.h
 *
 *
 *  Created on: 2021. 7. 16.
 *      Author: mokhwasomssi
 *
 */


#include "adc.h"


// stm32f411ceu6 only has adc1
#define JOYSTICK_ADC    (&hadc1)


extern uint16_t stick_roll;
extern uint16_t stick_pitch;
extern uint16_t stick_throttle;
extern uint16_t stick_yaw;


void joystick_init();
