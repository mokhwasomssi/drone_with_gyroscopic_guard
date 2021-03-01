/*
 * pid.c
 *
 *  Created on: 2021. 2. 21.
 *      Author: mokhwasomssi
 */

#include "pid.h"


// throttle value of motor to be calculated
throttle_a cal_value[4] = {0};

// control value
void p_control(balancing_force_t *balancing_force, target_angle_t *target_angle, angle_t *angle)
{
    double angle_error_roll    = target_angle->roll - angle->angle_x;
    double angle_error_pitch   = target_angle->pitch - angle->angle_y;
    double angle_error_yaw     = target_angle->yaw - angle->angle_z;

    balancing_force->roll      = 1 * angle_error_roll;
    balancing_force->pitch     = 1 * angle_error_pitch;
    balancing_force->yaw       = 1 * angle_error_yaw;
}


// final value
void distribute(throttle_a *cal_value, rc_channel_a *channel, balancing_force_t *balancing_force)
{
    uint16_t defalut_throttle = (channel[2] - 1000) * 2 + 47;

    // motor mixing algorithm
    // add control value to defaut value
    cal_value[0] = defalut_throttle + balancing_force->yaw - balancing_force->pitch + balancing_force->roll;
    cal_value[1] = defalut_throttle - balancing_force->yaw - balancing_force->pitch - balancing_force->roll;
    cal_value[2] = defalut_throttle - balancing_force->yaw + balancing_force->pitch + balancing_force->roll;
    cal_value[3] = defalut_throttle + balancing_force->yaw + balancing_force->pitch - balancing_force->roll;

    // limit
    for(int i = 0; i < 4; i++)
    {
        if(cal_value[i] < DSHOT_THROTTLE_MIN) cal_value[i] = DSHOT_THROTTLE_MIN;
        if(cal_value[i] > DSHOT_THROTTLE_MAX) cal_value[i] = DSHOT_THROTTLE_MAX;
    }
}
