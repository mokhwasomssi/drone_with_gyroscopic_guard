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

#include "icm_20948_register.h"
#include "icm_20948.h"


// temporary array
uint8_t tx_buffer[6] = {0};
uint8_t rx_buffer[6] = {0};


// cs state
void cs_high()
{
	HAL_GPIO_WritePin(CS_PIN_PORT, CS_PIN_NUMBER, SET);	
}

void cs_low()
{
	HAL_GPIO_WritePin(CS_PIN_PORT, CS_PIN_NUMBER, RESET);
}

// user bank
void select_user_bank(userbank_e ub)
{
	icm20948_write(B0_REG_BANK_SEL, ub);
}

// spi
void icm20948_read(uint8_t regaddr, uint8_t len)
{
	cs_low();
	tx_buffer[0] = READ | regaddr;
	HAL_SPI_Transmit(SPI_ICM20948, tx_buffer, 1, 10);
	HAL_SPI_Receive(SPI_ICM20948, rx_buffer, len, 10);
	cs_high();
}

void icm20948_write(uint8_t regaddr, uint8_t data)
{
	cs_low();
	tx_buffer[0] = WRITE | regaddr;
	tx_buffer[1] = data;
	HAL_SPI_Transmit(SPI_ICM20948, tx_buffer, 2, 10);
	cs_high();

	// necessary
	HAL_Delay(1);
}

// auxiliary i2c
void ak09916_read(uint8_t regaddr, uint8_t len)
{
	select_user_bank(userbank_3);

	icm20948_write(B3_I2C_SLV0_ADDR, READ | ADDRESS_AK09916);
	icm20948_write(B3_I2C_SLV0_REG, regaddr); 
	icm20948_write(B3_I2C_SLV0_CTRL, I2C_SLV_EN | len);

	select_user_bank(userbank_0);
	icm20948_read(B0_EXT_SLV_SENS_DATA_00, len);

	HAL_Delay(1);
}

void ak09916_wrtie(uint8_t regaddr, uint8_t data)
{
	select_user_bank(userbank_3);

	icm20948_write(B3_I2C_SLV0_ADDR, WRITE | ADDRESS_AK09916);
	icm20948_write(B3_I2C_SLV0_REG, regaddr);
	icm20948_write(B3_I2C_SLV0_DO, data);
	icm20948_write(B3_I2C_SLV0_CTRL, 0x81);

	HAL_Delay(1);
}

// check sensor id
uint8_t whoami_icm20948()
{
	select_user_bank(userbank_0);
	icm20948_read(B0_WHO_AM_I, 1);

	return rx_buffer[0];
}

uint8_t whoami_ak09916()
{
	ak09916_read(MAG_WIA2, 1);

	return rx_buffer[0];	// 0x09
}

// initialize
void icm20948_init()
{
	// ICM20948 Reset
	select_user_bank(userbank_0);
	icm20948_write(B0_PWR_MGMT_1, DEVICE_RESET | 0x41);

	// SPI mode only
	select_user_bank(userbank_0);
	icm20948_write(B0_USER_CTRL, I2C_IF_DIS);

	// Wake the chip and Recommended clock selection(CLKSEL = 1)
	select_user_bank(userbank_0);
	icm20948_write(B0_PWR_MGMT_1, WAKE | CLKSEL);

	// Set Gyroscope ODR and Scale
	select_user_bank(userbank_2);
	icm20948_write(B2_GYRO_SMPLRT_DIV, Gyro_ODR_1100Hz);				// Gyro ODR = 1.1kHz
	icm20948_write(B2_GYRO_CONFIG_1, GYRO_FS_SEL_250dps | GYRO_FCHOICE);	// Gyro scale ±250dps and Enable DLPF

	// Set Accelerometer ODR and Scale
	icm20948_write(B2_ACCEL_SMPLRT_DIV_2, Accel_ODR_1100Hz);			// Accel ODR = 1.1kHz
	icm20948_write(B2_ACCEL_CONFIG, ACCEL_FS_SEL_2g | ACCEL_FCHOICE);	// Accel scale ±2g and Enable DLPF
}

void ak09916_init()
{
	// I2C Master Reset
	select_user_bank(userbank_0);
	icm20948_write(B0_USER_CTRL, I2C_MST_RST);

	// I2C Master Enable
	select_user_bank(userbank_0);
	icm20948_write(B0_USER_CTRL, I2C_MST_EN);

	// I2C Master Clock Frequency
	select_user_bank(userbank_3);
	icm20948_write(B3_I2C_MST_CTRL, I2C_MST_CLK); // 345.6 kHz

	// I2C Slave Reset
	ak09916_wrtie(MAG_CNTL3, 0x01);
	
	// I2C Slave Operation Mode
	ak09916_wrtie(MAG_CNTL2, Continuous_measurement_mode_4);
}



// read gyro
void read_gyro_lsb(icm20948_t* icm20948)	// 22us
{
	icm20948_read(B0_GYRO_XOUT_H, 6);

	icm20948->gyro_lsb_x = (int16_t)(rx_buffer[0] << 8 | rx_buffer[1]);
	icm20948->gyro_lsb_y = (int16_t)(rx_buffer[2] << 8 | rx_buffer[3]);
	icm20948->gyro_lsb_z = (int16_t)(rx_buffer[4] << 8 | rx_buffer[5]);
}

void read_gyro_dps(icm20948_t* icm20948)	
{
	// get lsb data
	read_gyro_lsb(icm20948);

	// divide by 131(lsb/dps)
	icm20948->gyro_dps_x = icm20948->gyro_lsb_x / 131.0;
	icm20948->gyro_dps_y = icm20948->gyro_lsb_y / 131.0;
	icm20948->gyro_dps_z = icm20948->gyro_lsb_z / 131.0;  
}


// read aceel
void read_accel_lsb(icm20948_t* icm20948)	// 22us
{
	icm20948_read(B0_ACCEL_XOUT_H, 6);

	icm20948->accel_lsb_x = (int16_t)(rx_buffer[0] << 8 | rx_buffer[1]);
	icm20948->accel_lsb_y = (int16_t)(rx_buffer[2] << 8 | rx_buffer[3]);
	icm20948->accel_lsb_z = (int16_t)(rx_buffer[4] << 8 | rx_buffer[5]);
}

void read_accel_g(icm20948_t* icm20948)
{
	read_accel_lsb(icm20948);

	icm20948->accel_g_x = icm20948->accel_lsb_x / 16384.0;
	icm20948->accel_g_y = icm20948->accel_lsb_y / 16384.0;
	icm20948->accel_g_z = (icm20948->accel_lsb_z / 16384.0) + 1;
}


// read mag
void read_mag_lsb(ak09916_t* ak09916)
{
	int16_t data_buffer[3] = {0};

	// Read status1(ST1) register
	ak09916_read(MAG_ST1,1);

	// check data is ready
	if((rx_buffer[0] & 0x01) == 1)
	{ 
		// Read Measurement data register(HXL to HZH)
		ak09916_read(MAG_HXL, 6);

		data_buffer[0] = (int16_t)(rx_buffer[1] << 8 | rx_buffer[0]);
		data_buffer[1] = (int16_t)(rx_buffer[3] << 8 | rx_buffer[2]);
		data_buffer[2] = (int16_t)(rx_buffer[5] << 8 | rx_buffer[4]);

		// Read status2(ST2) register
		ak09916_read(MAG_ST2, 1);

		if((rx_buffer[0] & 0x08) == 0x00) // not overflow
		{
			ak09916->mag_x = data_buffer[0];
			ak09916->mag_y = data_buffer[1];
			ak09916->mag_z = data_buffer[2];
		}
	}
}


// calibrate gyro and accel
void calibrate_icm20948(icm20948_t* icm20948, uint16_t samples)
{
	int32_t gyro_bias[3] = {0, 0, 0};
	uint8_t gyro_offset[6] = {0, 0, 0, 0, 0, 0};

	int32_t accel_bias_reg[3] = {0, 0, 0};
	int32_t accel_bias[3] = {0, 0, 0};
	uint8_t accel_offset[6] = {0, 0, 0, 0, 0, 0};

	// for read function
	select_user_bank(userbank_0);

	// average
	for(int i = 0; i < samples; i++)
	{
		read_accel_lsb(icm20948);
		read_gyro_lsb(icm20948);

		gyro_bias[0] += icm20948->gyro_lsb_x;
		gyro_bias[1] += icm20948->gyro_lsb_y;
		gyro_bias[2] += icm20948->gyro_lsb_z;

		accel_bias[0] += icm20948->accel_lsb_x;
		accel_bias[1] += icm20948->accel_lsb_y;
		accel_bias[2] += icm20948->accel_lsb_z;
	}

	gyro_bias[0] /= (int32_t) samples;
	gyro_bias[1] /= (int32_t) samples;	
	gyro_bias[2] /= (int32_t) samples;

	accel_bias[0] /= (int32_t) samples;
	accel_bias[1] /= (int32_t) samples;	
	accel_bias[2] /= (int32_t) samples;

	// gyro offset register
	gyro_offset[0] = (-gyro_bias[0] / 4  >> 8) & 0xFF; 
	gyro_offset[1] = (-gyro_bias[0] / 4)       & 0xFF; 
	gyro_offset[2] = (-gyro_bias[1] / 4  >> 8) & 0xFF;
	gyro_offset[3] = (-gyro_bias[1] / 4)       & 0xFF;
	gyro_offset[4] = (-gyro_bias[2] / 4  >> 8) & 0xFF;
	gyro_offset[5] = (-gyro_bias[2] / 4)       & 0xFF;

	// write
	select_user_bank(userbank_2);
	icm20948_write(B2_XG_OFFS_USRH, gyro_offset[0]);
	icm20948_write(B2_XG_OFFS_USRL, gyro_offset[1]);
	icm20948_write(B2_YG_OFFS_USRH, gyro_offset[2]);
	icm20948_write(B2_YG_OFFS_USRL, gyro_offset[3]);
	icm20948_write(B2_ZG_OFFS_USRH, gyro_offset[4]);
	icm20948_write(B2_ZG_OFFS_USRL, gyro_offset[5]);

	// read factory accel trim values
	select_user_bank(userbank_1);
	icm20948_read(B1_XA_OFFS_H, 2);
	accel_bias_reg[0] = (int32_t)((int16_t)rx_buffer[0] << 8 | rx_buffer[1]);

	icm20948_read(B1_YA_OFFS_H, 2);
	accel_bias_reg[1] = (int32_t)((int16_t)rx_buffer[0] << 8 | rx_buffer[1]);

	icm20948_read(B1_ZA_OFFS_H, 2);
	accel_bias_reg[2] = (int32_t)((int16_t)rx_buffer[0] << 8 | rx_buffer[1]);

	// accel offset register
	accel_bias_reg[0] -= (accel_bias[0] / 8);
	accel_bias_reg[1] -= (accel_bias[1] / 8);
	accel_bias_reg[2] -= (accel_bias[2] / 8);

	// ignore bit 0 (& 0xFE)
	accel_offset[0] = (accel_bias_reg[0] >> 8) & 0xFF;
  	accel_offset[1] = (accel_bias_reg[0])      & 0xFE;

	accel_offset[2] = (accel_bias_reg[1] >> 8) & 0xFF;
  	accel_offset[3] = (accel_bias_reg[1])      & 0xFE;

	accel_offset[4] = (accel_bias_reg[2] >> 8) & 0xFF;
	accel_offset[5] = (accel_bias_reg[2])      & 0xFE;

	// write
	select_user_bank(userbank_1);
	icm20948_write(B1_XA_OFFS_H, accel_offset[0]);
	icm20948_write(B1_XA_OFFS_L, accel_offset[1]);
	icm20948_write(B1_YA_OFFS_H, accel_offset[2]);
	icm20948_write(B1_YA_OFFS_L, accel_offset[3]);
	icm20948_write(B1_ZA_OFFS_H, accel_offset[4]);
	icm20948_write(B1_ZA_OFFS_L, accel_offset[5]);

	// for read function
	select_user_bank(userbank_0);
}


void complementary_filter(icm20948_t *icm20948, angle_t *angle)
{
	read_gyro_dps(icm20948);
	read_accel_g(icm20948);

	// angle from gyro
	// dt : 1ms
	angle->gyro_angle_x += icm20948->gyro_dps_x * (0.001);
	angle->gyro_angle_y += icm20948->gyro_dps_y * (0.001);
	angle->gyro_angle_z += icm20948->gyro_dps_z * (0.001);

	// angle from accel
	angle->accel_angle_x = atan(icm20948->accel_g_y / sqrt( pow(icm20948->accel_g_x, 2) + pow(icm20948->accel_g_z, 2) ) ) * 57.3;
	angle->accel_angle_y = atan(icm20948->accel_g_x / sqrt( pow(icm20948->accel_g_y, 2) + pow(icm20948->accel_g_z, 2) ) ) * 57.3;
	angle->accel_angle_z = 0;

	// angle from complementary filter
	angle->angle_x = ALPHA * angle->gyro_angle_x + (1 - ALPHA) * angle->accel_angle_x;
	angle->angle_y = ALPHA * angle->gyro_angle_y + (1 - ALPHA) * angle->accel_angle_y;
	angle->angle_z = angle->gyro_angle_z;
}