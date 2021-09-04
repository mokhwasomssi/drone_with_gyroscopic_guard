/**
 * @file   motor.h
 * @brief  
 * @author mokhwasomssi
 * @date   2021-09-04
 */


#ifndef __MOTOR_H__
#define __MOTOR_H__


#include "dshot.h"


void motor_init();
void motor_update(uint16_t motor_value[]);


#endif /* __MOTOR_H__ */