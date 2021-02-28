/*
 * pid.h
 *
 *  Created on: 2021. 2. 21.
 *      Author: mokhwasomssi
 */

#ifndef _PID_H_
#define _PID_H_

#include "main.h"
#include "icm_20948.h"
#include "dshot.h"
#include "flysky_ibus.h"

// target angle to balance
// defalut : 0
typedef struct 
{
    double roll;
    double pitch;
    double yaw;

} target_angle_t;

// balancing force is output of pid control
typedef struct
{
    double roll;
    double pitch;
    double yaw;

} balancing_force_t;

// throttle value of motor to be calculated
typedef struct
{
    throttle_value default_value;

    throttle_value motor_1;
    throttle_value motor_2;
    throttle_value motor_3;
    throttle_value motor_4;

} motor_speed_t;

void p_control(balancing_force_t *balancing_force, target_angle_t *target_angle, angle_t *angle);
void distribute(motor_speed_t *motor_speed, balancing_force_t *balancing_force);

#endif /* _PID_H_ */
