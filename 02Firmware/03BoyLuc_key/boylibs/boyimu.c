/*
 * boyimu.c
 *
 *  Created on: 2023��8��1��
 *      Author: 26491
 */
#include "boyimu.h"
//˽�б�����
Attitude_t g_Attitude;    //��ǰ�Ƕ���ֵ̬
float NormAccz;
const float RtA = 57.2957795f;
const float AtR = 0.0174532925f;
const float Gyro_G = 0.03051756f * 2;
const float Gyro_Gr = 0.0005326f * 2;
const float PI_2 = 1.570796f;

/******************************************************************************
  * �������ƣ�sine
  * ������������������ֵ
  * ��    �룺float x:�Ƕ�ֵ
  * ��    ����void
  * ��    �أ�����ֵ
  * ��    ע��null
  *
  *
******************************************************************************/
float sine(float x)          // (-M_PI , M_PI) ???? 0.0005
{
    const float Q = 0.775;
    const float P = 0.225;
    const float B =  4 / M_PI;
    const float C = -4 / (M_PI * M_PI);
    float y = B * x + C * x * fabs(x);
    return (Q * y + P * y * fabs(y));
}

/******************************************************************************
  * �������ƣ�cosine
  * ������������������ֵ
  * ��    �룺float x:�Ƕ�
  * ��    ����
  * ��    �أ�����ֵ
  * ��    ע��cos(x)=sin(M_PI / 2 + x)=sin(M_PI / 2 - x)
  *
  *
******************************************************************************/
float cosine(float x)
{
    return sine(x + M_PI / 2);
}

/******************************************************************************
  * �������ƣ�arctan
  * ���������������к���
  * ��    �룺����������
  * ��    ����void
  * ��    �أ�������ֵ
  * ��    ע���������������չ��ʽ ����Խ�ߣ�ֵԽ׼ȷ70��������׼ȷ��
  *
  *
******************************************************************************/
float arctan(float x)  //  (-1 , +1)    6? ?? 0.002958
{
    float t = x;
    float result = 0;
    float X2 = x * x;
    unsigned char cnt = 1;
    do
    {
        result += t / ((cnt << 1) - 1);
        t = -t;
        t *= X2;
        cnt++;
    }while(cnt <= 6);

    return result;
}

/******************************************************************************
  * �������ƣ�arcsin
  * ���������������Һ���
  * ��    �룺float x:����������
  * ��    ����void
  * ��    �أ�����������
  * ��    ע���������������չ��ʽ -1 < x < +1     42��������׼ȷ��
  *
  *
******************************************************************************/
float arcsin(float x)
{
    float d = 1;
    float t = x;
    unsigned char cnt = 1;
    float result = 0;
    float X2 = x * x;

    if (x >= 1.0f)
    {
        return PI_2;
    }
    if (x <= -1.0f)
    {
        return -PI_2;
    }
    do
    {
        result += t / (d * ((cnt << 1) - 1));
        t *= X2 * ((cnt << 1) - 1);//
        d *= (cnt << 1);//2 4 6 8 10 ...
        cnt++;
    }while(cnt <= 6);

    return result;
}

/******************************************************************************
  * �������ƣ�Q_rsqrt
  * �������������ټ��� 1 / Sqrt(x)
  * ��    �룺float number:Ҫ���������
  * ��    ����void
  * ��    �أ�1 / Sqrt(x)
  * ��    ע��null
  *
  *
******************************************************************************/
float Q_rsqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = *(long*) &y;
    i  = 0x5f3759df - ( i >> 1 );
    y  = *(float*) &i;
    y  = y * (threehalfs - (x2 * y * y ));   // 1st iteration ����һ��ţ�ٵ�����
    return y;
}


/******************************************************************************
  * �������ƣ�data_limit
  * ���������������޷�
  * ��    �룺float data:Ҫ����������
              float toplimit:����
              float lowerlimit:����
  * ��    ����
  * ��    �أ�
  * ��    ע��
  *
  *
******************************************************************************/
float data_limit(float data, float toplimit, float lowerlimit)
{
  if(data > toplimit)  data = toplimit;
  else if(data < lowerlimit) data = lowerlimit;
    return data;
}
/******************************************************************************
  * �������ƣ�GetAngle
  * �������������ݴ��������ݼ���õ���ǰ��̬
  * ��    �룺const MPU6050Manager_t *pMpu��ԭʼ����������
               float dt����λ����ʱ��
  * ��    ����Attitude_t *pAngE������Ƕ�ֵ
  * ��    �أ�void
  * ��    ע��null
  *
  *
******************************************************************************/
static Quaternion NumQ = {1, 0, 0, 0};
static float vecxZ,vecyZ,veczZ;
static float wz_acc_tmp[2];


void ATT_Update(const MPU6050Manager_t *pMpu,Attitude_t *pAngE, float dt)
{
  static int gravity_temp = 0;
    static int g_i = 0;
    volatile struct V{
        float x;
        float y;
        float z;
        } Gravity,Acc,Gyro,AccGravity;

    static  float KpDef = 0.4f; //��Ԫ������ֵ

    float q0_t,q1_t,q2_t,q3_t;
    float NormQuat;
    float HalfTime = dt * 0.5f;

    Gravity.x = 2 * (NumQ.q1 * NumQ.q3 - NumQ.q0 * NumQ.q2);
    Gravity.y = 2 * (NumQ.q0 * NumQ.q1 + NumQ.q2 * NumQ.q3);
    Gravity.z = 1 - 2 * (NumQ.q1 * NumQ.q1 + NumQ.q2 * NumQ.q2);
    // ���ٶȹ�һ����
    NormQuat = Q_rsqrt(squa(g_MPUManager.accX)+ squa(g_MPUManager.accY) +squa(g_MPUManager.accZ));

    Acc.x = pMpu->accX * NormQuat; //��һ��ɻ�Ϊ��λ�����·������
    Acc.y = pMpu->accY * NormQuat;
    Acc.z = pMpu->accZ * NormQuat;

    //������˵ó���ֵ����˺���Եõ���ת����������������µļ��ٶȷ����ϵ�ƫ��
    AccGravity.x = (Acc.y * Gravity.z - Acc.z * Gravity.y);
    AccGravity.y = (Acc.z * Gravity.x - Acc.x * Gravity.z);
    AccGravity.z = (Acc.x * Gravity.y - Acc.y * Gravity.x);

    //���ٶ��ںϼ��ٶȱ�������ֵ�����������乲ͬ�γ���PI�������õ�������Ľ��ٶ�ֵ
    Gyro.x = pMpu->gyroX * Gyro_Gr + KpDef * AccGravity.x;//�����ƣ��˴��������ǽ��ٶȵ�Ư��
    Gyro.y = pMpu->gyroY * Gyro_Gr + KpDef * AccGravity.y;
    Gyro.z = pMpu->gyroZ * Gyro_Gr + KpDef * AccGravity.z;

    // һ�����������, ������Ԫ��
    //������Ľ��ٶ�ֵ���֣��õ�������̬��������Ԫ��һ��ʵ��Q0�������鲿Q1~3��ֵ�ı仯
    q0_t = (-NumQ.q1 * Gyro.x - NumQ.q2 * Gyro.y - NumQ.q3 * Gyro.z) * HalfTime;
    q1_t = ( NumQ.q0 * Gyro.x - NumQ.q3 * Gyro.y + NumQ.q2 * Gyro.z) * HalfTime;
    q2_t = ( NumQ.q3 * Gyro.x + NumQ.q0 * Gyro.y - NumQ.q1 * Gyro.z) * HalfTime;
    q3_t = (-NumQ.q2 * Gyro.x + NumQ.q1 * Gyro.y + NumQ.q0 * Gyro.z) * HalfTime;

    //���ֺ��ֵ�ۼӵ��ϴε���Ԫ���У����µ���Ԫ��
    NumQ.q0 += q0_t;
    NumQ.q1 += q1_t;
    NumQ.q2 += q2_t;
    NumQ.q3 += q3_t;

    // ������Ԫ����һ�����õ���λ������
    NormQuat = Q_rsqrt(squa(NumQ.q0) + squa(NumQ.q1) + squa(NumQ.q2) + squa(NumQ.q3)); //�õ���Ԫ����ģ��
    NumQ.q0 *= NormQuat; //ģ��������Ԫ��ֵ
    NumQ.q1 *= NormQuat;
    NumQ.q2 *= NormQuat;
    NumQ.q3 *= NormQuat;

    /*��������ϵ�µ�Z��������*/
    vecxZ = 2 * NumQ.q0 *NumQ.q2 - 2 * NumQ.q1 * NumQ.q3 ;                                  /*����(3,1)��*///��������ϵ�µ�X�����������
    vecyZ = 2 * NumQ.q2 *NumQ.q3 + 2 * NumQ.q0 * NumQ.q1;                                   /*����(3,2)��*///��������ϵ�µ�Y�����������
    veczZ = NumQ.q0 * NumQ.q0 - NumQ.q1 * NumQ.q1 - NumQ.q2 * NumQ.q2 + NumQ.q3 * NumQ.q3;  /*����(3,3)��*///��������ϵ�µ�Z�����������


    NormAccz = -pMpu->accX* vecxZ + pMpu->accY * vecyZ + pMpu->accZ * veczZ;  /*Z�ᴹֱ�����ϵļ��ٶȣ���ֵ��������бʱ��Z����ٶȵ������ͣ����ǵ���������Ӧ�ó���ֵ*/

        //[I2CY EDIT] ��ʼ���������ٶ�
        if (!g_MPUManager.G)
        {
            if (g_i > 500) g_MPUManager.G = gravity_temp / 400;
            if (g_i > 100) gravity_temp += NormAccz;
            g_i ++;
        }

        wz_acc_tmp[0] = (NormAccz - g_MPUManager.G) * 0.479f;// cm/ss //0.1196f;
    wz_acc_tmp[1] += 0.1f *(wz_acc_tmp[0] - wz_acc_tmp[1]);//LPF
//    HeightInfo.Z_Acc = wz_acc_tmp[1];
}

void GetAngle(Attitude_t *pAngE)
{
    //����ŷ����
    pAngE->yaw = atan2f((2 * NumQ.q1 *NumQ.q2 + 2 * NumQ.q0 * NumQ.q3),(1 - 2 * (NumQ.q2 * NumQ.q2 + NumQ.q3 * NumQ.q3))) * RtA;
    pAngE->pitch  =  asin(vecxZ)* RtA;   //������
    pAngE->roll  = atan2f(vecyZ,veczZ) * RtA;  //�����
}

//��λ��Ԫ��
void IMU_Reset()
{
    NumQ.q0 = 1;
    NumQ.q1 = 0;
    NumQ.q2 = 0;
    NumQ.q3 = 0;
}

/******************************************************************************
  * �������ƣ�GetNormAccz
  * ��������������Z�᷽��ļ��ٶ�ֵ
  * ��    �룺void
  * ��    ��������Z�᷽��ļ��ٶ�ֵ
  * ��    �أ�void
  * ��    ע��null
  *
  *
******************************************************************************/
float GetNormAccz(void)
{
   return NormAccz;
}


