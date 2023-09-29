/*
 * Source file for MPU6050 Configuration
 *
 *  Created on: Sep. 28, 2023
 *      Author: Rijin
 */

#include "mpu6050.h"
#include "main.h"
#include <stdio.h>

extern I2C_HandleTypeDef hi2c1;

void mpu6050_init()
{ 
  uint8_t data1 = GYRO_RANGE_500;
  uint8_t data2 = ACCEL_RANGE_4G;
  uint8_t data3 = SLEEP_MODE_OFF;
  HAL_StatusTypeDef device_ready = HAL_I2C_IsDeviceReady(&hi2c1, SENSOR_ADDR, 1, 100);
  HAL_StatusTypeDef gyro_ready = HAL_I2C_Mem_Write(&hi2c1, SENSOR_ADDR, GYRO_CONFIG_REG, 1, &data1, 1, 100);
  HAL_StatusTypeDef acc_ready = HAL_I2C_Mem_Write(&hi2c1, SENSOR_ADDR, ACCEL_CONFIG_REG, 1, &data2, 1, 100);
  HAL_StatusTypeDef sleep_ready = HAL_I2C_Mem_Write(&hi2c1, SENSOR_ADDR, SLEEP_MODE_REG, 1, &data3, 1, 100);
  
  if(device_ready == HAL_OK && gyro_ready == HAL_OK && acc_ready == HAL_OK && sleep_ready == HAL_OK)
  {
    printf("Device, Gyro, Accelerometer and Sleep mode are all configured. \n");
  }
  else
  {
    printf("Device not all configured. \n");
  }
}

void mpu6050_read()
{
    uint8_t x_acc_data[2];
    uint16_t x_acc_val;
    uint8_t y_acc_data[2];
    uint16_t y_acc_val;
    uint8_t z_acc_data[2];
    uint16_t z_acc_val;

    HAL_I2C_Mem_Read(&hi2c1, SENSOR_ADDR, ACCEL_XOUT, 1, x_acc_data, 2, 100);
    x_acc_val = ((uint16_t)x_acc_data[0] << 8) + x_acc_data[1];

    HAL_I2C_Mem_Read(&hi2c1, SENSOR_ADDR, ACCEL_YOUT, 1, y_acc_data, 2, 100);
    y_acc_val = ((uint16_t)y_acc_data[0] << 8) + y_acc_data[1];

    HAL_I2C_Mem_Read(&hi2c1, SENSOR_ADDR, ACCEL_ZOUT, 1, z_acc_data, 2, 100);
    z_acc_val = ((uint16_t)z_acc_data[0] << 8) + z_acc_data[1];

    printf("x axis acceleration: %d , y axis acceleration: %d, z axis acceleration: %d  \n", x_acc_val, y_acc_val, z_acc_val);

    HAL_Delay(1000);
}
