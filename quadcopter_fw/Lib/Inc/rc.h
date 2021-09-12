/**
 * @file   rc.h
 * @brief  change rc transmitter channel data to quadcopter command
 * @author mokhwasomssi
 * @date   2021-08-31
 */


#ifndef __RC_H__
#define __RC_H__


#include "ibus.h"
#include "imu.h"


typedef struct 
{
    bool start;     // if start is true, start init functions and control loop.
    bool arming;    // start the motors.

    uint16_t throttle; 

    int16_t roll;   // target angle (unit : degree)
    int16_t pitch;
    int16_t yaw;
} rc_command_t;

typedef struct 
{
    // struct for mapping ibus channel to rc command.
    // have same data type(uint16_t) as ibus data.
    uint16_t start;   
    uint16_t arming; 

    uint16_t throttle; 

    uint16_t roll;  
    uint16_t pitch;
    uint16_t yaw;
} rc_raw_command_t;


extern rc_command_t my_rc_command;
extern angle_t my_target_angle;


/* Main Functions */
void rc_init();
bool rc_update();


#endif /* __RC_H__ */