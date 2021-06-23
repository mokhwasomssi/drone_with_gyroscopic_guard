/*
 * battery_monitor.h
 * 
 *  Created on: Apr 15, 2021
 *      Author: mokhwasomssi
 * 
 *  Circuit: Voltage distribution and Voltage follower.
 * 
 */

#ifndef _VOLTAGE_MONITOR_H_
#define _VOLTAGE_MONITOR_H_


#include "adc.h"


#define R1 470000
#define R2 100000


void battery_monitor_init();
void battery_monitor_read();

#endif /* _VOLTAGE_MONITOR_H_ */
