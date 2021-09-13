/**
 * @file   motor.h
 * @brief  calculate and send motor value
 * @author mokhwasomssi
 * @date   2021-09-04
 */


#ifndef __MOTOR_H__
#define __MOTOR_H__


#include "pid.h" // calculate motor value
#include "dshot.h" // send motor value
#include "rc.h"
#include "interrupt.h"
#include "led.h"



extern double my_motor_value[4];


/* Main Functions */
void motor_init();
void motor_update();


#endif /* __MOTOR_H__ */