/*
 * battery_monitor.c
 * 
 *  Created on: Apr 15, 2021
 *      Author: mokhwasomssi
 * 
 *  Circuit: Voltage distribution and Voltage follower.
 * 
 */


#include "battery_monitor.h"


uint32_t    battery_adc;
float       battery_voltage;


void battery_monitor_init()
{
    HAL_ADC_Start_DMA(&hadc1, &battery_adc, 1);
    HAL_Delay(100);
}

void battery_monitor_read()
{
    battery_voltage = (3.3/4095) * 5.7 * battery_adc;
}

