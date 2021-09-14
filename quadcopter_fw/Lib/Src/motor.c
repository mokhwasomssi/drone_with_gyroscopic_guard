/**
 * @file   motor.c
 * @brief  calculate and send motor value
 * @author mokhwasomssi
 * @date   2021-09-04
 */


#include "motor.h"



double my_motor_value[4]; // value range : 0 - 1000
static uint16_t dshot_value[4] = { 0, 0, 0, 0 }; // value range : 0, 48 - 2047


/* Static Functions */
static void clear_motor_value();
static void mixer();
static void limit_motor_value();
static void ready_dshot_value();


/* Main Functions */
void motor_init()
{
    dshot_init(DSHOT600); // use dshot as drone esc protocol
}


void motor_update()
{
    if(my_rc_command.arming)
    {
        led_blue_on(); // arming indicator
        pid_angle();
        mixer();
    }

    else
    {
        led_blue_off(); // disarming indicator
        clear_motor_value();
    }

    ready_dshot_value();
    dshot_write(dshot_value);
}


/* Static Functions */
static void clear_motor_value()
{
    for(int i = 0; i < 4; i++)
        my_motor_value[i] = 0;
}

static void mixer()
{
    uint16_t throttle = my_rc_command.throttle;

    double roll  = my_pid_value.roll;
    double pitch = my_pid_value.pitch;
    double yaw   = my_pid_value.yaw;

    my_motor_value[0] = throttle + roll - pitch + yaw;
    my_motor_value[1] = throttle - roll - pitch - yaw;
    my_motor_value[2] = throttle + roll + pitch - yaw;
    my_motor_value[3] = throttle - roll + pitch + yaw;

    limit_motor_value();
}

/**
 * @brief limit motor_value between 0 to 1000
 * @param[out] motor_value
 */
static void limit_motor_value()
{
    for(int i = 0; i < 4; i++)
    {
        if(my_motor_value[i] < 0) my_motor_value[i] = 0;
        if(my_motor_value[i] > 1000) my_motor_value[i] = 1000;
    }
}

/**
 * @brief convert motor value to dshot value
 * @param[in] motor_value 
 * @param[out] dshot_value actual value to send
 */
static void ready_dshot_value()
{
    for(int i = 0; i < 4; i++)
    {
        if(my_motor_value[i] == 0) // dshot trottle : 0 (0)
            dshot_value[i] = 0;
        
        else // dshot throttle : 48 - 2047 (1 - 2000)
            dshot_value[i] = 47 + (my_motor_value[i] * 2);
    }
}
