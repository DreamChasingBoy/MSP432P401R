/*
 * boympu6050.h
 *
 *  Created on: 2023年8月1日
 *      Author: 26491
 */

#ifndef BOYLIBS_BOYMPU6050_H_
#define BOYLIBS_BOYMPU6050_H_
#include "exinlibs\headfile.h"
#define SMPLRT_DIV          0x19    //陀螺仪采样率，典型值：0x07(125Hz)
#define CONFIGL             0x1A    //低通滤波频率，典型值：0x06(5Hz)
#define GYRO_CONFIG         0x1B    //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define ACCEL_CONFIG        0x1C    //加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define ACCEL_ADDRESS       0x3B
#define ACCEL_XOUT_H        0x3B
#define ACCEL_XOUT_L        0x3C
#define ACCEL_YOUT_H        0x3D
#define ACCEL_YOUT_L        0x3E
#define ACCEL_ZOUT_H        0x3F
#define ACCEL_ZOUT_L        0x40
#define TEMP_OUT_H          0x41
#define TEMP_OUT_L          0x42
#define GYRO_XOUT_H         0x43
#define GYRO_XOUT_L         0x44
#define GYRO_YOUT_H         0x45
#define GYRO_YOUT_L         0x46
#define GYRO_ZOUT_H         0x47
#define GYRO_ZOUT_L         0x48
#define PWR_MGMT_1          0x6B    //电源管理，典型值：0x00(正常启用)
#define WHO_AM_I            0x75    //IIC地址寄存器(默认数值0x68，只读)
#define MPU6050_PRODUCT_ID  0x68
#define MPU6052C_PRODUCT_ID 0x72
#define MPU6050_ADDRESS     0xD0    //0x68

//数据结构声明
typedef struct{
    int16_t accX;
    int16_t accY;
    int16_t accZ;
    int16_t gyroX;
    int16_t gyroY;
    int16_t gyroZ;

    int16_t Offset[6];
    uint8_t Check;
    int16_t G;
}MPU6050Manager_t;
extern MPU6050Manager_t g_MPUManager;
uint8_t MPU6050Init(void);
void GetMPU6050Data(void);
void GetMPU6050Offset(void);
#define Acc_Read()          I2C_Read_Bytes(MPU6050_ADDRESS, 0x3B, buffer, 6) //读取加速度
#define Gyro_Read()         I2C_Read_Bytes(MPU6050_ADDRESS, 0x43, &buffer[6], 6)  //  读取角速度
extern uint8_t I2C_Read_Byte(uint8_t Slaveaddr, uint8_t REG_Address);


#endif /* BOYLIBS_BOYMPU6050_H_ */
