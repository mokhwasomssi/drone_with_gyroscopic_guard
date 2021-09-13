/**
 * @file   pid.c
 * @brief  calculate motor value
 * @author mokhwasomssi
 * @date   2021-09-12
 */


#include "pid.h"


double roll_kp = 1.0;
double roll_ki = 0.7;
double roll_kd = 0.3;

double pitch_kp = 1.5;
double pitch_ki = 1.1;
double pitch_kd = 0.5;

double yaw_kp;
double yaw_ki;
double yaw_kd;


angle_t my_pid_value;


/* Static Functions */
static void pid_roll_angle();
static void pid_pitch_angle();


/* Main Functions */
void pid_init()
{

}

void pid_angle()
{
    pid_roll_angle();
    pid_pitch_angle();
}


/* Static Functions */
static void pid_roll_angle()
{
    double        roll_error;
    static double roll_integral, roll_integral_prior;
    double        roll_derivative;

    double dt = imu_sampling_time*0.000001;

    roll_error      = my_target_angle.roll - my_current_angle.roll;
    roll_derivative = -my_current_gyro.x;
    roll_integral   = roll_integral_prior + roll_error*dt;

    // calculate pid
    my_pid_value.roll = (roll_kp*roll_error) + (roll_ki*roll_integral) + (roll_kd*roll_derivative);

    roll_integral_prior = roll_integral;
}

static void pid_pitch_angle()
{
    double        pitch_error;
    static double pitch_integral, pitch_integral_prior;
    double        pitch_derivative;

    double dt = imu_sampling_time*0.000001;

    pitch_error      = my_target_angle.pitch - my_current_angle.pitch;
    pitch_derivative = -my_current_gyro.y;
    pitch_integral   = pitch_integral_prior + pitch_error*dt;

    // calculate pid
    my_pid_value.pitch = (pitch_kp*pitch_error) + (pitch_ki*pitch_integral) + (pitch_kd*pitch_derivative);

    pitch_integral_prior = pitch_integral;
}


// void pid_yaw_angle(double kp, double ki, doble kd);