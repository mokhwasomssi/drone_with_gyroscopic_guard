/**
 * @file   pid.h
 * @brief  calculate motor value
 * @author mokhwasomssi
 * @date   2021-09-12
 */


#ifndef __PID_H__
#define __PID_H__


#include "imu.h"


void pid_init();
void pid_calculate(angle_t current_angle, gyro_t current_gyro, double dt, angle_t target_angle, angle_t* pid_value);


#endif /* __PID_H__ */