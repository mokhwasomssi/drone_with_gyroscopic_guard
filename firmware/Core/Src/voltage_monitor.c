/*
 * voltage_monitor.c
 *
 *  Created on: Apr 15, 2021
 *      Author: mokhwasomssi
 * 
 */

#include "voltage_monitor.h"


cirqueue adcqueue;

int adc_average = 0;
int adc_prev_average = 0;
uint32_t adc_value = 0;


void init_queue(cirqueue* queue, size n)
{
    queue->rear = 0;
    queue->front = 0;
    queue->data = (element *)malloc(sizeof(element) * n);
}

element enqueue(cirqueue* queue, size n, element data)
{
    queue->rear = (queue->rear + 1) % n;
    queue->data[queue->rear] = data;

    return queue->data[queue->rear];
}

element dequeue(cirqueue* queue, size n)
{
    queue->front = (queue->front + 1) % n;
    return queue->data[queue->front];
}

bool is_full(cirqueue* queue, size n)
{
    if( (queue->rear + 1) % n == queue->front )
        return true;

    else
        return false;
}

bool is_empty(cirqueue* queue)
{
    if(queue->front == queue->rear)
        return true;
    else
        return false;
}

void init_voltage_monitor(float* battery_voltage, size n)
{
    init_queue(&adcqueue, n);
    HAL_ADC_Start_DMA(ADC_VOLTAGE_MONITOR, &adc_value, 1);

    HAL_Delay(100);

    while(!is_full(&adcqueue, n))
        adc_average += enqueue(&adcqueue, n, adc_value);

    adc_average /= (n - 1);
}

// moving average filiter
// X_k_avg = X_k-1_avg + (X_k - X_k-n) / n
int moving_average_filiter_voltage_monitor(size n)
{
    int diff;
    element oldest; 
    element latest; 

    oldest = dequeue(&adcqueue, n);
    latest = enqueue(&adcqueue, n, adc_value);

    diff = (latest - oldest);
    diff /= (n - 1);

    adc_prev_average = adc_average;
    adc_average = adc_prev_average + diff;

    return adc_average;
}

float read_battery_voltage(size n)
{
    int raw_data;
    float battery_voltage;

    raw_data = moving_average_filiter_voltage_monitor(n);
    battery_voltage = 0.000806 * 5.7 * raw_data;

    return battery_voltage;
}
