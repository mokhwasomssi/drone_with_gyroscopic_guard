/**
 * @file   ibus.h
 * @brief  ibus is a Flysky RC receiver protocol
 * @author mokhwasomssi
 * @date   2021-02-04
 */


#ifndef __IBUS_H__
#define __IBUS_H__


#include "usart.h"              // header from stm32cubemx code generate
#include <stdbool.h>


/* User configuration */
#define IBUS_UART				(&huart1)


/* Defines */
#define IBUS_LENGTH				0x20	// 32 bytes
#define IBUS_COMMAND40			0x40	// Command to set servo or motor speed is always 0x40
#define IBUS_MAX_CHANNLES		14


/* Main Functions */
void ibus_init();
bool ibus_read(uint16_t ibus_channel[], uint8_t ch_num);


/* Sub Functions */
bool ibus_is_valid();
bool ibus_checksum();
void ibus_update(uint16_t ibus_channel[], uint8_t ch_num);
bool is_ibus_lost();
void ibus_lost_flag_clear();

#endif /* __IBUS_H__ */
