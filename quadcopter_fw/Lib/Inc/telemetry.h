/**
 * @file   telemetry.h
 * @brief  communication between quadcopter and computer
 * @author mokhwasomssi
 * @date   2021-08-30
 */


#include "nrf24l01p.h"
#include "angle.h"


void transmit_angle(angle_t current_angle);
