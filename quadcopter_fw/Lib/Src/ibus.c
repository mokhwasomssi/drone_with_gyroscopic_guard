/**
 * @file   ibus.c
 * @brief  ibus is a Flysky RC receiver protocol
 * @author mokhwasomssi
 * @date   2021-02-04
 */


#include "ibus.h"


/* Static variables */
static uint8_t uart_rx_buffer[IBUS_LENGTH] = {0};
static uint8_t ibus_lost_flag = 0;


/* Main Functions */
void ibus_init()
{
	HAL_UART_Receive_DMA(IBUS_UART, uart_rx_buffer, 32);
}

/**
 * @brief Check ibus is valid and parse ibus data from uart dma buffer
 */
bool ibus_read(uint16_t ibus_channel[], uint8_t ch_num)
{
	if(!ibus_is_valid()) 
		return false;

	if(!ibus_checksum())
		return false;

	ibus_update(ibus_channel, ch_num);
	return true;
}


/* Sub Functions */
bool ibus_is_valid()
{
	// is it ibus?
	return (uart_rx_buffer[0] == IBUS_LENGTH && uart_rx_buffer[1] == IBUS_COMMAND40);
}

bool ibus_checksum()
{
 	uint16_t checksum_cal = 0xffff;
	uint16_t checksum_ibus;

	for(int i = 0; i < 30; i++)
		checksum_cal -= uart_rx_buffer[i];

	checksum_ibus = uart_rx_buffer[31] << 8 | uart_rx_buffer[30]; // checksum value from ibus
	return (checksum_ibus == checksum_cal);
}

void ibus_update(uint16_t ibus_channel[], uint8_t ch_num)
{
	for(int i = 0, j = 2; i < ch_num; i++, j += 2)
	{
		ibus_channel[i] = uart_rx_buffer[j + 1] << 8 | uart_rx_buffer[j];
	}
}

bool is_ibus_lost()
{
	uint8_t max_lost_flag = 20;

	if(max_lost_flag > ibus_lost_flag)
	{
		ibus_lost_flag++;
		return false;
	}

	else
		return true;
}

void ibus_lost_flag_clear()
{
	ibus_lost_flag = 0;
}