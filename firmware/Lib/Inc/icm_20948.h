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


#include "icm_20948_reg.h"
#include "spi.h"


typedef enum unit_e
{
	lsb,
	dps,
	g,
	deg,
	uT

} unit_e;

// user bank
typedef enum userbank_e
{
	userbank_0		= 0 << 4,
	userbank_1		= 1 << 4,
	userbank_2		= 2 << 4,
	userbank_3		= 3 << 4
} userbank_e;

typedef enum gyro_fs_e
{
	fs_250dps = 0,
	fs_500dps = 2,
	fs_1000dps = 4,
	fs_2000dps = 6

} gyro_fs_e;

typedef enum accel_fs_e
{
	fs_2g = 1,
	fs_4g = 3,
	fs_8g = 5,
	fs_16g = 7

} accel_fs_e;

typedef enum op_mode_e
{
	power_down 				 = 0,
	single_measure 			 = 1,
	continuous_measure_10hz  = 2,
	continuous_measure_20hz  = 4,
	continuous_measure_50hz  = 6,
	continuous_measure_100hz = 8,
	self_test 				 = 16

} op_mode_e;

typedef struct gyro_data_t
{
	float x;
	float y;
	float z;

} gyro_data_t;

typedef struct accel_data_t
{
	float x;
	float y;
	float z;

} accel_data_t;

typedef struct mag_data_t
{
	float x;
	float y;
	float z;

} mag_data_t;


// cs state
void cs_high();
void cs_low();

// user bank
void select_user_bank(userbank_e ub);

// read / write
void read_icm20948(uint8_t regaddr, uint8_t len);
void write_icm20948(uint8_t regaddr, uint8_t data);

// auxiliary i2c
void read_ak09916(uint8_t regaddr, uint8_t len);
void write_ak09916(uint8_t regaddr, uint8_t data);

// check sensor id
uint8_t whoami_icm20948();	// return : 0xEA
uint8_t whoami_ak09916();	// return : 0x09

// initialize
void init_icm20948(gyro_fs_e gyro_fs, uint16_t gyro_odr_hz, accel_fs_e accel_fs, uint16_t accel_ord_hz);
void init_ak09916(op_mode_e op_mode);

// read sensor data
void read_gyro(gyro_data_t* gyro_data, unit_e unit);
void read_accel(accel_data_t* accel_data, unit_e unit);
void read_mag(mag_data_t* mag_data, unit_e unit);

// calibrate gyro and accel
//void calibrate_icm20948(icm20948_t* icm20948, uint16_t samples);

// complementary filter
//void complementary_filter(icm20948_t *icm20948, angle_t *angle);



#endif	/* _ICM_20948_H_ */




