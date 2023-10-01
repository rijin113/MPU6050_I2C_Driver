/*
 * Source file for MPU6050 Configuration
 *
 *  Created on: Sep. 28, 2023
 *      Author: Rijin
 */

#include "mpu6050.h"
#include "main.h"
#include <stdio.h>
#include <math.h>

extern I2C_HandleTypeDef hi2c1;

void mpu6050_init()
{ 
  uint8_t set_gyro_range = GYRO_RANGE_500;
  uint8_t set_accel_range = ACCEL_RANGE_4G;
  uint8_t set_sleep_mode = SLEEP_MODE_OFF;
  HAL_StatusTypeDef device_ready = HAL_I2C_IsDeviceReady(&hi2c1, SENSOR_ADDR, 1, 100);
  HAL_StatusTypeDef gyro_ready = HAL_I2C_Mem_Write(&hi2c1, SENSOR_ADDR, GYRO_CONFIG_REG, 1, &set_gyro_range, 1, 100);
  HAL_StatusTypeDef acc_ready = HAL_I2C_Mem_Write(&hi2c1, SENSOR_ADDR, ACCEL_CONFIG_REG, 1, &set_accel_range, 1, 100);
  HAL_StatusTypeDef sleep_ready = HAL_I2C_Mem_Write(&hi2c1, SENSOR_ADDR, SLEEP_MODE_REG, 1, &set_sleep_mode, 1, 100);
  
  if(device_ready == HAL_OK && gyro_ready == HAL_OK && acc_ready == HAL_OK && sleep_ready == HAL_OK)
  {
    printf("Sensor is ready and configured.\n");
  }
  else
  {
    printf("Device is not ready.\n");
  }
}

void mpu6050_read()
{
    /* Acceleration Init Variables */
    uint8_t x_acc_data[2];
    int16_t x_acc_val_raw;
    int16_t x_acc_val;

    uint8_t y_acc_data[2];
    int16_t y_acc_val_raw;
    int16_t y_acc_val;

    uint8_t z_acc_data[2];
    int16_t z_acc_val_raw;
    int16_t z_acc_val;

    /* Gyroscope Init Variables */
    uint8_t x_gyro_data[2];
    int16_t x_gyro_val_raw;
    int16_t x_gyro_val;

    uint8_t y_gyro_data[2];
    int16_t y_gyro_val_raw;
    int16_t y_gyro_val;

    uint8_t z_gyro_data[2];
    int16_t z_gyro_val_raw;
    int16_t z_gyro_val;

    /* Acceleration Measurements */
    HAL_I2C_Mem_Read(&hi2c1, SENSOR_ADDR, ACCEL_XOUT_HIGH, 1, &x_acc_data[0], 1, 100);
    HAL_I2C_Mem_Read(&hi2c1, SENSOR_ADDR, ACCEL_XOUT_LOW, 1, &x_acc_data[1], 1, 100);
    x_acc_val_raw = ((int16_t)x_acc_data[0] << 8) | x_acc_data[1];
    x_acc_val = (double)x_acc_val_raw * (FULL_SCALE_RANGE/(pow(2,16)-1));

    HAL_I2C_Mem_Read(&hi2c1, SENSOR_ADDR, ACCEL_YOUT_HIGH, 1, &y_acc_data[0], 1, 100);
    HAL_I2C_Mem_Read(&hi2c1, SENSOR_ADDR, ACCEL_YOUT_LOW, 1, &y_acc_data[1], 1, 100);
    y_acc_val_raw = ((int16_t)y_acc_data[0] << 8) | y_acc_data[1];
    y_acc_val = (double)y_acc_val_raw * (FULL_SCALE_RANGE/(pow(2,16)-1));

    HAL_I2C_Mem_Read(&hi2c1, SENSOR_ADDR, ACCEL_ZOUT_HIGH, 1, &z_acc_data[0], 1, 100);
    HAL_I2C_Mem_Read(&hi2c1, SENSOR_ADDR, ACCEL_ZOUT_LOW, 1, &z_acc_data[1], 1, 100);
    z_acc_val_raw = ((int16_t)z_acc_data[0] << 8) | z_acc_data[1];
    z_acc_val = (double)z_acc_val_raw * (FULL_SCALE_RANGE/(pow(2,16)-1));

    /* Gyroscope Measurements */
    HAL_I2C_Mem_Read(&hi2c1, SENSOR_ADDR, GYRO_XOUT_HIGH, 1, &x_gyro_data[0], 1, 100);
    HAL_I2C_Mem_Read(&hi2c1, SENSOR_ADDR, GYRO_XOUT_LOW, 1, &x_gyro_data[1], 1, 100);
    x_gyro_val_raw = ((int16_t)x_gyro_data[0] << 8) | x_gyro_data[1];
    x_gyro_val = (double)x_gyro_val_raw;

    HAL_I2C_Mem_Read(&hi2c1, SENSOR_ADDR, GYRO_YOUT_HIGH, 1, &y_gyro_data[0], 1, 100);
    HAL_I2C_Mem_Read(&hi2c1, SENSOR_ADDR, GYRO_YOUT_LOW, 1, &y_gyro_data[1], 1, 100);
    y_gyro_val_raw = ((int16_t)y_gyro_data[0] << 8) | y_gyro_data[1];
    y_gyro_val = (double)y_gyro_val_raw;

    HAL_I2C_Mem_Read(&hi2c1, SENSOR_ADDR, GYRO_ZOUT_HIGH, 1, &z_gyro_data[0], 1, 100);
    HAL_I2C_Mem_Read(&hi2c1, SENSOR_ADDR, GYRO_ZOUT_LOW, 1, &z_gyro_data[1], 1, 100);
    z_gyro_val_raw = ((int16_t)z_gyro_data[0] << 8) | z_gyro_data[1];
    z_gyro_val = (double)z_gyro_val_raw;

    printf(" ---------- MEASUREMENTS START ------------ \n\r");
    printf(" x axis acceleration: %d , y axis acceleration: %d, z axis acceleration: %d\n\r",
    		x_acc_val, y_acc_val, z_acc_val);
    printf(" x axis gyro: %d , y axis gyro: %d, z axis gyro: %d\n\r",
    		x_gyro_val, y_gyro_val, z_gyro_val);
    printf(" ---------- MEASUREMENTS END ------------ \n\r");

    HAL_Delay(1000);
}
