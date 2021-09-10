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
#include "imu.h"
#include "rc.h"


/* Main Functions */
void telemetry_init();
void telemetry_update();


#endif /* __TELEMETRY_H__ */