/**
 * @file   pid.c
 * @brief  calculate motor value
 * @author mokhwasomssi
 * @date   2021-09-12
 */


#include "pid.h"


double kp = 1;
double ki = 0.5;
double kd = 0.1;



void pid_init()
{

}

/**
 * @brief pid calculation to get new motor value using current angle
 * @param[in] current_angle put current angle
 * @param[in] target_angle 
 * @param[out] pid_value 
 */
void pid_calculate(angle_t current_angle, gyro_t current_gyro, double dt, angle_t target_angle, angle_t* pid_value)
{
    double roll_error;
    static double roll_integral, roll_integral_prior;
    double roll_derivative;

    roll_error = target_angle.roll - current_angle.roll;
    roll_derivative = -current_gyro.x;
    roll_integral = roll_integral_prior + roll_error*dt;

    pid_value->roll = (kp*roll_error) + (ki*roll_integral) + (kd*roll_derivative);

    roll_integral_prior = roll_integral;
}

/*
void pid_angle()
{
    pid_roll_angle(double kp, double ki, double kd);
    pid_pitch_angle(double kp, double ki, double kd);
    pid_yaw_angle(double kp, double ki, double kd);
}
*/

// void pid_roll_angle(double kp, double ki, double kd);
// void pid_pitch_angle(double kp, double ki, double kd);
// void pid_yaw_angle(double kp, double ki, doble kd);