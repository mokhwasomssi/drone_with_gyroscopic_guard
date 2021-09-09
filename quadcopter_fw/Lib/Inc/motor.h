/**
 * @file   motor.h
 * @brief  calculate and send motor value
 * @author mokhwasomssi
 * @date   2021-09-04
 */


#ifndef __MOTOR_H__
#define __MOTOR_H__


//#include "pid.h" // calculate motor value
#include "dshot.h" // send motor value


void motor_init();
void motor_update(uint16_t motor_value[]);


#endif /* __MOTOR_H__ */