/**
 * @file   rc.c
 * @brief  change rc transmitter channel data to quadcopter command
 * @author mokhwasomssi
 * @date   2021-08-31
 */


#include "rc.h"


rc_command_t my_rc_command;
angle_t my_target_angle;


/* Static Functions */
static void clear_rc_command(rc_command_t* rc_command);
static void get_rc_raw_command(uint16_t ibus_channel[], rc_raw_command_t* rc_raw_command);
static void get_rc_command(rc_raw_command_t rc_raw_command, rc_command_t* rc_command);
static void get_target_angle(rc_command_t rc_command, angle_t* target_angle);


/* Main Functions */
void rc_init()
{
    ibus_init();
}

bool rc_update()
{
    static uint16_t ibus_channel[6] = { 0, 0, 0, 0, 0, 0 };
    rc_raw_command_t rc_raw_command = { 0 };

    if(!ibus_read(ibus_channel, 6))
        return false;
    
    if(is_ibus_lost())
    {
        clear_rc_command(&my_rc_command);
        return false;
    }

    get_rc_raw_command(ibus_channel, &rc_raw_command);
    get_rc_command(rc_raw_command, &my_rc_command);
    get_target_angle(my_rc_command, &my_target_angle);
    return true;
}


/* Static Functions */
static void clear_rc_command(rc_command_t* rc_command)
{
    rc_command->start = false;
    rc_command->arming = false;
    
    rc_command->throttle = 0;

    rc_command->roll = 0;
    rc_command->pitch = 0;
    rc_command->yaw = 0;
}

static void get_rc_raw_command(uint16_t ibus_channel[], rc_raw_command_t* rc_raw_command)
{
    rc_raw_command->start = ibus_channel[4];
    rc_raw_command->arming = ibus_channel[5];

    rc_raw_command->throttle = ibus_channel[2];

    rc_raw_command->roll = ibus_channel[0];
    rc_raw_command->pitch = ibus_channel[1];
    rc_raw_command->yaw = ibus_channel[3];
}

/**
 * @brief set angle command range
 */
static uint8_t set_angle_range(int8_t max_angle, int8_t min_angle)
{
    uint8_t angle_range = max_angle - min_angle;
    uint8_t scale_factor = 1000 / angle_range;

    return scale_factor;
}

static void get_rc_command(rc_raw_command_t rc_raw_command, rc_command_t* rc_command)
{
    rc_command->start  = (rc_raw_command.start == 2000) ? true : false;
    rc_command->arming = (rc_raw_command.arming == 2000) ? true : false;

    rc_command->throttle = rc_raw_command.throttle - 1000;

    uint8_t scale_factor = set_angle_range(20, -20); // send angle command upto ±20 degree
    rc_command->roll  = (int8_t)((rc_raw_command.roll  - 1500) / scale_factor);
    rc_command->pitch = (int8_t)((rc_raw_command.pitch - 1500) / scale_factor);
    rc_command->yaw   = (int8_t)((rc_raw_command.yaw   - 1500) / scale_factor);
}

/**
 * @brief get target angle from rc command
 * @param[in] rc_command
 * @param[out] target_angle
 */
static void get_target_angle(rc_command_t rc_command, angle_t* target_angle)
{
    target_angle->roll  = rc_command.roll;
    target_angle->pitch = rc_command.pitch;
    target_angle->yaw   = rc_command.yaw;
}