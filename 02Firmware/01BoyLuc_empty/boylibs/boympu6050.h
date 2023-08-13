/*
 * boympu6050.h
 *
 *  Created on: 2023��8��1��
 *      Author: BoyLuc׷����������
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
#define PI 3.1415926f
#define squa( Sq )        (((float)Sq)*((float)Sq))
#define absu16( Math_X )  ((Math_X)<0? -(Math_X):(Math_X))
#define absFloat( Math_X )((Math_X)<0? -(Math_X):(Math_X))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define ABS(x) ((x) > 0 ? (x) : -(x))
#define LIMIT( x, min, max ) ( (x) <= (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )
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
typedef struct{
    float roll;
    float pitch;
    float yaw;
}Attitude_t;

typedef struct {  //��Ԫ��
  float q0;
  float q1;
  float q2;
  float q3;
} Quaternion;
float GetNormAccz(void);
void ATT_Update(const MPU6050Manager_t *pMpu,Attitude_t *pAngE, float dt);
void GetAngle(Attitude_t *pAngE);
void IMU_Reset(void);
//Extern����
extern Attitude_t g_Attitude;    //��ǰ�Ƕ���ֵ̬
extern const float AtR;
extern const float RtA;
extern const float Gyro_G;
extern const float Gyro_Gr;

//��������
extern float safe_asin(float v);
extern float arcsin(float x);
extern float arctan(float x);
extern float sine(float x);
extern float cosine(float x);
extern float Q_rsqrt(float number);
extern float VariableParameter(float error);
/***/
extern MPU6050Manager_t g_MPUManager;
uint8_t MPU6050Init(void);
void GetMPU6050Data(void);
void GetMPU6050Offset(void);
#define Acc_Read()          I2C_Read_Bytes(MPU6050_ADDRESS, 0x3B, buffer, 6) //��ȡ���ٶ�
#define Gyro_Read()         I2C_Read_Bytes(MPU6050_ADDRESS, 0x43, &buffer[6], 6)  //  ��ȡ���ٶ�
extern uint8_t I2C_Read_Byte(uint8_t Slaveaddr, uint8_t REG_Address);


#endif /* BOYLIBS_BOYMPU6050_H_ */
