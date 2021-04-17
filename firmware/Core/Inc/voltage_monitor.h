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

typedef uint32_t element;
typedef int size;

typedef struct cirqueue
{
    int rear;
    int front;
    element* data;
} cirqueue;


void init_voltage_monitor(float* battery_voltage, size n);
float read_battery_voltage(size n);

#endif /* _VOLTAGE_MONITOR_H_ */
