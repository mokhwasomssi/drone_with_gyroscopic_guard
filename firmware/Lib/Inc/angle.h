/*
 * angle.h
 *
 *  Created on: Aug 27, 2021
 *      Author: mokhwasomssi
 */


#ifndef __ANGLE_H__
#define __ANGLE_H__


#include "icm20948.h"
#include <math.h>

/* User Configuration */
#define DT                  0.001 // 1ms
#define ALPHA               0.01  // complemetary filter coefficient

#define RADIAN_TO_DEGREE    (180 / M_PI);


typedef struct 
{
    double roll;
    double pitch;
    double yaw;
} angle_t;


void get_angle_from_accel(accel_t accel, angle_t* angle); // integrate anguler velocity
void get_angle_from_gyro(gyro_t gyro, angle_t prev_angle, angle_t* angle); // use gravity acceleration.

void complementary_filter(angle_t gyro_angle, angle_t accel_angle, angle_t* filterd_angle);

#endif /* __ANGLE_H__ */
