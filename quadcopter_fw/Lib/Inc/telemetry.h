/**
 * @file   telemetry.h
 * @brief  communicate between quadcopter and computer
 * @author mokhwasomssi
 * @date   2021-08-30
 */


#ifndef __TELEMETRY_H__
#define __TELEMETRY_H__


#include "nrf24l01p.h"
#include "angle.h"


void telemetry_init();
void telemetry_tx_angle(angle_t current_angle);
void telemetry_tx_rc_command();
void telemetry_rx_pid_gain();


#endif /* __TELEMETRY_H__ */