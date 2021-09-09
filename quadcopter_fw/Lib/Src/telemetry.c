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

void telemetry_update()
{
    // 현재 각도 송신
    // 현재 명령 각도 송신
    // pid 게인 값 수신 (게인 값 변경 용이)
}


void telemetry_tx_angle(angle_t current_angle)
{
    int8_t angle[6] = { 0, };
    
    angle[0] = (int8_t)(current_angle.roll);
    angle[1] = (int8_t)(current_angle.pitch);
    angle[2] = (int8_t)(current_angle.yaw);

    nrf24l01p_tx_transmit(angle, 3);
}
