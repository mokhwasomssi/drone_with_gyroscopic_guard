/*
 * voltage_monitor.h
 *
 *  Created on: Apr 15, 2021
 *      Author: mokhwasomssi
 * 
 */

#ifndef _VOLTAGE_MONITOR_H_
#define _VOLTAGE_MONITOR_H_

#include "user_pin_setting.h"
#include "stm32f4xx_hal.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


void init_voltage_monitor();
void read_battery_voltage(float* battery_voltage);

#endif /* _VOLTAGE_MONITOR_H_ */
