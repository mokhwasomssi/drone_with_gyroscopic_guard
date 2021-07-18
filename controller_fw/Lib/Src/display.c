/*
 *  display.c
 *
 *  Created on: 2021. 7. 16.
 *      Author: mokhwasomssi
 *
 */


#include "display.h"

static char* convert_stick_value_to_string(uint16_t stick_value)
{
    static char string_value[5];

    if(stick_value == 0)
    {
        for(int i = 0; i < 3; i++)
        {
            string_value[i] = ' ';
        }

        string_value[3] = '0';
    }

    else
    {
        int a = 1000;
        int b = 0;

        for(int i = 0; i < 4; i++)
        {
            if(stick_value < a)
                b++;

            a /= 10;
        }

        for(int i = 3; i >= 0; i--)
        {
            if(i < b)
            {
                string_value[i] = ' ';
            }
            else
            {
                string_value[i] = stick_value % 10 + '0';
            }

            stick_value /= 10;
        }
    }
    
    string_value[4] = '\0';

    return string_value;
}

void display_joystick_value()
{

    ssd1306_set_cursor(0, 0);
    ssd1306_write_string(font11x18, "Roll :");
    ssd1306_write_string(font11x18, convert_stick_value_to_string(stick_roll));

    ssd1306_set_cursor(0, 18);
    ssd1306_write_string(font11x18, "Pitch:");
    ssd1306_write_string(font11x18, convert_stick_value_to_string(stick_pitch));

    ssd1306_update_screen();

}

