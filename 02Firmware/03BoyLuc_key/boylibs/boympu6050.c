/*
 * boympu6050.c
 *
 *  Created on: 2023��8��1��
 *      Author: 26491
 */
#include "boympu6050.h"
//˽�к�����



//˽�б�����
MPU6050Manager_t g_MPUManager;   //g_MPUManagerԭʼ����
int16_t *pMpu = (int16_t *)&g_MPUManager;
/******************************************************************************
  * �������ƣ�MPU6050Init
  * ����������g_MPUManager�ĳ�ʼ��
  * ��    �룺void
  * ��    ����g_MPUManager��ʼ�����
              0:��ʼ���ɹ�
              1:��ʼ��ʧ��
  * ��    �أ�
  * ��    ע��
  *
  *
******************************************************************************/
uint8_t MPU6050Init(void) //��ʼ��
{
    uint8_t check = 0;

    check = I2C_Read_Byte(MPU6050_ADDRESS, 0x75);  //�ж�g_MPUManager��ַ

    if(check != MPU6050_PRODUCT_ID) //�����ַ����ȷ
    {
        g_MPUManager.Check = 1;
        return 1;
    }
    else
    {
        delay_ms(200);
        I2C_Write_Byte(MPU6050_ADDRESS, PWR_MGMT_1,    0x80);   //��λ
        delay_ms(200);
        I2C_Write_Byte(MPU6050_ADDRESS, SMPLRT_DIV,   0x00);   //�����ǲ����ʣ�0x00(1000Hz)
        delay_ms(10);
        I2C_Write_Byte(MPU6050_ADDRESS, PWR_MGMT_1,   0x03);   //�����豸ʱ��Դ��������Z��
        delay_ms(10);
        I2C_Write_Byte(MPU6050_ADDRESS, CONFIGL,      0x04);   //��ͨ�˲�Ƶ�ʣ�0x03(42Hz)
        delay_ms(10);
        I2C_Write_Byte(MPU6050_ADDRESS, GYRO_CONFIG,  0x18);   //+-2000deg/s
        delay_ms(10);
        I2C_Write_Byte(MPU6050_ADDRESS, ACCEL_CONFIG, 0x18);   //+-16
        delay_ms(10);

        GetMPU6050Offset(); //����У׼����
        g_MPUManager.Check = 0;
        g_MPUManager.G = 0;
        return 0;
    }
}

/******************************************************************************
  * �������ƣ�GetMPU6050Data
  * ������������ȡ�����Ǻͼ��ٶȼƵ����ݲ����˲�����
  * ��    �룺void
  * ��    ����void
  * ��    �أ�void
  * ��    ע��null
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

    //��ȡ���ٶȼ����ݺ�����������
    Acc_Read();
    Gyro_Read();


    for( i = 0; i < 6; i++)
    {
        //ƴ�Ӷ�ȡ����ԭʼ����
        mpu_filter_tmp[i] = (((int16_t)buffer[i << 1] << 8) | buffer[(i << 1) + 1])
                - g_MPUManager.Offset[i];

        //ԭʼ����LPF
        mpu_filter[0][i] += 0.27f *(mpu_filter_tmp[i] - mpu_filter[0][i]);
        mpu_filter[1][i] += 0.5f *(mpu_filter[0][i]  - mpu_filter[1][i]);

        //��ֵ���ṹ��
        //pMpu[i] = (int16_t)mpu_filter[1][i];

        //[I2CY EDIT]
//      pMpu[0] = (int16_t)mpu_filter[1][1];  //AccX   XY�ύ��
//      pMpu[1] = (int16_t)mpu_filter[1][0];  //AccY   YX�ύ��
//      pMpu[2] = -(int16_t)mpu_filter[1][2]; //AccZ   Z�ᷭת
//      pMpu[3] = (int16_t)mpu_filter[1][4];  //GyroX  XY�ύ��
//      pMpu[4] = (int16_t)mpu_filter[1][3];  //GyroY  YX�ύ��
//      pMpu[5] = -(int16_t)mpu_filter[1][5]; //GyroZ  Z�ᷭת

        //[END EDIT]
    }

    pMpu[0] = (int16_t)mpu_filter[1][0];  //AccX   XY��
    pMpu[1] = (int16_t)mpu_filter[1][1];  //AccY   YX��
    pMpu[2] = (int16_t)mpu_filter[1][2]; //AccZ   Z��
    pMpu[3] = (int16_t)mpu_filter[1][3];  //GyroX  XY��
    pMpu[4] = (int16_t)mpu_filter[1][4];  //GyroY  YX��
    pMpu[5] = (int16_t)mpu_filter[1][5]; //GyroZ  Z��

}

/******************************************************************************
  * �������ƣ�GetMPU6050Offset
  * ������������ȡg_MPUManager��̬�´�����ƫ��
  * ��    �룺void
  * ��    ����void
  * ��    �أ�void
  * ��    ע��null
  *
  *
******************************************************************************/
void GetMPU6050Offset(void) //У׼
{
    int32_t buffer[6] = { 0 };
    int16_t i = 0;
    int16_t temp = 0;
    int k;
    const int8_t MAX_GYRO_QUIET = 5;

    int16_t LastGyro[3] = {0};          /*wait for calm down*/
    int16_t ErrorGyro[3] = {0};         /*set offset initial to zero*/

    memset(g_MPUManager.Offset, 0, 12);
    g_MPUManager.Offset[2] = 2048;   //�����ֲ������趨���ٶȱ궨ֵ[I2CY EDIT]

    //����ǰ300������
    for( i = 0;i < 300;i++)
    {
        delay_ms(2);
        GetMPU6050Data();
    }

//    //�жϷɻ��Ƿ�ƽ������ֹб�ſ���
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
//    //�ж��ɻ��Ƿ��Ѿ��ȶ�
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


    //ȡ��100����356���ƽ��ֵ��ΪУ׼ֵ
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

    //����У׼ֵ
    for(i = 0; i < 6; i++)
    {
        //����8λ�����ݳ���256
        g_MPUManager.Offset[i] = buffer[i] >> 8;

    }

    //[I2CY EDIT] ���ݻ���ת�궨ֵ

//  temp = g_MPUManager.Offset[0];
//  g_MPUManager.Offset[0] = g_MPUManager.Offset[1];    // AccX
//  g_MPUManager.Offset[1] = temp;                      // AccY
//  temp = g_MPUManager.Offset[3];
//  g_MPUManager.Offset[3] = g_MPUManager.Offset[4];    // GyroX
//  g_MPUManager.Offset[4] = temp;                      // GyroY
//  g_MPUManager.Offset[5] = -g_MPUManager.Offset[5];

    //ȡ��100��256���ƽ��ֵ��Ϊ�������ٶȲ���ֵ[I2CY EDIT]
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

