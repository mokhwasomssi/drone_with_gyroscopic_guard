/**
 * @file   angle.h
 * @brief  calculate angle from imu sensor data.
 * @author mokhwasomssi
 * @date   2021-08-30
 */


#ifndef __ANGLE_H__
#define __ANGLE_H__


#include "icm20948.h"
#include <math.h>


#define RADIAN_TO_DEGREE    (180 / M_PI);

typedef double sec;
typedef struct 
{
    double roll;
    double pitch;
    double yaw;
} angle_t;


void get_angle_from_gyro(gyro_t gyro, angle_t prev_angle, double dt, angle_t* angle); // integrate anguler velocity
void get_angle_from_accel(accel_t accel, angle_t* angle); // use gravity acceleration.

void complementary_filter(gyro_t gyro, accel_t accel, sec dt, double alpha, angle_t* filtered_angle);


void get_roll_angle(gyro_t gyro, accel_t accel, sec dt, double alpha, angle_t* angle);
void get_pitch_angle(gyro_t gyro, accel_t accel, sec dt, double alpha, angle_t* angle);
void get_yaw_angle(gyro_t gyro, sec dt, angle_t* angle);

#endif /* __ANGLE_H__ */
