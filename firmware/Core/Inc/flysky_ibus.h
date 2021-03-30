/*
 * flysky_ibus.h
 *
 * This library was written by referring to "https://github.com/bmellink/IBusBM"
 *
 *  Created on: Feb 4, 2021
 *      Author: mokhwasomssi
 */


#ifndef _FLYSKY_IBUS_H_
#define _FLYSKY_IBUS_H_

#include "stm32f4xx_hal.h"
#include "usart.h"

/* User configuration */
#define IBUS_UART				(&huart1)
#define IBUS_UART_INSTANCE		(USART1)
#define IBUS_USER_CHANNELS		6			// Use 6 channels
/* User configuration */

#define IBUS_LENGTH				0x20	// 32 bytes
#define IBUS_COMMAND40			0x40	// Command to set servo or motor speed is always 0x40
#define IBUS_MAX_CHANNLES		14

typedef enum
{   
    IBUS_OK,
    IBUS_NOT_OK,
    IBUS_READY,
    IBUS_MISSING, // fail-safe
    IBUS_DATA_READY,
    IBUS_DATA_GOOD,
    IBUS_DATA_NOT_GOOD,

} ibus_state;

typedef uint16_t rc_channel_a;

ibus_state ibus_init();
ibus_state ibus_read_channel(rc_channel_a *channel);
//ibus_state ibus_software_failsafe(uint8_t *ibus_state, uint8_t *ibus_check);

#endif /* _FLYSKY_IBUS_H_ */

