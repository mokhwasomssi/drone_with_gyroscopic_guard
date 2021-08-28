/*
 * angle.c
 *
 *  Created on: Aug 27, 2021
 *      Author: mokhwasomssi
 */


#include "angle.h"


void get_angle_from_accel(accel_t accel, angle_t* angle)
{
    angle_t temp_angle;

    // atan gives angle value between -90 and 90
    temp_angle.roll  = atan(accel.y / accel.z);
    temp_angle.pitch = atan(accel.x / sqrt(accel.y*accel.y + accel.z*accel.z));

    // convert radian to degree
    temp_angle.roll  *= RADIAN_TO_DEGREE;
    temp_angle.pitch *= RADIAN_TO_DEGREE;

    angle->roll  =  temp_angle.roll;
    angle->pitch = -temp_angle.pitch;
}

void get_angle_from_gyro(gyro_t gyro, angle_t prev_angle, angle_t* angle)
{
    angle_t temp_angle;

    temp_angle.roll = gyro.x * DT;
    temp_angle.pitch = gyro.y * DT;
    temp_angle.yaw = gyro.z * DT;

    angle->roll  = prev_angle.roll + temp_angle.roll;
    angle->pitch = prev_angle.pitch + temp_angle.pitch;
}

void complementary_filter(angle_t gyro_angle, angle_t accel_angle, angle_t* filterd_angle)
{
    filterd_angle->roll  = (1 - ALPHA)*gyro_angle.roll + ALPHA*accel_angle.roll;
    filterd_angle->pitch = (1 - ALPHA)*gyro_angle.pitch + ALPHA*accel_angle.pitch;
}
