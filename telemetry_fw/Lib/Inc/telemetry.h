/**
 * @file   telemetry.h
 * @brief  wireless communication between quadcopter and computer
 *         this file is on computer side.
 * @author mokhwasomssi
 * @date   2021-09-10
 */


#ifndef __TELEMETRY_H__
#define __TELEMETRY_H__


#include <stdio.h>
#include "usart.h"
#include "nrf24l01p.h"
#include "led.h"


typedef struct 
{
    int8_t roll;
    int8_t pitch;
    int8_t yaw;
} angle_t;


extern uint8_t telemetry_rx_buffer[NRF24L01P_PAYLOAD_LENGTH];


/* Main Functions */
void telemetry_init();
void telemetry_update();


#endif /* __TELEMETRY_H__ */