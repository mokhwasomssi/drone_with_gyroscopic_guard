/*
 * pid.c
 *
 *  Created on: 2021. 2. 21.
 *      Author: mokhwasomssi
 */

#include "pid.h"


void p_control(balancing_force_t *balancing_force, target_angle_t *target_angle, angle_t *angle)
{
    double angle_error_roll    = target_angle->roll - angle->angle_x;
    double angle_error_pitch   = target_angle->pitch - angle->angle_y;
    double angle_error_yaw     = target_angle->yaw - angle->angle_z;

    balancing_force->roll      = 1 * angle_error_roll;
    balancing_force->pitch     = 1 * angle_error_pitch;
    balancing_force->yaw       = 1 * angle_error_yaw;
}


// calculate motor speed using output of pid control
void distribute(motor_speed_t *motor_speed, balancing_force_t *balancing_force)
{
    // default throttle
    motor_speed->default_value = 100;

    // motor mixing algorithm
    motor_speed->motor_1 = motor_speed->default_value  + balancing_force->yaw - balancing_force->pitch + balancing_force->roll;
    motor_speed->motor_2 = motor_speed->default_value  - balancing_force->yaw - balancing_force->pitch - balancing_force->roll;
    motor_speed->motor_3 = motor_speed->default_value  - balancing_force->yaw + balancing_force->pitch + balancing_force->roll;
    motor_speed->motor_4 = motor_speed->default_value  + balancing_force->yaw + balancing_force->pitch - balancing_force->roll;

    // motor speed limit
    // motor 1
    if(motor_speed->motor_1 < DSHOT_THROTTLE_MIN) motor_speed->motor_1 = DSHOT_THROTTLE_MIN;
    if(motor_speed->motor_1 > DSHOT_THROTTLE_MAX) motor_speed->motor_1 = DSHOT_THROTTLE_MAX;

    // motor 2
    if(motor_speed->motor_2 < DSHOT_THROTTLE_MIN) motor_speed->motor_2 = DSHOT_THROTTLE_MIN;
    if(motor_speed->motor_2 > DSHOT_THROTTLE_MAX) motor_speed->motor_2 = DSHOT_THROTTLE_MAX;

    // motor 3
    if(motor_speed->motor_3 < DSHOT_THROTTLE_MIN) motor_speed->motor_3 = DSHOT_THROTTLE_MIN;
    if(motor_speed->motor_3 > DSHOT_THROTTLE_MAX) motor_speed->motor_3 = DSHOT_THROTTLE_MAX;

    // motor 4
    if(motor_speed->motor_4 < DSHOT_THROTTLE_MIN) motor_speed->motor_4 = DSHOT_THROTTLE_MIN;
    if(motor_speed->motor_4 > DSHOT_THROTTLE_MAX) motor_speed->motor_4 = DSHOT_THROTTLE_MAX;

    extern channel my_channel[IBUS_USER_CHANNELS];
    // throttle = 0 from my_channel[2]
    if(my_channel[2] == 1000)
    {
        motor_speed->motor_1 = 0;
        motor_speed->motor_2 = 0;
        motor_speed->motor_3 = 0;
        motor_speed->motor_4 = 0;
    }
}
