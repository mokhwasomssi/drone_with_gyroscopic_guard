/*
 * flysky_ibus.c
 *
 *  Created on: Feb 4, 2021
 *      Author: mokhwasomssi
 */


#include "flysky_ibus.h"


/* variable */
static uint8_t ibus_buffer[32] = {0};
uint16_t channel[IBUS_USER_CHANNELS] = {0};


void ibus_init()
{
	/* Interrupt mode */
	//HAL_UART_Receive_IT(IBUS_UART, ibus_buffer, 32);

	/* DMA mode */
	HAL_UART_Receive_DMA(IBUS_UART, ibus_buffer, 32);
}


static bool ibus_is_valid()
{
	// is it ibus?
	return (ibus_buffer[0] == IBUS_LENGTH && ibus_buffer[1] == IBUS_COMMAND40);
}


static bool ibus_checksum()
{
 	uint16_t checksum_cal = 0xffff;
	uint16_t checksum_ibus;

	for(int i = 0; i < 30; i++)
	{
		checksum_cal -= ibus_buffer[i];
	}

	checksum_ibus = ibus_buffer[31] << 8 | ibus_buffer[30]; // checksum value from ibus
	
	return (checksum_ibus == checksum_cal);
}


static void ibus_little_endian()
{
	for(int ch_index = 0, bf_index = 2; ch_index < IBUS_USER_CHANNELS; ch_index++, bf_index += 2)
	{
		channel[ch_index] = ibus_buffer[bf_index + 1] << 8 | ibus_buffer[bf_index];
	}
}


bool ibus_read_channel()
{
	if(!ibus_is_valid())
		return false;

	if(!ibus_checksum())
		return false;

	ibus_little_endian();

	/* Interrupt mode */
	//HAL_UART_Receive_IT(IBUS_UART, ibus_buffer, 32);

	/* DMA mode */
	HAL_UART_Receive_DMA(IBUS_UART, ibus_buffer, 32);

	return true;
}
