/**
 * @file   telemetry.c
 * @brief  wireless communication between quadcopter and computer
 *         this file is on computer side.
 * @author mokhwasomssi
 * @date   2021-09-10
 */


#include "telemetry.h"


/* Static Functions */
static void get_quadcopter_angle();
static void get_target_angle();


uint8_t telemetry_rx_buffer[NRF24L01P_PAYLOAD_LENGTH];
angle_t quadcopter_angle;
angle_t target_angle;


/* Main Functions */
void telemetry_init()
{
    nrf24l01p_rx_init(2500, _1Mbps);
}

void telemetry_update()
{
    nrf24l01p_rx_receive(telemetry_rx_buffer); // receive data from quadcopter
    get_quadcopter_angle();
    get_target_angle();
    //telemetry_printf();  // print received data
}


/* Static Functions */
static void get_quadcopter_angle()
{
    quadcopter_angle.roll = (int8_t)telemetry_rx_buffer[0];
    quadcopter_angle.pitch = (int8_t)telemetry_rx_buffer[1];
    quadcopter_angle.yaw = (int8_t)telemetry_rx_buffer[2];
}

static void get_target_angle()
{
    target_angle.roll = (int8_t)telemetry_rx_buffer[3];
    target_angle.pitch = (int8_t)telemetry_rx_buffer[4];
    target_angle.yaw = (int8_t)telemetry_rx_buffer[5];
}