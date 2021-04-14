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

// constant for changing unit
float gyro_typ;
float accel_typ;
float mag_typ = 0.15;


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
	cs_low();
	tx_buffer[0] = WRITE | B0_REG_BANK_SEL;
	tx_buffer[1] = ub;
	HAL_SPI_Transmit(SPI_ICM20948, tx_buffer, 2, 10);
	cs_high();
}

// spi
void read_icm20948(uint8_t regaddr, uint8_t len)
{
	cs_low();
	tx_buffer[0] = READ | regaddr;
	HAL_SPI_Transmit(SPI_ICM20948, tx_buffer, 1, 10);
	HAL_SPI_Receive(SPI_ICM20948, rx_buffer, len, 10);
	cs_high();
}

void write_icm20948(uint8_t regaddr, uint8_t data)
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
void read_ak09916(uint8_t regaddr, uint8_t len)
{
	select_user_bank(userbank_3);

	write_icm20948(B3_I2C_SLV0_ADDR, READ | ADDRESS_AK09916);
	write_icm20948(B3_I2C_SLV0_REG, regaddr); 
	write_icm20948(B3_I2C_SLV0_CTRL, I2C_SLV_EN | len);

	select_user_bank(userbank_0);
	read_icm20948(B0_EXT_SLV_SENS_DATA_00, len);
}

void write_ak09916(uint8_t regaddr, uint8_t data)
{
	select_user_bank(userbank_3);

	write_icm20948(B3_I2C_SLV0_ADDR, WRITE | ADDRESS_AK09916);
	write_icm20948(B3_I2C_SLV0_REG, regaddr);
	write_icm20948(B3_I2C_SLV0_DO, data);
	write_icm20948(B3_I2C_SLV0_CTRL, 0x81);

}

// check sensor id
uint8_t whoami_icm20948()
{
	select_user_bank(userbank_0);
	read_icm20948(B0_WHO_AM_I, 1);
	while(rx_buffer[0] != DEVICE_ID_ICM20948)

	return rx_buffer[0];
}

uint8_t whoami_ak09916()
{
	read_ak09916(MAG_WIA2, 1);
	while(rx_buffer[0] != DEVICE_ID_AK09916);

	return rx_buffer[0];
}


// set full scale and ODR
void set_gyro_full_scale(gyro_fs_e gyro_fs)
{
	select_user_bank(userbank_2);
	write_icm20948(B2_GYRO_CONFIG_1, gyro_fs | GYRO_FCHOICE);

	switch(gyro_fs)
	{
		case fs_250dps :
			gyro_typ = 131;
			break;
		
		case fs_500dps :
			gyro_typ = 65.5;
			break;

		case fs_1000dps :
			gyro_typ = 32.8;
			break;
		
		case fs_2000dps :
			gyro_typ = 16.4;
			break;

		default : 
			gyro_typ = 0;
	}
}

void set_accel_full_scale(accel_fs_e accel_fs)
{
	select_user_bank(userbank_2);
	write_icm20948(B2_ACCEL_CONFIG, accel_fs | ACCEL_FCHOICE);

	switch(accel_fs)
	{
		case fs_2g :
			accel_typ = 16384;
			break;
		
		case fs_4g :
			accel_typ = 8192;
			break;

		case fs_8g :
			accel_typ = 4096;
			break;
		
		case fs_16g :
			accel_typ = 2048;
			break;

		default : 
			accel_typ = 0;
	}
}

void set_gyro_odr(uint16_t odr_hz)
{
	select_user_bank(userbank_2);

	uint8_t div = 0;
	div = (1125 / odr_hz) - 1;

	write_icm20948(B2_GYRO_SMPLRT_DIV, div);
}

void set_accel_odr(uint16_t odr_hz)
{
	select_user_bank(userbank_2);

	uint8_t div = 0;
	div = (1125 / odr_hz) - 1;

	write_icm20948(B2_ACCEL_SMPLRT_DIV_2, div);
}


// initialize
void icm20948_init(gyro_fs_e gyro_fs, uint16_t gyro_odr_hz, accel_fs_e accel_fs, uint16_t accel_ord_hz)
{
	// ICM20948 Reset
	select_user_bank(userbank_0);
	write_icm20948(B0_PWR_MGMT_1, DEVICE_RESET | 0x41);	// 0x41 is reset value

	// SPI mode only
	select_user_bank(userbank_0);
	write_icm20948(B0_USER_CTRL, I2C_IF_DIS);

	// Wake the chip and Recommended clock selection(CLKSEL = 1)
	select_user_bank(userbank_0);
	write_icm20948(B0_PWR_MGMT_1, WAKE | CLKSEL);

	// ODR start time alignment
	select_user_bank(userbank_2);
	write_icm20948(B2_ODR_ALIGN_EN, ODR_START_TIME_ALIGNMENT_ENABLE);

	// set full scale and ODR
	set_gyro_full_scale(gyro_fs);
	set_accel_full_scale(accel_fs);

	set_gyro_odr(gyro_odr_hz);
	set_accel_odr(accel_ord_hz);
}

// i2c : master(icm-20948) / slave(ak09916)
void ak09916_init(op_mode_e op_mode)
{
	// I2C Master Reset
	select_user_bank(userbank_0);
	write_icm20948(B0_USER_CTRL, I2C_MST_RST);

	// I2C Master Enable
	select_user_bank(userbank_0);
	write_icm20948(B0_USER_CTRL, I2C_MST_EN);

	// I2C Master Clock Frequency
	select_user_bank(userbank_3);
	write_icm20948(B3_I2C_MST_CTRL, I2C_MST_CLK); // 345.6 kHz

	// I2C Slave Reset
	write_ak09916(MAG_CNTL3, 0x01);
	
	// I2C Slave Operation Mode
	write_ak09916(MAG_CNTL2, op_mode);
}

// read gyro
void read_gyro(gyro_data_t* gyro_data, unit_e unit)
{
	int16_t gyro_data_temp[3];

	select_user_bank(userbank_0);
	read_icm20948(B0_GYRO_XOUT_H, 6);

	gyro_data_temp[0] = (int16_t)(rx_buffer[0] << 8 | rx_buffer[1]);
	gyro_data_temp[1] = (int16_t)(rx_buffer[2] << 8 | rx_buffer[3]);
	gyro_data_temp[2] = (int16_t)(rx_buffer[4] << 8 | rx_buffer[5]);

	switch(unit)
	{
		case lsb :
			gyro_data->x = gyro_data_temp[0];
			gyro_data->y = gyro_data_temp[1];
			gyro_data->z = gyro_data_temp[2];
			break;
		
		case dps : 
			gyro_data->x = (float)(gyro_data_temp[0] / gyro_typ);
			gyro_data->y = (float)(gyro_data_temp[1] / gyro_typ);
			gyro_data->z = (float)(gyro_data_temp[2] / gyro_typ);
			break;

		default : 
			gyro_data->x = 0;
			gyro_data->y = 0;
			gyro_data->z = 0;
	}
}


void read_accel(accel_data_t* accel_data, unit_e unit)
{
	int16_t accel_data_temp[3];

	select_user_bank(userbank_0);
	read_icm20948(B0_ACCEL_XOUT_H, 6);
	
	accel_data_temp[0] = (int16_t)(rx_buffer[0] << 8 | rx_buffer[1]);
	accel_data_temp[1] = (int16_t)(rx_buffer[2] << 8 | rx_buffer[3]);
	accel_data_temp[2] = (int16_t)(rx_buffer[4] << 8 | rx_buffer[5]);

	switch(unit)
	{
		case lsb :
			accel_data->x = accel_data_temp[0];
			accel_data->y = accel_data_temp[1];
			accel_data->z = accel_data_temp[2];
			break;
		
		case g : 
			accel_data->x = (float)(accel_data_temp[0] / accel_typ);
			accel_data->y = (float)(accel_data_temp[1] / accel_typ);
			accel_data->z = (float)(accel_data_temp[2] / accel_typ);
			break;

		default : 
			accel_data->x = 0;
			accel_data->y = 0;
			accel_data->z = 0;
	}
}


// read mag
void read_mag(mag_data_t* mag_data, unit_e unit)
{
	int16_t mag_data_temp[3] = {0};

	// Read status1(ST1) register
	read_ak09916(MAG_ST1,1);

	// check data is ready
	if((rx_buffer[0] & 0x01) == 1)
	{ 
		// Read Measurement data register(HXL to HZH)
		read_ak09916(MAG_HXL, 6);
		mag_data_temp[0] = (int16_t)(rx_buffer[1] << 8 | rx_buffer[0]);
		mag_data_temp[1] = (int16_t)(rx_buffer[3] << 8 | rx_buffer[2]);
		mag_data_temp[2] = (int16_t)(rx_buffer[5] << 8 | rx_buffer[4]);

		// Read status2(ST2) register
		read_ak09916(MAG_ST2, 1);
		if((rx_buffer[0] & 0x08) == 0x00) // not overflow
		{
			switch(unit)
			{
				case lsb :
					mag_data->x = mag_data_temp[0];
					mag_data->y = mag_data_temp[1];
					mag_data->z = mag_data_temp[2];
					break;
				
				case uT : 
					mag_data->x = (float)(mag_data_temp[0] / mag_typ);
					mag_data->y = (float)(mag_data_temp[1] / mag_typ);
					mag_data->z = (float)(mag_data_temp[2] / mag_typ);
					break;

				default : 
					mag_data->x = 0;
					mag_data->y = 0;
					mag_data->z = 0;
			}

		}

	}

}



/*

// calibrate gyro and accel
void calibrate_icm20948(icm20948_t* icm20948, uint16_t samples)
{
	// for read function
	select_user_bank(userbank_0);

	// average
	for(int i = 0; i < samples; i++)
	{
		read_gyro_lsb(icm20948);
		read_accel_lsb(icm20948);

		my_offset.gyro_x += icm20948->gyro_lsb_x;
		my_offset.gyro_y += icm20948->gyro_lsb_y;
		my_offset.gyro_z += icm20948->gyro_lsb_z;

		my_offset.accel_x += icm20948->accel_lsb_x;
		my_offset.accel_y += icm20948->accel_lsb_y;
		my_offset.accel_z += icm20948->accel_lsb_z;
	}

	my_offset.gyro_x /= samples;
	my_offset.gyro_y /= samples;	
	my_offset.gyro_z /= samples;

	my_offset.accel_x /= samples;
	my_offset.accel_y /= samples;	
	my_offset.accel_z /= samples;
	
	// 
	my_offset.gyro_x = 25;
	my_offset.gyro_y = 15;

	// offset flag
	my_offset.offsetting = 1;

	// for read function
	select_user_bank(userbank_0);
}


void complementary_filter(icm20948_t *icm20948, angle_t *angle)
{
	read_gyro_dps(icm20948);
	read_accel_g(icm20948);

	// angle from gyro
	// dt : 0.89ms
	angle->gyro_angle_x += icm20948->gyro_dps_x * dt;
	angle->gyro_angle_y += icm20948->gyro_dps_y * dt;
	angle->gyro_angle_z += icm20948->gyro_dps_z * dt;

	// angle from accel
	angle->accel_angle_x = atan(icm20948->accel_g_y / sqrt( pow(icm20948->accel_g_x, 2) + pow(icm20948->accel_g_z, 2) ) ) * 57.3;
	angle->accel_angle_y = atan(icm20948->accel_g_x / sqrt( pow(icm20948->accel_g_y, 2) + pow(icm20948->accel_g_z, 2) ) ) * 57.3;
	angle->accel_angle_z = 0;

	// angle from complementary filter
	angle->angle_x = ALPHA * angle->gyro_angle_x + (1 - ALPHA) * angle->accel_angle_x;
	angle->angle_y = ALPHA * angle->gyro_angle_y + (1 - ALPHA) * angle->accel_angle_y;
	angle->angle_z = angle->gyro_angle_z;

}

*/
