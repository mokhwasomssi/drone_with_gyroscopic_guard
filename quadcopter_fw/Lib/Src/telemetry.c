/**
 * @file   telemetry.c
 * @brief  communicate between quadcopter and computer
 * @author mokhwasomssi
 * @date   2021-08-30
 */


#include "telemetry.h"


static uint8_t telemetry_tx_buffer[NRF24L01P_PAYLOAD_LENGTH];


/* Static Functions */
static void put_angle();
static void put_rc_command();


/* Main Functions */
void telemetry_init()
{
    nrf24l01p_tx_init(2500, _1Mbps);
}

void telemetry_update()
{
    led_blue_off(); //telemetry indicator

    put_angle();
    put_rc_command();
    nrf24l01p_tx_transmit(telemetry_tx_buffer);
    // pid 게인 값 수신 (게인 값 변경 용이)
}


/* Static Functions */
static void put_angle()
{
    telemetry_tx_buffer[0] = (int8_t)(my_current_angle.roll);
    telemetry_tx_buffer[1] = (int8_t)(my_current_angle.pitch);
    telemetry_tx_buffer[2] = (int8_t)(my_current_angle.yaw);
}

static void put_rc_command()
{
    telemetry_tx_buffer[3] = (int8_t)(my_rc_command.roll);
    telemetry_tx_buffer[4] = (int8_t)(my_rc_command.pitch);
    telemetry_tx_buffer[5] = (int8_t)(my_rc_command.yaw);
}
