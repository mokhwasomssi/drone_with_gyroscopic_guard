/**
 * @file   motor.c
 * @brief  
 * @author mokhwasomssi
 * @date   2021-09-04
 */


#include "motor.h"


void motor_init()
{
    dshot_init(DSHOT600); // use dshot as drone esc protocol
}


void motor_update(uint16_t motor_value[])
{
    uint16_t dshot_value[4] = { 0, 0, 0, 0 };

    // convert motor value to dshot value
    for(int i = 0; i < 4; i++)
    {
        if(motor_value[i] == 0) // dshot trottle : 0 (0)
            dshot_value[i] = 0;
        
        else // dshot throttle : 48 - 2047 (1 - 2000)
            dshot_value[i] = 47 + (motor_value[i] * 2);
    }

    dshot_write(dshot_value);
}
