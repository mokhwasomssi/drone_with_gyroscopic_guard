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

// offset variable
offset_t my_offset = {0, };


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
	icm20948_write(B0_PWR_MGMT_1, DEVICE_RESET | 0x41);	// 0x41 is reset value

	// SPI mode only
	select_user_bank(userbank_0);
	icm20948_write(B0_USER_CTRL, I2C_IF_DIS);

	// Wake the chip and Recommended clock selection(CLKSEL = 1)
	select_user_bank(userbank_0);
	icm20948_write(B0_PWR_MGMT_1, WAKE | CLKSEL);

	// ODR start time alignment
	select_user_bank(userbank_2);
	icm20948_write(B2_ODR_ALIGN_EN, ODR_START_TIME_ALIGNMENT_ENABLE);

	// Set Gyroscope ODR and Scale
	select_user_bank(userbank_2);
	icm20948_write(B2_GYRO_SMPLRT_DIV, Gyro_ODR_1125Hz);				// Gyro ODR = 1.125kHz
	icm20948_write(B2_GYRO_CONFIG_1, GYRO_FS_SEL_2000dps | GYRO_FCHOICE);	// Gyro scale ±2000dps and Enable DLPF
																			// 자이로 스케일 키우면 잔떨림은 감지x
	// Set Accelerometer ODR and Scale
	icm20948_write(B2_ACCEL_SMPLRT_DIV_2, Accel_ODR_1125Hz);			// Accel ODR = 1.125kHz
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
void read_gyro_lsb(icm20948_t* icm20948)
{
	icm20948_read(B0_GYRO_XOUT_H, 6);

	// calibration
	if(my_offset.offsetting == 1)
	{
		icm20948->gyro_lsb_x = (int16_t)(rx_buffer[0] << 8 | rx_buffer[1]) - my_offset.gyro_x;
		icm20948->gyro_lsb_y = (int16_t)(rx_buffer[2] << 8 | rx_buffer[3]) - my_offset.gyro_y;
		icm20948->gyro_lsb_z = (int16_t)(rx_buffer[4] << 8 | rx_buffer[5]) - my_offset.gyro_z;
	}

	// raw data
	else
	{
		icm20948->gyro_lsb_x = (int16_t)(rx_buffer[0] << 8 | rx_buffer[1]);
		icm20948->gyro_lsb_y = (int16_t)(rx_buffer[2] << 8 | rx_buffer[3]);
		icm20948->gyro_lsb_z = (int16_t)(rx_buffer[4] << 8 | rx_buffer[5]);
	}
}

void read_gyro_dps(icm20948_t* icm20948)	
{
	// get lsb data
	read_gyro_lsb(icm20948);

	// divide by 131(lsb/dps)
	icm20948->gyro_dps_x = icm20948->gyro_lsb_x / 16.4;
	icm20948->gyro_dps_y = icm20948->gyro_lsb_y / 16.4;
	icm20948->gyro_dps_z = icm20948->gyro_lsb_z / 16.4;  
}


// read aceel
void read_accel_lsb(icm20948_t* icm20948)	// 22us
{
	icm20948_read(B0_ACCEL_XOUT_H, 6);
	
	if(my_offset.offsetting == 1)
	{
		icm20948->accel_lsb_x = (int16_t)(rx_buffer[0] << 8 | rx_buffer[1]) - my_offset.accel_x;
		icm20948->accel_lsb_y = (int16_t)(rx_buffer[2] << 8 | rx_buffer[3]) - my_offset.accel_y;
		icm20948->accel_lsb_z = (int16_t)(rx_buffer[4] << 8 | rx_buffer[5]) - my_offset.accel_z;
	}
	else
	{
		icm20948->accel_lsb_x = (int16_t)(rx_buffer[0] << 8 | rx_buffer[1]);
		icm20948->accel_lsb_y = (int16_t)(rx_buffer[2] << 8 | rx_buffer[3]);
		icm20948->accel_lsb_z = (int16_t)(rx_buffer[4] << 8 | rx_buffer[5]);
	}
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