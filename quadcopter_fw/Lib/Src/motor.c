/**
 * @file   motor.c
 * @brief  calculate and send motor value
 * @author mokhwasomssi
 * @date   2021-09-04
 */


#include "motor.h"


angle_t my_pid_value;
double my_motor_value[4]; // value range : 0 - 1000
uint16_t dshot_value[4] = { 0, 0, 0, 0 }; // value range : 0, 48 - 2047


/* Static Functions */
static void motor_value_clear();
static void mixer(uint16_t throttle, angle_t pid_value, double motor_value[]);
static void limit_motor_value(double motor_value[]);
static void dshot_ready();


/* Main Functions */
void motor_init()
{
    dshot_init(DSHOT600); // use dshot as drone esc protocol
}


void motor_update() // 매개변수에 각도 추가
{
    uint16_t throttle = my_rc_command.throttle;

    if(!my_rc_command.arming)
    {
        motor_value_clear();
        // pid_value_clear
    }

    else
    {
        pid_calculate(my_angle, my_gyro, imu_sampling_time*0.000001, my_target_angle, &my_pid_value);
        mixer(throttle, my_pid_value, my_motor_value);
    }

    dshot_ready(my_motor_value, dshot_value);
    dshot_write(dshot_value);
}


/* Static Functions */
static void motor_value_clear()
{
    for(int i = 0; i < 4; i++)
        my_motor_value[i] = 0;
}

/**
 * @brief
 * @param[in] throttle
 * @param[in] pid_value
 * @param[out] motor_value
 */
static void mixer(uint16_t throttle, angle_t pid_value, double motor_value[])
{
    double roll  = pid_value.roll;
    double pitch = pid_value.pitch;
    double yaw   = pid_value.yaw;

    motor_value[0] = throttle + roll + pitch + yaw;
    motor_value[1] = throttle - roll + pitch - yaw;
    motor_value[2] = throttle + roll - pitch - yaw;
    motor_value[3] = throttle - roll - pitch + yaw;

    limit_motor_value(motor_value);
}

/**
 * @brief limit motor_value between 0 to 1000
 * @param[out] motor_value
 */
static void limit_motor_value(double motor_value[])
{
    for(int i = 0; i < 4; i++)
    {
        if(motor_value[i] < 0) motor_value[i] = 0;
        if(motor_value[i] > 1000) motor_value[i] = 1000;
    }
}

/**
 * @brief convert motor value to dshot value
 * @param[in] motor_value 
 * @param[out] dshot_value actual value to send
 */
static void dshot_ready(double motor_value[], uint16_t dshot_value[])
{
    for(int i = 0; i < 4; i++)
    {
        if(motor_value[i] == 0) // dshot trottle : 0 (0)
            dshot_value[i] = 0;
        
        else // dshot throttle : 48 - 2047 (1 - 2000)
            dshot_value[i] = 47 + (motor_value[i] * 2);
    }
}
