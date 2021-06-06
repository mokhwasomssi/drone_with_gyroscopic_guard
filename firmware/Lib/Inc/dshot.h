/*
 * dshot.h
 *
 *
 *  Created on: 2021. 1. 27.
 *      Author: mokhwasomssi
 * 
 */


#ifndef _DSHOT_H_
#define _DSHOT_H_


#include "tim.h"    // header from stm32cubemx code generate


/* user pin setting */
// MOTOR1 : PA3
#define MOTOR_1_TIM             (&htim5)
#define MOTOR_1_TIM_CHANNEL     TIM_CHANNEL_4

// MOTOR2 : PA2
#define MOTOR_2_TIM             (&htim2)
#define MOTOR_2_TIM_CHANNEL     TIM_CHANNEL_3

// MOTOR3 : PA0
#define MOTOR_3_TIM             (&htim2)
#define MOTOR_3_TIM_CHANNEL     TIM_CHANNEL_1

// MOTOR4 : PA1
#define MOTOR_4_TIM             (&htim5)
#define MOTOR_4_TIM_CHANNEL     TIM_CHANNEL_2


/* definition */
#define NUM_OF_MOTORS          4    // quadcopter

#define MHZ_TO_HZ(x) ((x) * 1000000)

#define DSHOT600_HZ     MHZ_TO_HZ(12)
#define DSHOT300_HZ     MHZ_TO_HZ(6)
#define DSHOT150_HZ     MHZ_TO_HZ(3)

#define MOTOR_BIT_0            7
#define MOTOR_BIT_1            14
#define MOTOR_BITLENGTH        20

#define DSHOT_FRAME_SIZE       16
#define DSHOT_DMA_BUFFER_SIZE   18 /* resolution + frame reset (2us) */

#define DSHOT_MIN_THROTTLE       48
#define DSHOT_MAX_THROTTLE     2047
#define DSHOT_RANGE (DSHOT_MAX_THROTTLE - DSHOT_MIN_THROTTLE)


/* enumeration */
typedef enum
{
    DSHOT150,
    DSHOT300,
    DSHOT600

} dshot_type_e;


/* structure */
typedef struct dshot_handle_s
{
	TIM_HandleTypeDef* 	dshot_timer;
	uint32_t 			channel;			
	
	uint16_t 			value;	// motor speed
	bool 				request_telemetry;

	uint16_t 			packet;
	uint32_t 			dshot_dmabuffer[DSHOT_DMA_BUFFER_SIZE];

} dshot_handle_t;


/* variable */
dshot_handle_t dshot_handle[4];


/* functions */
void dshot_hardware_config(); // hardware configuration is done by cubemx and this function.

uint32_t dshot_choose_type(dshot_type_e dshot_type);

void dshot_set_timer(dshot_handle_t *dshot_handle_array, dshot_type_e dshot_type);

void dshot_init(dshot_handle_t *dshot_handle_array, dshot_type_e dshot_type);

void dshot_prepare_packet(dshot_handle_t *dshot_handle, uint16_t value);

void dshot_packet_to_pwm(dshot_handle_t *dshot_handle);

void dshot_dma_start_hal(dshot_handle_t *dshot_handle);

void dshot_dma_start(TIM_HandleTypeDef* dshot_timer, uint32_t channel, uint32_t *pData, uint16_t length);

void dshot_write(dshot_handle_t *dshot_handle_array, uint16_t value, uint8_t index);

void dshot_write_all(dshot_handle_t *dshot_handle_array, uint16_t *value);


#endif /* _DSHOT_H_ */
