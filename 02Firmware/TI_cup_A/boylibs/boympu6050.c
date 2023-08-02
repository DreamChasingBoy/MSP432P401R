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

    memset(g_MPUManager.Offset, 0, 12);
    g_MPUManager.Offset[2] = 2048;   //根据手册量程设定加速度标定值[I2CY EDIT]

    //丢弃前300个数据
    for( i = 0;i < 300;i++)
    {
        delay_ms(2);
        GetMPU6050Data();
    }

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
/**/
Attitude_t g_Attitude;    //当前角度姿态值
float NormAccz;
const float RtA = 57.2957795f;
const float AtR = 0.0174532925f;
const float Gyro_G = 0.03051756f * 2;
const float Gyro_Gr = 0.0005326f * 2;
const float PI_2 = 1.570796f;

/******************************************************************************
  * 函数名称：sine
  * 函数描述：返回正弦值
  * 输    入：float x:角度值
  * 输    出：void
  * 返    回：正弦值
  * 备    注：null
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
  * 函数名称：cosine
  * 函数描述：计算余弦值
  * 输    入：float x:角度
  * 输    出：
  * 返    回：余弦值
  * 备    注：cos(x)=sin(M_PI / 2 + x)=sin(M_PI / 2 - x)
  *
  *
******************************************************************************/
float cosine(float x)
{
    return sine(x + M_PI / 2);
}

/******************************************************************************
  * 函数名称：arctan
  * 函数描述：反正切函数
  * 输    入：反正切数据
  * 输    出：void
  * 返    回：反正切值
  * 备    注：反正切麦克劳林展开式 阶数越高，值越准确70°以内是准确的
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
  * 函数名称：arcsin
  * 函数描述：反正弦函数
  * 输    入：float x:反正弦数据
  * 输    出：void
  * 返    回：反正弦数据
  * 备    注：反正弦麦克劳林展开式 -1 < x < +1     42°以内是准确的
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
  * 函数名称：Q_rsqrt
  * 函数描述：快速计算 1 / Sqrt(x)
  * 输    入：float number:要计算的数据
  * 输    出：void
  * 返    回：1 / Sqrt(x)
  * 备    注：null
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
    y  = y * (threehalfs - (x2 * y * y ));   // 1st iteration （第一次牛顿迭代）
    return y;
}


/******************************************************************************
  * 函数名称：data_limit
  * 函数描述：数据限幅
  * 输    入：float data:要操作的数据
              float toplimit:上限
              float lowerlimit:下限
  * 输    出：
  * 返    回：
  * 备    注：
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
  * 函数名称：GetAngle
  * 函数描述：根据传感器数据计算得到当前姿态
  * 输    入：const MPU6050Manager_t *pMpu：原始传感器数据
               float dt：单位运行时间
  * 输    出：Attitude_t *pAngE：输出角度值
  * 返    回：void
  * 备    注：null
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

    static  float KpDef = 0.4f; //四元数收勉值

    float q0_t,q1_t,q2_t,q3_t;
    float NormQuat;
    float HalfTime = dt * 0.5f;

    Gravity.x = 2 * (NumQ.q1 * NumQ.q3 - NumQ.q0 * NumQ.q2);
    Gravity.y = 2 * (NumQ.q0 * NumQ.q1 + NumQ.q2 * NumQ.q3);
    Gravity.z = 1 - 2 * (NumQ.q1 * NumQ.q1 + NumQ.q2 * NumQ.q2);
    // 加速度归一化，
    NormQuat = Q_rsqrt(squa(g_MPUManager.accX)+ squa(g_MPUManager.accY) +squa(g_MPUManager.accZ));

    Acc.x = pMpu->accX * NormQuat; //归一后可化为单位向量下方向分量
    Acc.y = pMpu->accY * NormQuat;
    Acc.z = pMpu->accZ * NormQuat;

    //向量叉乘得出的值，叉乘后可以得到旋转矩阵的重力分量在新的加速度分量上的偏差
    AccGravity.x = (Acc.y * Gravity.z - Acc.z * Gravity.y);
    AccGravity.y = (Acc.z * Gravity.x - Acc.x * Gravity.z);
    AccGravity.z = (Acc.x * Gravity.y - Acc.y * Gravity.x);

    //角速度融合加速度比例补偿值，与上面三句共同形成了PI补偿，得到矫正后的角速度值
    Gyro.x = pMpu->gyroX * Gyro_Gr + KpDef * AccGravity.x;//弧度制，此处补偿的是角速度的漂移
    Gyro.y = pMpu->gyroY * Gyro_Gr + KpDef * AccGravity.y;
    Gyro.z = pMpu->gyroZ * Gyro_Gr + KpDef * AccGravity.z;

    // 一阶龙格库塔法, 更新四元数
    //矫正后的角速度值积分，得到两次姿态解算中四元数一个实部Q0，三个虚部Q1~3的值的变化
    q0_t = (-NumQ.q1 * Gyro.x - NumQ.q2 * Gyro.y - NumQ.q3 * Gyro.z) * HalfTime;
    q1_t = ( NumQ.q0 * Gyro.x - NumQ.q3 * Gyro.y + NumQ.q2 * Gyro.z) * HalfTime;
    q2_t = ( NumQ.q3 * Gyro.x + NumQ.q0 * Gyro.y - NumQ.q1 * Gyro.z) * HalfTime;
    q3_t = (-NumQ.q2 * Gyro.x + NumQ.q1 * Gyro.y + NumQ.q0 * Gyro.z) * HalfTime;

    //积分后的值累加到上次的四元数中，即新的四元数
    NumQ.q0 += q0_t;
    NumQ.q1 += q1_t;
    NumQ.q2 += q2_t;
    NumQ.q3 += q3_t;

    // 重新四元数归一化，得到单位向量下
    NormQuat = Q_rsqrt(squa(NumQ.q0) + squa(NumQ.q1) + squa(NumQ.q2) + squa(NumQ.q3)); //得到四元数的模长
    NumQ.q0 *= NormQuat; //模长更新四元数值
    NumQ.q1 *= NormQuat;
    NumQ.q2 *= NormQuat;
    NumQ.q3 *= NormQuat;

    /*机体坐标系下的Z方向向量*/
    vecxZ = 2 * NumQ.q0 *NumQ.q2 - 2 * NumQ.q1 * NumQ.q3 ;                                  /*矩阵(3,1)项*///地理坐标系下的X轴的重力分量
    vecyZ = 2 * NumQ.q2 *NumQ.q3 + 2 * NumQ.q0 * NumQ.q1;                                   /*矩阵(3,2)项*///地理坐标系下的Y轴的重力分量
    veczZ = NumQ.q0 * NumQ.q0 - NumQ.q1 * NumQ.q1 - NumQ.q2 * NumQ.q2 + NumQ.q3 * NumQ.q3;  /*矩阵(3,3)项*///地理坐标系下的Z轴的重力分量


//    NormAccz = -pMpu->accX* vecxZ + pMpu->accY * vecyZ + pMpu->accZ * veczZ;  /*Z轴垂直方向上的加速度，此值涵盖了倾斜时在Z轴角速度的向量和，不是单纯重力感应得出的值*/
//
//    //[I2CY EDIT] 初始化重力加速度
//    if (!g_MPUManager.G)
//    {
//        if (g_i > 500) g_MPUManager.G = gravity_temp / 400;
//        if (g_i > 100) gravity_temp += NormAccz;
//        g_i ++;
//    }
//
//    wz_acc_tmp[0] = (NormAccz - g_MPUManager.G) * 0.479f;// cm/ss //0.1196f;
//    wz_acc_tmp[1] += 0.1f *(wz_acc_tmp[0] - wz_acc_tmp[1]);//LPF
//    HeightInfo.Z_Acc = wz_acc_tmp[1];
}


void GetAngle(Attitude_t *pAngE)
{
    //更新欧拉角
    pAngE->yaw = atan2f((2 * NumQ.q1 *NumQ.q2 + 2 * NumQ.q0 * NumQ.q3),(1 - 2 * (NumQ.q2 * NumQ.q2 + NumQ.q3 * NumQ.q3))) * RtA;
    pAngE->pitch  =  asin(vecxZ)* RtA;   //俯仰角
    pAngE->roll  = atan2f(vecyZ,veczZ) * RtA;  //横滚角
}

//复位四元数
void IMU_Reset()
{
    NumQ.q0 = 1;
    NumQ.q1 = 0;
    NumQ.q2 = 0;
    NumQ.q3 = 0;
}

/******************************************************************************
  * 函数名称：GetNormAccz
  * 函数描述：返回Z轴方向的加速度值
  * 输    入：void
  * 输    出：返回Z轴方向的加速度值
  * 返    回：void
  * 备    注：null
  *
  *
******************************************************************************/
float GetNormAccz(void)
{
   return NormAccz;
}

