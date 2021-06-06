/*
 * dshot.h
 *
 *
 *  Created on: 2021. 1. 27.
 *      Author: mokhwasomssi
 *
 */


#include "dshot.h"


uint32_t dshot_choose_type(dshot_type_e dshot_type)
{
	switch (dshot_type)
	{
	case(DSHOT600):
			printf("dshot type : DSHOT600\n");
			return DSHOT600_HZ;
	case(DSHOT300):
		printf("dshot type : DSHOT300\n");
			return DSHOT300_HZ;

	default:
	case(DSHOT150):
			printf("dshot type : DSHOT150\n");
			return DSHOT150_HZ;
	}
}

void dshot_set_timer(dshot_handle_t *dshot_handle_array, dshot_type_e dshot_type)
{
	uint16_t dshot_prescaler;
	uint32_t timer_clock = SystemCoreClock;

	dshot_prescaler = lrintf((float) timer_clock / dshot_choose_type(dshot_type) + 0.01f) - 1;

	/*
	for(int i = 0; i < 4; i++)
	{
		__HAL_TIM_SET_PRESCALER(dshot_handle[i].dshot_timer, dshot_prescaler);
		__HAL_TIM_SET_AUTORELOAD(dshot_handle[i].dshot_timer, MOTOR_BITLENGTH);
	}
	*/

	// motor1
	__HAL_TIM_SET_PRESCALER(MOTOR_1_TIM, dshot_prescaler);
	__HAL_TIM_SET_AUTORELOAD(MOTOR_1_TIM, MOTOR_BITLENGTH);

	// motor2
	__HAL_TIM_SET_PRESCALER(MOTOR_2_TIM, dshot_prescaler);
	__HAL_TIM_SET_AUTORELOAD(MOTOR_2_TIM, MOTOR_BITLENGTH);

	// motor3
	__HAL_TIM_SET_PRESCALER(MOTOR_3_TIM, dshot_prescaler);
	__HAL_TIM_SET_AUTORELOAD(MOTOR_3_TIM, MOTOR_BITLENGTH);

	// motor4
	__HAL_TIM_SET_PRESCALER(MOTOR_4_TIM, dshot_prescaler);
	__HAL_TIM_SET_AUTORELOAD(MOTOR_4_TIM, MOTOR_BITLENGTH);

}

void dshot_init(dshot_handle_t *dshot_handle_array, dshot_type_e dshot_type)
{
	dshot_handle[0].dshot_timer = MOTOR_1_TIM;
	dshot_handle[1].dshot_timer = MOTOR_2_TIM;
	dshot_handle[2].dshot_timer = MOTOR_3_TIM;
	dshot_handle[3].dshot_timer = MOTOR_4_TIM;

	dshot_handle[0].channel = MOTOR_1_TIM_CHANNEL;
	dshot_handle[1].channel = MOTOR_2_TIM_CHANNEL;
	dshot_handle[2].channel = MOTOR_3_TIM_CHANNEL;
	dshot_handle[3].channel = MOTOR_4_TIM_CHANNEL;

	dshot_set_timer(dshot_handle_array, dshot_type);

    // Start the timer channel now.
    // Enabling/disabling DMA request can restart a new cycle without PWM start/stop.
  	HAL_TIM_PWM_Start(MOTOR_1_TIM, MOTOR_1_TIM_CHANNEL);
  	HAL_TIM_PWM_Start(MOTOR_2_TIM, MOTOR_2_TIM_CHANNEL);


	printf("dshot initialized\n");
}

void dshot_prepare_packet(dshot_handle_t *dshot_handle, uint16_t value)
{
	uint16_t packet;
	bool dshot_telemetry = false;

	packet = (value << 1) | (dshot_telemetry ? 1 : 0);

	// compute checksum
	unsigned csum = 0;
	unsigned csum_data = packet;

	for(int i = 0; i < 3; i++)
	{
        csum ^=  csum_data;   // xor data by nibbles
        csum_data >>= 4;
	}

	csum &= 0xf;
	dshot_handle->packet = (packet << 4) | csum;
}

void dshot_packet_to_pwm(dshot_handle_t *dshot_handle)
{
	int i;
	uint16_t packet = dshot_handle->packet;

	for(i = 0; i < 16; i++)
	{
		dshot_handle->dshot_dmabuffer[i] = (packet & 0x8000) ? MOTOR_BIT_1 : MOTOR_BIT_0;
		packet <<= 1;
	}

	dshot_handle->dshot_dmabuffer[i++] = 0;
	dshot_handle->dshot_dmabuffer[i++] = 0;

}

void dshot_dma_start_hal(dshot_handle_t *dshot_handle)
{
	HAL_TIM_PWM_Start_DMA(dshot_handle->dshot_timer, dshot_handle->channel, dshot_handle->dshot_dmabuffer, DSHOT_DMA_BUFFER_SIZE);

}


void dshot_dma_start(TIM_HandleTypeDef *htim, uint32_t channel, uint32_t *pData, uint16_t Length)
{

    switch (channel) 
	{
		case TIM_CHANNEL_1:
			HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC1], (uint32_t)pData, (uint32_t)&htim->Instance->CCR1, Length);
			__HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC1);
			break;

		case TIM_CHANNEL_2:
			HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC2], (uint32_t)pData, (uint32_t)&htim->Instance->CCR2, Length);
			__HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC2);
			break;

		case TIM_CHANNEL_3:
			HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC3], (uint32_t)pData, (uint32_t)&htim->Instance->CCR3,Length);
			__HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC3);
			break;

		case TIM_CHANNEL_4:
			HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC4], (uint32_t)pData, (uint32_t)&htim->Instance->CCR4, Length);
			__HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC4);
			break;
    }
	

}

void dshot_write(dshot_handle_t *dshot_handle_array, uint16_t value, uint8_t index)
{
	dshot_prepare_packet(&dshot_handle[index], value);

	dshot_packet_to_pwm(&dshot_handle[index]);

	//dshot_dma_start_hal(&dshot_handle[index]);

	//dshot_dma_start(dshot_handle[index].dshot_timer, dshot_handle[index].channel, dshot_handle[index].dshot_dmabuffer, 18);
}

void dshot_write_all(dshot_handle_t *dshot_handle_array, uint16_t *value)
{
	for(int i = 0; i < 4; i++)
	{
		dshot_write(&dshot_handle[i], i, value[i]);
	}

}







