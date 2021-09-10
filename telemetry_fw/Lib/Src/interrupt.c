/**
 * @file   interrupt.c
 * @brief  define interrupt callback functions.
 * @author mokhwasomssi
 * @date   2021-09-10
 */


#include "interrupt.h"


/**
 * @brief nrf24l01+ data ready interrupt
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == NRF24L01P_IRQ_PIN_NUMBER)
	{
		led_blue_on(); //telemetry indicator
		telemetry_update();
	}
}