/**
 * @file   imu.c
 * @brief  
 * @author mokhwasomssi
 * @date   2021-09-05
 */


#include "imu.h"


angle_t my_angle;


void imu_init()
{
    icm20948_init();
    ak09916_init();
}

/**
 * @brief calculate and update current angle
 */
void imu_update()
{
    gyro_t temp_gyro;
    accel_t temp_accel;

    icm20948_gyro_read_dps(&temp_gyro);
    icm20948_accel_read_g(&temp_accel);
    complementary_filter(temp_gyro, temp_accel, imu_sampling_time*0.000001, 0.99, &my_angle);
}
