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

/* user configuration */

#define DEFALUT_VALUE       100

/* user configuration */




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


//void p_control(balancing_force_t *balancing_force, target_angle_t *target_angle, angle_t *angle);
//void distribute(throttle_a *cal_value, rc_channel *channel, balancing_force_t *balancing_force);

#endif /* _PID_H_ */
