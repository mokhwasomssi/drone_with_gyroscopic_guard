/**
 * @file   rc.c
 * @brief  change rc transmitter channel data to quadcopter command
 * @author mokhwasomssi
 * @date   2021-08-31
 */


#include "rc.h"


static int8_t angle_range;


void rc_init(int8_t max_angle, int8_t min_angle)
{
    ibus_init();
    angle_range = max_angle - min_angle;
}

bool rc_update(rc_command_t* rc_command)
{
    // read ibus channel
    static uint16_t ibus_channel[6] = { 0, 0, 0, 0, 0, 0 };
    ibus_read(ibus_channel, 6);

    // check ibus signal lost
    if(is_rc_lost())   
    {
        rc_command->arming = false;
        rc_command->roll = 0;
        rc_command->pitch = 0;
        rc_command->yaw = 0;
        rc_command->trottle = 0;

        return false;
    }

    // check arming
    if(ibus_channel[4] == 2000)
        rc_command->arming = true;
    else
        rc_command->arming = false;

    // convert ibus data to rc command
    uint8_t scale_factor = 1000 / angle_range;

    rc_command->roll  = (ibus_channel[0] - 1500) / scale_factor;
    rc_command->pitch = (ibus_channel[1] - 1500) / scale_factor;
    rc_command->yaw   = (ibus_channel[3] - 1500) / scale_factor;
    
    rc_command->trottle = ibus_channel[2] - 1000;

    return true;
}

bool is_rc_lost()
{
    return is_ibus_lost();
}
