/**
 * @file   imu.h
 * @brief  
 * @author mokhwasomssi
 * @date   2021-09-05
 */


#ifndef __IMU_H__
#define __IMU_H__


#include "icm20948.h"
#include "angle.h"
#include "interrupt.h"


extern angle_t my_angle;


void imu_init();
void imu_update();


#endif /* __IMU_H__ */