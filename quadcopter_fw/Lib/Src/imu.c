/**
 * @file   imu.c
 * @brief  
 * @author mokhwasomssi
 * @date   2021-09-05
 */


#include "imu.h"


angle_t my_angle;
gyro_t my_gyro;
accel_t my_accel;


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
    icm20948_gyro_read_dps(&my_gyro);
    icm20948_accel_read_g(&my_accel);
    complementary_filter(my_gyro, my_accel, imu_sampling_time*0.000001, 0.99, &my_angle);
}
