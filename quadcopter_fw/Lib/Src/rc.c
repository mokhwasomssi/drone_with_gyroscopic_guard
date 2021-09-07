/**
 * @file   rc.c
 * @brief  change rc transmitter channel data to quadcopter command
 * @author mokhwasomssi
 * @date   2021-08-31
 */


#include "rc.h"


/* Main Functions */
void rc_init()
{
    ibus_init();
}

bool rc_update(rc_command_t* rc_command)
{
    static uint16_t ibus_channel[6] = { 0, 0, 0, 0, 0, 0 };
    rc_raw_command_t rc_raw_command = { 0 };

    if(!ibus_read(ibus_channel, 6))
        return false;

    if(is_ibus_lost())   
    {
        rc_command_clear(rc_command);
        return false;
    }

    rc_channel_mapping(ibus_channel, &rc_raw_command);
    rc_get_command(rc_raw_command, rc_command);
    return true;
}


/* Sub Functions */
void rc_command_clear(rc_command_t* rc_command)
{
    rc_command->start = false;
    rc_command->arming = false;
    
    rc_command->throttle = 0;

    rc_command->roll = 0;
    rc_command->pitch = 0;
    rc_command->yaw = 0;
}

void rc_channel_mapping(uint16_t ibus_channel[], rc_raw_command_t* rc_raw_command)
{
    rc_raw_command->start = ibus_channel[4];
    rc_raw_command->arming = ibus_channel[5];

    rc_raw_command->throttle = ibus_channel[2];

    rc_raw_command->roll = ibus_channel[0];
    rc_raw_command->pitch = ibus_channel[1];
    rc_raw_command->yaw = ibus_channel[3];
}

static uint8_t rc_set_angle_range(int8_t max_angle, int8_t min_angle)
{
    int8_t angle_range = max_angle - min_angle;
    uint8_t scale_factor = 1000 / angle_range;

    return scale_factor;
}

void rc_get_command(rc_raw_command_t rc_raw_command, rc_command_t* rc_command)
{
    rc_command->start  = (rc_raw_command.start == 2000) ? true : false;
    rc_command->arming = (rc_raw_command.arming == 2000) ? true : false;

    rc_command->throttle = rc_raw_command.throttle - 1000;

    uint8_t scale_factor = rc_set_angle_range(20, -20);
    rc_command->roll  = (int16_t)((rc_raw_command.roll - 1500) / scale_factor);
    rc_command->pitch = (int16_t)((rc_raw_command.pitch - 1500) / scale_factor);
    rc_command->yaw   = (int16_t)((rc_raw_command.yaw - 1500) / scale_factor);
}