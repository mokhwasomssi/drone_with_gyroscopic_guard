/*
 * joystick.c
 *
 *
 *  Created on: 2021. 7. 16.
 *      Author: mokhwasomssi
 *
 */


#include "joystick.h"


static uint32_t stick_adc_value[4];

uint16_t stick_roll;
uint16_t stick_pitch;
uint16_t stick_throttle;
uint16_t stick_yaw;


void joystick_init()
{
    HAL_ADC_Start_DMA(JOYSTICK_ADC, (uint32_t*)stick_adc_value, 4);
}

static void joystick_set_value()
{
    // roll
    if(stick_adc_value[0] / 4 > 1000)
        stick_roll = 1000;
    else
        stick_roll = stick_adc_value[0] / 4;

    // pitch, 18 is offset
    if((stick_adc_value[1] / 4) > 1000)
        stick_pitch = 1000;
    else
        stick_pitch = (stick_adc_value[1] / 4);

    // throttle
    if(stick_adc_value[2] / 4 > 1000)
        stick_throttle = 1000;
    else
        stick_throttle = stick_adc_value[2] / 4;

    // yaw
    if(stick_adc_value[3] / 4 > 1000)
        stick_yaw = 1000;
    else
        stick_yaw = stick_adc_value[3] / 4;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    joystick_set_value();
}