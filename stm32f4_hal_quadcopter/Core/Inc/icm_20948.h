/*
*
* 	icm_20948.h
*
*  	Created on: Dec 26, 2020
*      Author: mokhwasomssi
*
*   gyro and accel 		: icm-20948
*	magnatometer 		: ak09916
*   Breakout Board		: SparkFun 9Dof IMU Breakout - ICM-20948 (Qwiic)
*
*/

#ifndef _ICM_20948_H_
#define	_ICM_20948_H_

#include "icm_20948_register.h"
#include "stm32f4xx_hal.h"
#include "main.h"
#include "spi.h"

#include <math.h>

#define ALPHA				0.96

/* User Configuration */
#define SPI_ICM20948 		(&hspi1)			// SPI Number
#define CS_PIN_PORT			GPIOA				// CS Pin
#define CS_PIN_NUMBER		GPIO_PIN_4
/* User Configuration */


// icm20948 data structure 
typedef struct icm20948_s
{
	// unit lsb
	int16_t gyro_lsb_x;		// gyroscope output data
	int16_t gyro_lsb_y;
	int16_t gyro_lsb_z;

	// unit dps
	double gyro_dps_x;		
	double gyro_dps_y;
	double gyro_dps_z;

	// unit lsb
	int16_t accel_lsb_x;	// acceleromoter output data
	int16_t accel_lsb_y;
	int16_t accel_lsb_z;

	// unit g
	double accel_g_x;		
	double accel_g_y;
	double accel_g_z;

} icm20948_t;

typedef struct angle
{
	// from gyro
	double gyro_angle_x;
	double gyro_angle_y;
	double gyro_angle_z;

	// from accel
	double accel_angle_x;
	double accel_angle_y;
	double accel_angle_z;

	// from complementary filter
	double angle_x;
	double angle_y;
	double angle_z;

} angle_t;

// ak09916 data structure
typedef struct ak09916_s
{
	// unit lsb
	int16_t mag_x;
	int16_t mag_y;
	int16_t mag_z;

} ak09916_t;

// user bank
typedef enum userbank_e
{
	userbank_0		= 0 << 4,
	userbank_1		= 1 << 4,
	userbank_2		= 2 << 4,
	userbank_3		= 3 << 4
} userbank_e;


// cs state
void cs_high();
void cs_low();

// user bank
void select_user_bank(userbank_e ub);

// spi
void icm20948_read(uint8_t regaddr, uint8_t len);
void icm20948_write(uint8_t regaddr, uint8_t data);

// auxiliary i2c
void ak09916_read(uint8_t regaddr, uint8_t len);
void ak09916_wrtie(uint8_t regaddr, uint8_t data);

// check sensor id
uint8_t whoami_icm20948();	// return : 0xEA
uint8_t whoami_ak09916();	// return : 0x09

// initialize
void icm20948_init();
void ak09916_init();

// read gyro
void read_gyro_lsb(icm20948_t* icm20948);
void read_gyro_dps(icm20948_t* icm20948);

// read aceel
void read_accel_lsb(icm20948_t* icm20948);
void read_accel_g(icm20948_t* icm20948);

// read mag
void read_mag_lsb(ak09916_t* ak09916);

// calibrate gyro and accel
void calibrate_icm20948(icm20948_t* icm20948, uint16_t samples);

// complementary filter
void complementary_filter(icm20948_t *icm20948, angle_t *angle);


// registers
typedef enum _USER_CTRL
{
	DMP_EN 			= 1 << 7,		// Enables DMP features
	FIFO_EN 		= 1 << 6,		// Enable FIFO operation mode
	I2C_MST_EN 		= 1 << 5,		// Enable the I2C Master I/F module
	I2C_IF_DIS		= 1 << 4,		// Reset I2C Slave module
	DMP_RST 		= 1 << 3,		// Reset DMP module
	SRAM_RST 		= 1 << 2,		// Reset SRAM module
	I2C_MST_RST		= 1 << 1		// Reset I2C Master module
} USER_CTRL;

/* Enumeration ICM-20948 */
typedef enum _PWR_MGNT_1			// Reset Value : 0x41
{
	DEVICE_RESET 	= 1 << 7,		// Reset the internal registers and restores the default settings.
	SLEEP 			= 1 << 6,		// When set, the chip is set to sleep mode
	WAKE			= 0 << 6,		// Clearing the bit wakes the chip from sleep mode.
	LP_EN 			= 1 << 5,
	TEMP_DIS		= 1 << 3,
	CLKSEL 			= 1
} PWR_MGNT_1;

typedef enum _GYRO_SMPLRT_DIV
{
	Gyro_ODR_1100Hz = 0,			// Output Data Rate = 1.1kHz / (1 + GYRO_SMPLRT_DIV)
	Gyro_ODR_100Hz = 10,
	Gyro_ODR_10Hz = 109
} GYRO_SMPLRT_DIV;

typedef enum _GYRO_CONFIG_1			// Reset Value : 0x01
{
	GYRO_DLPFCFG = 0,				// Gyro low pass filter configuration (Table 16)
	GYRO_FS_SEL_250dps = 0,			// Gyro Full Scale Select
	GYRO_FS_SEL_500dps = 2,
	GYRO_FS_SEL_1000dps = 4,
	GYRO_FS_SEL_2000dps = 6,
	GYRO_FCHOICE = 1				// Enable gyro DLPF
} GYRO_CONFIG_1;

typedef enum _ACCEL_SMPLRT_DIV_2
{
	Accel_ODR_1100Hz = 0,			// Output Data Rate = 1.1kHz / (1 + ACCEL_SMPLRT_DIV)
	Accel_ODR_100Hz = 10,
	Accel_ODR_10Hz = 109
} ACCEL_SMPLRT_DIV_2;

typedef enum _ACCEL_CONFIG			// Reset Value : 0x01
{
	ACCEL_DLPFCFG = 0,				// accel low pass filter configuration (Table 18)
	ACCEL_FS_SEL_2g = 1,
	ACCEL_FS_SEL_4g = 3,
	ACCEL_FS_SEL_8g = 5,
	ACCEL_FS_SEL_16g = 7,
	ACCEL_FCHOICE = 1				// Enable accel DLPF
} ACCEL_CONFIG;



typedef enum _I2C_MST_ODR_CONFIG
{
	I2C_MST_ODR_CONFIG = 0					// ODR configuration for external sensor when gyroscope and accelerometer are disabled.
									        // ODR = 1.1kHz / ( 2 ^(odr_config[3:0]) )
} _I2C_MST_ODR_CONFIG;

typedef enum _I2C_MST_CTRL
{
	MULT_MST_EN				= 1 << 7,				// Enables multi-master capability
	I2C_MST_P_NSR			= 1 << 4,				// This bit controls the I2C Master's transition
	I2C_MST_CLK				= 7						// Sets I2C master clock frequency (Table 23)
} I2C_MST_CTRL;

typedef enum _I2C_MST_DELAY_CTRL
{
	DELAY_ES_SHADOW			= 1 << 7,				// Delays shadowing of external sensor data until all data is received
	I2C_SLV4_DELAY_EN 		= 1 << 4,				// When enabled, slave 0-4 will only be accessed 1/(1+I2C_SLC4_DLY) samples
	I2C_SLV3_DELAY_EN 		= 1 << 3,				// as determined by I2C_MST_ODR_CONFIG
	I2C_SLV2_DELAY_EN 		= 1 << 2,
	I2C_SLV1_DELAY_EN 		= 1 << 1,
	I2C_SLV0_DELAY_EN 		= 1 << 0
} I2C_MST_DELAY_CTRL;

typedef enum _I2C_SLV_CTRL
{
	I2C_SLV_EN				= 1 << 7,		// Enable reading data from this slave.
	I2C_SLV_BYTE_SW 		= 1 << 6,		// Swap bytes when reading both the low and high byte of a word.
	I2C_SLV_REG_DIS 		= 1 << 5,		// When set, transaction does not write a register value.
	I2C_SLV_GRP 			= 1 << 4,		// External sensor data typically comes in as groups of two bytes
	I2C_SLV_LENG_6bytes 	= 6				// Number of bytes to be read from I2C slave
} I2C_SLV_CTRL;
/* Enumeration ICM-20948 */


/* Enumeration AK09916 */
typedef enum _CNTL2
{
	Power_down_mode = 0b00000,
	Single_measurement_mode = 0b00001,			// Sensor is measured for one time
	Continuous_measurement_mode_1 = 0b00010,	// Sensor is measured periodically in 10Hz
	Continuous_measurement_mode_2 = 0b00100,	// ... 20Hz
	Continuous_measurement_mode_3 = 0b00110,	// ... 50Hz
	Continuous_measurement_mode_4 = 0b01000,	// ... 100Hz
	Self_test_mode = 0b10000
} CNTL2;




#endif	/* _ICM_20948_H_ */






























