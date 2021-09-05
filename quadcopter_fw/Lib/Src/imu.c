/**
 * @file   imu.c
 * @brief  
 * @author mokhwasomssi
 * @date   2021-09-05
 */


#include "imu.h"


void imu_init()
{
    icm20948_init();
    ak09916_init();
}

void imu_angle_update(double dt, angle_t* angle)
{
    gyro_t temp_gyro;
    accel_t temp_accel;

    icm20948_gyro_read_dps(&temp_gyro);
    icm20948_accel_read_g(&temp_accel);
    complementary_filter(temp_gyro, temp_accel, dt, 0.99, angle);
}
