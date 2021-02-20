/*
 * flysky_ibus.c
 *
 * This library was written by referring to "https://github.com/bmellink/IBusBM"
 *
 *  Created on: Feb 4, 2021
 *      Author: mokhwasomssi
 */

#include "flysky_ibus.h"

uint8_t ibus_buffer[32] = {0};
//uint16_t channel[IBUS_USER_CHANNELS] = {0};


void ibus_init()
{
	//uint8_t ibus_buffer[32] = {0};
	HAL_UART_Receive_IT(IBUS_UART, ibus_buffer, 32);
}


void ibus_read_channel(channel *channel)
{
	//uint8_t ibus_buffer[32] = {0};
	//HAL_UART_Receive_IT(IBUS_UART, ibus_buffer, 32);

	uint16_t channel_buffer[IBUS_MAX_CHANNLES] = {0};
	uint16_t checksum_cal, checksum_ibus;

	// is it ibus?
	if(ibus_buffer[0] == IBUS_LENGTH && ibus_buffer[1] == IBUS_COMMAND40)
	{
		checksum_cal = 0xffff - ibus_buffer[0] - ibus_buffer[1];

		// data parsing
		for(int i = 0; i < IBUS_MAX_CHANNLES; i++)
		{
			// little endian
			channel_buffer[i] = (uint16_t)(ibus_buffer[i * 2 + 3] << 8 | ibus_buffer[i * 2 + 2]);
			
			// checksum from user calculation
			checksum_cal = checksum_cal - ibus_buffer[i * 2 + 3] - ibus_buffer[i * 2 + 2];
		}

		// checksum from received data
		checksum_ibus = ibus_buffer[31] << 8 | ibus_buffer[30];

		// compare checksum 
		if(checksum_cal == checksum_ibus) 
		{
			// return validated channel data
			for(int ch_index = 0; ch_index < IBUS_USER_CHANNELS; ch_index++)
			{
				channel[ch_index] = channel_buffer[ch_index];
			}
		}
	}

	HAL_UART_Receive_IT(IBUS_UART, ibus_buffer, 32);
}

