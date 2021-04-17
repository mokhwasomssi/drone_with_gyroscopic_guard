/*
 * voltage_monitor.c
 *
 *  Created on: Apr 15, 2021
 *      Author: mokhwasomssi
 * 
 */

#include "voltage_monitor.h"

uint32_t adc_value;

void init_voltage_monitor()
{
    HAL_ADC_Start_DMA(ADC_VOLTAGE_MONITOR, &adc_value, 1);
    HAL_Delay(100);
}

void read_battery_voltage(float* battery_voltage)
{
    float cal_battery_voltage;

    cal_battery_voltage = (3.3/4095) * 5.7 * adc_value;
    *battery_voltage = cal_battery_voltage;
}
