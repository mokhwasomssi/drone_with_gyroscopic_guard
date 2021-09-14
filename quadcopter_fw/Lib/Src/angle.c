/**
 * @file   angle.c
 * @brief  calculate angle from imu sensor data.
 * @author mokhwasomssi
 * @date   2021-08-30
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

void get_angle_from_gyro(gyro_t gyro, angle_t prev_angle, double dt, angle_t* angle)
{
    angle_t temp_angle;

    temp_angle.roll  = gyro.x * dt;
    temp_angle.pitch = gyro.y * dt;
    temp_angle.yaw   = gyro.z * dt;

    angle->roll  = prev_angle.roll + temp_angle.roll;
    angle->pitch = prev_angle.pitch + temp_angle.pitch;
    angle->yaw   = prev_angle.yaw + temp_angle.pitch;
}

void complementary_filter(gyro_t gyro, accel_t accel, sec dt, double alpha, angle_t* filtered_angle)
{
    angle_t accel_angle;
    get_angle_from_accel(accel, &accel_angle);

    angle_t gyro_angle;
    get_angle_from_gyro(gyro, *filtered_angle, dt, &gyro_angle);

    filtered_angle->roll  = alpha*gyro_angle.roll  + (1-alpha)*accel_angle.roll;
    filtered_angle->pitch = alpha*gyro_angle.pitch + (1-alpha)*accel_angle.pitch;

}

void get_roll_angle(gyro_t gyro, accel_t accel, sec dt, double alpha, angle_t* angle)
{
    double accel_roll_angle;
    accel_roll_angle = atan(accel.y / accel.z) * RADIAN_TO_DEGREE;

    // complementary_filter
    angle->roll = alpha*(gyro.x*dt + angle->roll) + (1-alpha)*accel_roll_angle; 
}

void get_pitch_angle(gyro_t gyro, accel_t accel, sec dt, double alpha, angle_t* angle)
{
    double accel_pitch_angle;
    accel_pitch_angle = -atan(accel.x / sqrt(accel.y*accel.y + accel.z*accel.z)) * RADIAN_TO_DEGREE;

    // complementary_filter
    angle->pitch = alpha*(gyro.y*dt + angle->pitch) + (1-alpha)*accel_pitch_angle; 
}

void get_yaw_angle(gyro_t gyro, sec dt, angle_t* angle)
{
    angle->yaw += gyro.z*dt;
}