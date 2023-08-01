/*
 * boympu6050.c
 *
 *  Created on: 2023年8月1日
 *      Author: 26491
 */
#include "boympu6050.h"
//私有函数区



//私有变量区
MPU6050Manager_t g_MPUManager;   //g_MPUManager原始数据
int16_t *pMpu = (int16_t *)&g_MPUManager;
/******************************************************************************
  * 函数名称：MPU6050Init
  * 函数描述：g_MPUManager的初始化
  * 输    入：void
  * 输    出：g_MPUManager初始化结果
              0:初始化成功
              1:初始化失败
  * 返    回：
  * 备    注：
  *
  *
******************************************************************************/
uint8_t MPU6050Init(void) //初始化
{
    uint8_t check = 0;

    check = I2C_Read_Byte(MPU6050_ADDRESS, 0x75);  //判断g_MPUManager地址

    if(check != MPU6050_PRODUCT_ID) //如果地址不正确
    {
        g_MPUManager.Check = 1;
        return 1;
    }
    else
    {
        delay_ms(200);
        I2C_Write_Byte(MPU6050_ADDRESS, PWR_MGMT_1,    0x80);   //复位
        delay_ms(200);
        I2C_Write_Byte(MPU6050_ADDRESS, SMPLRT_DIV,   0x00);   //陀螺仪采样率，0x00(1000Hz)
        delay_ms(10);
        I2C_Write_Byte(MPU6050_ADDRESS, PWR_MGMT_1,   0x03);   //设置设备时钟源，陀螺仪Z轴
        delay_ms(10);
        I2C_Write_Byte(MPU6050_ADDRESS, CONFIGL,      0x04);   //低通滤波频率，0x03(42Hz)
        delay_ms(10);
        I2C_Write_Byte(MPU6050_ADDRESS, GYRO_CONFIG,  0x18);   //+-2000deg/s
        delay_ms(10);
        I2C_Write_Byte(MPU6050_ADDRESS, ACCEL_CONFIG, 0x18);   //+-16
        delay_ms(10);

        GetMPU6050Offset(); //调用校准数据
        g_MPUManager.Check = 0;
        g_MPUManager.G = 0;
        return 0;
    }
}

/******************************************************************************
  * 函数名称：GetMPU6050Data
  * 函数描述：读取陀螺仪和加速度计的数据并做滤波处理
  * 输    入：void
  * 输    出：void
  * 返    回：void
  * 备    注：null
  *
  *
******************************************************************************/
uint32_t test_6050time[3];
void GetMPU6050Data(void)
{
    int i,k;
    static float mpu_filter[2][6];
    int16_t mpu_filter_tmp[6];
    uint8_t buffer[12];

    //读取加速度计数据和陀螺仪数据
    Acc_Read();
    Gyro_Read();


    for( i = 0; i < 6; i++)
    {
        //拼接读取到的原始数据
        mpu_filter_tmp[i] = (((int16_t)buffer[i << 1] << 8) | buffer[(i << 1) + 1])
                - g_MPUManager.Offset[i];

        //原始数据LPF
        mpu_filter[0][i] += 0.27f *(mpu_filter_tmp[i] - mpu_filter[0][i]);
        mpu_filter[1][i] += 0.5f *(mpu_filter[0][i]  - mpu_filter[1][i]);

        //赋值到结构体
        //pMpu[i] = (int16_t)mpu_filter[1][i];

        //[I2CY EDIT]
//      pMpu[0] = (int16_t)mpu_filter[1][1];  //AccX   XY轴交换
//      pMpu[1] = (int16_t)mpu_filter[1][0];  //AccY   YX轴交换
//      pMpu[2] = -(int16_t)mpu_filter[1][2]; //AccZ   Z轴翻转
//      pMpu[3] = (int16_t)mpu_filter[1][4];  //GyroX  XY轴交换
//      pMpu[4] = (int16_t)mpu_filter[1][3];  //GyroY  YX轴交换
//      pMpu[5] = -(int16_t)mpu_filter[1][5]; //GyroZ  Z轴翻转

        //[END EDIT]
    }

    pMpu[0] = (int16_t)mpu_filter[1][0];  //AccX   XY轴
    pMpu[1] = (int16_t)mpu_filter[1][1];  //AccY   YX轴
    pMpu[2] = (int16_t)mpu_filter[1][2]; //AccZ   Z轴
    pMpu[3] = (int16_t)mpu_filter[1][3];  //GyroX  XY轴
    pMpu[4] = (int16_t)mpu_filter[1][4];  //GyroY  YX轴
    pMpu[5] = (int16_t)mpu_filter[1][5]; //GyroZ  Z轴

}

/******************************************************************************
  * 函数名称：GetMPU6050Offset
  * 函数描述：获取g_MPUManager静态下传感器偏差
  * 输    入：void
  * 输    出：void
  * 返    回：void
  * 备    注：null
  *
  *
******************************************************************************/
void GetMPU6050Offset(void) //校准
{
    int32_t buffer[6] = { 0 };
    int16_t i = 0;
    int16_t temp = 0;
    int k;
    const int8_t MAX_GYRO_QUIET = 5;

    int16_t LastGyro[3] = {0};          /*wait for calm down*/
    int16_t ErrorGyro[3] = {0};         /*set offset initial to zero*/

    memset(g_MPUManager.Offset, 0, 12);
    g_MPUManager.Offset[2] = 2048;   //根据手册量程设定加速度标定值[I2CY EDIT]

    //丢弃前300个数据
    for( i = 0;i < 300;i++)
    {
        delay_ms(2);
        GetMPU6050Data();
    }

//    //判断飞机是否平方，防止斜放开机
//    while(1)
//    {
//        static int cnt = 0;
//        cnt++;
//
//        delay_ms(2);
//        GetMPU6050Data();
//
//        if(g_MPUManager.accX < 400 && g_MPUManager.accX > -400 &&
//           g_MPUManager.accY < 400 && g_MPUManager.accY > -400 &&
//           g_MPUManager.accZ < 400 && g_MPUManager.accZ > -400)
//        {
//            if (cnt > 2 * 500 * 2)
//            {
//                break;
//            }
//        }else
//        {
//            cnt = 0;
//        }
//    }
//
//    //判定飞机是否已经稳定
//    while(1)
//    {
//        if(abs(g_MPUManager.gyroX) != 0 ||
//           abs(g_MPUManager.gyroY) != 0 ||
//           abs(g_MPUManager.gyroZ) != 0)
//        {
//            for(i = 0; i < 3; i++)
//            {
//                ErrorGyro[i] = pMpu[i + 3] - LastGyro[i];
//                LastGyro[i] = pMpu[i + 3];
//            }
//
//            if(abs(ErrorGyro[0]) < MAX_GYRO_QUIET &&
//               abs(ErrorGyro[1]) < MAX_GYRO_QUIET &&
//               abs(ErrorGyro[2]) < MAX_GYRO_QUIET)
//            {
//                break;
//            }
//        }
//    }


    //取第100到第356组的平均值做为校准值
    for(i = 0; i < 356; i++)
    {
        GetMPU6050Data();

        if(100 <= i)
        {
            for( k = 0; k < 6; k++)
            {
                buffer[k] += pMpu[k];
            }
        }
    }

    //保存校准值
    for(i = 0; i < 6; i++)
    {
        //右移8位，数据除以256
        g_MPUManager.Offset[i] = buffer[i] >> 8;

    }

    //[I2CY EDIT] 兼容化翻转标定值

//  temp = g_MPUManager.Offset[0];
//  g_MPUManager.Offset[0] = g_MPUManager.Offset[1];    // AccX
//  g_MPUManager.Offset[1] = temp;                      // AccY
//  temp = g_MPUManager.Offset[3];
//  g_MPUManager.Offset[3] = g_MPUManager.Offset[4];    // GyroX
//  g_MPUManager.Offset[4] = temp;                      // GyroY
//  g_MPUManager.Offset[5] = -g_MPUManager.Offset[5];

    //取第100到256组的平均值做为重力加速度测量值[I2CY EDIT]
    for(i = 0; i < 356; i++)
    {
        GetMPU6050Data();

        if(100 <= i)
        {
            for( k = 0; k < 6; k++)
            {
                buffer[k] += pMpu[k];
            }
        }
    }

    //[END EDIT]
}

