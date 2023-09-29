/*
 * Header file for MPU6050 configuration
 *
 *  Created on: Sep. 28, 2023
 *      Author: Rijin
 */


#ifndef MPU6050_H_
#define MPU6050_H_

#define SENSOR_ADDR 0x68 << 1

/* Registers for the MPU6050*/

/* General config (Sampling Rate, Bandwidth, Delay) */
#define SENSOR_CONFIG_REG 0x1A

/* Gyroscope Config */
#define GYRO_CONFIG_REG 0x1B
#define GYRO_RANGE_250 0x00
#define GYRO_RANGE_500 0x08
#define GYRO_RANGE_1000 0x09
#define GYRO_RANGE_2000 0xA

/* Gyroscope Measurements */
#define GYRO_XOUT 0x43
#define GYRO_YOUT 0x45
#define GYRO_ZOUT 0x47

/* Accelerometer Config */
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_RANGE_4G 0x08
#define ACCEL_RANGE_8G 0x09
#define ACCEL_RANGE_16G 0xA

/* Accelerometer Measurements */
#define ACCEL_XOUT 0x3B
#define ACCEL_YOUT 0x3D
#define ACCEL_ZOUT 0x3F

/* Sleep Mode Config */
#define SLEEP_MODE_REG 0x6B
#define SLEEP_MODE_ON  0x40
#define SLEEP_MODE_OFF 0x00

/* MPU6050 Sensor Functions */

void mpu6050_init();
void mpu6050_read();

#endif /* MPU6050_H_ */




