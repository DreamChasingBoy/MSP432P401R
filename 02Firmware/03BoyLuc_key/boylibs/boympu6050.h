/*
 * boympu6050.h
 *
 *  Created on: 2023��8��1��
 *      Author: 26491
 */

#ifndef BOYLIBS_BOYMPU6050_H_
#define BOYLIBS_BOYMPU6050_H_
#include "exinlibs\headfile.h"
#define SMPLRT_DIV          0x19    //�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define CONFIGL             0x1A    //��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define GYRO_CONFIG         0x1B    //�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define ACCEL_CONFIG        0x1C    //���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
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
#define PWR_MGMT_1          0x6B    //��Դ��������ֵ��0x00(��������)
#define WHO_AM_I            0x75    //IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define MPU6050_PRODUCT_ID  0x68
#define MPU6052C_PRODUCT_ID 0x72
#define MPU6050_ADDRESS     0xD0    //0x68

//���ݽṹ����
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
#define Acc_Read()          I2C_Read_Bytes(MPU6050_ADDRESS, 0x3B, buffer, 6) //��ȡ���ٶ�
#define Gyro_Read()         I2C_Read_Bytes(MPU6050_ADDRESS, 0x43, &buffer[6], 6)  //  ��ȡ���ٶ�
extern uint8_t I2C_Read_Byte(uint8_t Slaveaddr, uint8_t REG_Address);


#endif /* BOYLIBS_BOYMPU6050_H_ */
