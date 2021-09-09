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

#define TIMER_1                  (&htim10)
#define TIMER_2                  (&htim11)
typedef uint16_t us;


/* Main Functions */
void timer_init();
us   get_timer_1_counter();
void set_timer_1_counter_zero();
us   get_timer_2_counter();
void set_timer_2_counter_zero();


#endif /* __TIMER_H__ */
