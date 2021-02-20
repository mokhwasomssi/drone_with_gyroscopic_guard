/*
*
* icm_20948.C
*
 *  Created on: Dec 26, 2020
 *      Author: mokhwasomssi
 *
*   Chip : ICM-20948
*   Breakout Board : SparkFun 9Dof IMU Breakout - ICM-20948 (Qwiic)
*
*/

#include "icm_20948_register.h"
#include "icm_20948.h"


/* Temporary Array */
uint8_t tx_buffer[6] = {0};
uint8_t rx_buffer[6] = {0};


/* Change The State of CS */
void cs_high()
{
	HAL_GPIO_WritePin(CS_PIN_PORT, CS_PIN_NUMBER, SET);
}

void cs_low()
{
	HAL_GPIO_WritePin(CS_PIN_PORT, CS_PIN_NUMBER, RESET);
}


/* Select Bank Before Access the Register */
void select_user_bank(userbank_e ub)
{
	icm20948_write(B0_REG_BANK_SEL, ub);
}


/* Read/Write ICM20948 */
void icm20948_read(uint8_t regaddr, uint8_t len)
{
	cs_low();
	tx_buffer[0] = READ | regaddr;
	HAL_SPI_Transmit(SPI_ICM20948, tx_buffer, 1, 10);
	HAL_SPI_Receive(SPI_ICM20948, rx_buffer, len, 10);
	cs_high();

	HAL_Delay(1);
}

void icm20948_write(uint8_t regaddr, uint8_t data)
{
	cs_low();
	tx_buffer[0] = WRITE | regaddr;
	tx_buffer[1] = data;
	HAL_SPI_Transmit(SPI_ICM20948, tx_buffer, 2, 10);
	cs_high();

	HAL_Delay(1);
}

/* Read/Write AK09916 */
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


/* Who Am I */
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


/* Initialize ICM-20948(Gyroscope, accelerometer) */
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


/* Initialize AK09916(Magnetometer) */
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


/* Read Sensor Data */
void read_gyro(icm20948_s* data)
{
	select_user_bank(userbank_0);
	icm20948_read(B0_GYRO_XOUT_H, 6);

	data->Gyro_X_Data = (int16_t)(rx_buffer[0] << 8 | rx_buffer[1]);
	data->Gyro_Y_Data = (int16_t)(rx_buffer[2] << 8 | rx_buffer[3]);
	data->Gyro_Z_Data = (int16_t)(rx_buffer[4] << 8 | rx_buffer[5]);
}

void read_accel(icm20948_s* data)
{
	select_user_bank(userbank_0);
	icm20948_read(B0_ACCEL_XOUT_H, 6);

	data->Accel_X_Data = (int16_t)(rx_buffer[0] << 8 | rx_buffer[1]);
	data->Accel_Y_Data = (int16_t)(rx_buffer[2] << 8 | rx_buffer[3]);
	data->Accel_Z_Data = (int16_t)(rx_buffer[4] << 8 | rx_buffer[5]);
}

void read_mag(icm20948_s* data)
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
			data->Mag_X_Data = data_buffer[0];
			data->Mag_Y_Data = data_buffer[1];
			data->Mag_Z_Data = data_buffer[2];
		}
	}
}
