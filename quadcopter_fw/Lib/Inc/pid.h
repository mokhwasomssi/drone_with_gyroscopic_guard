/**
 * @file   pid.h
 * @brief  calculate motor value
 * @author mokhwasomssi
 * @date   2021-09-12
 */


#ifndef __PID_H__
#define __PID_H__


#include "imu.h"
#include "rc.h"


extern angle_t my_pid_value;


/* Main Functions */
void pid_init();
void pid_angle();

#endif /* __PID_H__ */