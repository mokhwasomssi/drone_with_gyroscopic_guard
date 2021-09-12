/**
 * @file   telemetry.c
 * @brief  wireless communication between quadcopter and computer
 *         this file is on computer side.
 * @author mokhwasomssi
 * @date   2021-09-10
 */


#include "telemetry.h"


uint8_t telemetry_rx_buffer[NRF24L01P_PAYLOAD_LENGTH];
angle_t quadcopter_angle;
angle_t target_angle;


/* Static Functions */
static void get_quadcopter_angle();
static void get_target_angle();
//static void telemetry_printf();


/* Main Functions */
void telemetry_init()
{
    nrf24l01p_rx_init(2500, _1Mbps);
}

/**
 * @brief receive data from quadcopter
 */
void telemetry_update()
{
    nrf24l01p_rx_receive(telemetry_rx_buffer);
    get_quadcopter_angle();
    get_target_angle();
    //telemetry_printf();
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

/**
 * @brief function for using printf
 */
/*
int _write(int file, char *ptr, int len)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, 500);
	return len;
}
*/

/**
 * @brief print received data
 */
/*
static void telemetry_printf()
{
    printf("roll : %d \t pitch : %d \n", quadcopter_angle.roll, quadcopter_angle.pitch);
}
*/