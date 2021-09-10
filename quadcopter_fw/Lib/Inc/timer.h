/**
 * @file   timer.h
 * @brief  
 * @author mokhwasomssi
 * @date   2021-09-10
 */


#ifndef __TIMER_H__
#define __TIMER_H__


#include "tim.h"
#include <stdbool.h>


#define TIMER1                  (&htim10)
#define TIMER2                  (&htim11)


typedef uint16_t us;


/* Main Functions */
void timer_init();

void timer1_start();
us   timer1_end();

void tiemr2_start();
us   timer2_end();

#endif /* __TIMER_H__ */
