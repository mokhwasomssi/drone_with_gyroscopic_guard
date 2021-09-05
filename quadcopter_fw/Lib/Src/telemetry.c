/**
 * @file   telemetry.c
 * @brief  communicate between quadcopter and computer
 * @author mokhwasomssi
 * @date   2021-08-30
 */


#include "telemetry.h"


void telemetry_init()
{
    nrf24l01p_tx_init(2500, _1Mbps);
}


void telemetry_tx_angle(angle_t current_angle)
{
    int8_t angle[3] = { 0, 0, 0 };
    
    angle[0] = (int8_t)(current_angle.roll);
    angle[1] = (int8_t)(current_angle.pitch);
    angle[2] = (int8_t)(current_angle.yaw);

    nrf24l01p_tx_transmit(angle, 3);
}