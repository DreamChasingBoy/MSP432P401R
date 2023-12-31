/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年10月5日21:10:17
-------------------------------------------------------------------------------------------------------*/


#include "headfile.h"
#include "exinMPU6050.h"
#define MPU6050_ADDR      0x68

/*********************MPU6050寄存器地址表********************************/
const uint8 MPU_reg[50]={
                    0x6b,//电源
                    0X6C,//电源2
                    0x19,//采样率
                    0x1a,//低通滤波
                    0x1b,//量程
                    0x1c,//加速度计量程
                    0x3B,//x轴加速度高八位
                    0x3C,//x轴加速度低八位
                    0x3D,//Y轴加速度高八位
                    0x3E,//Y轴加速度低八位
                    0x3F,//Z轴加速度高八位
                    0x40,//Z轴加速度低八位
                    0x41,//温度高八位
                    0x42,//温度低八位
                    0x43,//x轴角加速度
                    0x44,
                    0x45,//y轴角加速度
                    0x46,
                    0x47,//z轴角加速度
                    0x48,
                    0x23,//FIFO配置寄存器
                    0x24,//IIC总线配置
                    0x38,//中断使能
                    0x37,//INT引脚电平
                    0x6A,//用户控制寄存器
                    0x75,//地址寄存器
};
/*********************MPU6050寄存器地址表********************************/



/************************
 * 函  数  名:error_LED_toggle
 * 功       能:错误闪灯，当IIC协议错误时，P1^0LED将闪烁
 * 参       数:无
 * 注意事项:无
 *****************************/
void error_LED_toggle()
{
    while(1)
    {
    gpio_toggle(GPIO_PORT_P1,GPIO_PIN0);
    delay_ms(200);
    }
}
#ifndef __MPU6050_H
/************************
 * 函  数  名:MPU6050_write_Byte
 * 功       能:向MPU6050写一个字节
 * 参       数:reg(寄存器地址),data(需要写入的数据)
 * 注意事项:检测此返回值，可以判断在哪一阶段出现错误
 *****************************/
uint8 MPU6050_write_Byte(uint8 reg,uint8 data)
{
    IIC_start();//产生IIC开始信号
    IIC_Send_Byte((MPU6050_ADDR<<1)|0x00); //发送器件地址+写命令
    if(!Check_ACK())
    {
        IIC_stop();//没有检测到应答信号就发送结束信号
        error_LED_toggle();
        return 1;//发送1错误
    }
    IIC_Send_Byte(reg);//发送寄存器地址
    if(!Check_ACK())
    {
        IIC_stop();//没有检测到应答信号就发送结束信号
       // error_LED_toggle();
        return 2;//发送2错误
    }
    IIC_Send_Byte(data);//发送数据
    if(!Check_ACK())
     {
        IIC_stop();//没有检测到应答信号就发送结束信号
       // error_LED_toggle();
        return 3;//发送2错误
     }
    IIC_stop();
    return 0;//没有错误
}

/************************
 * 函  数  名:MPU_read_Byte
 * 功       能:对MPU6050读取一个字节数据
 * 参       数:reg(寄存器地址),data(需要写入的数据)
 * 注意事项:检测此返回值，可以判断在哪一阶段出现错误
 *****************************/
uint8 MPU_read_Byte(uint8 reg)
{
    uint8 res;//寄存读取的数据
    IIC_start();//产生IIC开始信号
    IIC_Send_Byte((MPU6050_ADDR<<1)|0x00); //发送器件地址+写命令
    if(!Check_ACK())
    {
        IIC_stop();//没有检测到应答信号就发送结束信号
        //error_LED_toggle();
        return 4;//发送4错误
    }
    IIC_Send_Byte(reg); //写入寄存器地址
    if(!Check_ACK())
    {
        IIC_stop();//没有检测到应答信号就发送结束信号
        //error_LED_toggle();
        return 5;//发送5错误
    }
    IIC_start();//产生IIC开始信号
    IIC_Send_Byte((MPU6050_ADDR<<1)|0x010); //发送器件地址+读命令
    if(!Check_ACK())
    {
       IIC_stop();//没有检测到应答信号就发送结束信号
      // error_LED_toggle();
       return 6;//发送6错误
    }
    res = IIC_Read_Byte(0);//主机不应答
    IIC_stop();
    return res;
}


/********************************************************
 * 函  数  名:MPU_init
 * 功       能:MPU初始化程序
 * 参       数:无
 * 注意事项:
                    陀螺仪量程:  ±2000dps
                    加速度量程:  ±2g
                    采   样    率:  50hz

  在使用陀螺仪相关函数之前需要先调用该函数进行初始化
 ********************************************************/
void MPU_init()
{
    IIC_init();//初始化IIC总线
    IIC_reset();//复位IIC
    MPU6050_write_Byte(MPU_reg[POWER1],0x80);//复位MPU6050,向电源管理寄存器写入0x80以复位
    delay_ms(100);//等待MPU6050复位
    MPU6050_write_Byte(MPU_reg[POWER1],0x00);//启动MPU6050
    MPU6050_write_Byte(MPU_reg[GYRO_CONFIG],3<<3);//设置陀螺仪量程±2000dps
    MPU6050_write_Byte(MPU_reg[ACCEL_CONFIG],3<<3);//设置加速度量程±2g
    uint8 DIV_NUM=0;
    uint8 rate = 50;//采样率50hz
    DIV_NUM=1000/rate-1;//设置采样率为50HZ  1000/采样率  -  1
    MPU6050_write_Byte(MPU_reg[SMPLRT_DIV],DIV_NUM);//设置采样率
    MPU6050_write_Byte(MPU_reg[FILTER],4);//设置滤波器长度4

    MPU6050_write_Byte(MPU_reg[INT_ENABLE],0x00);//关闭所有中断
    MPU6050_write_Byte(MPU_reg[FIFO],0x00);//关闭FIFO
    MPU6050_write_Byte(MPU_reg[USER],0x00);//I2C主模式关闭INT_PIN
    MPU6050_write_Byte(MPU_reg[INT_PIN],0x00);//引脚电平为0有效

    MPU6050_write_Byte(MPU_reg[POWER1],0x01);//时钟源
    MPU6050_write_Byte(MPU_reg[POWER2],0x00);//加速度与陀螺仪均工作
}


/********************************************************
 * 函  数  名:MPU_Write_Len
 * 功       能:MPU连续写函数
 * 参       数:addr(MPU6050器件地址)、reg(寄存器地址)、len(连续写入长度)
 *          buf(需要写入的数据数组)
 * 注意事项:无
 ********************************************************/
uint8 MPU_Write_Len(uint8 addr,uint8 reg,uint8 len,uint8 *buf)
{
    uint8 i;
    IIC_start();//产生IIC开始信号
    IIC_Send_Byte((addr<<1)|0x00); //发送器件地址+写命令
    if(!Check_ACK())
    {
       IIC_stop();//没有检测到应答信号就发送结束信号
       error_LED_toggle();
       return 1;//发送1错误
    }
    IIC_Send_Byte(reg);//发送寄存器地址
    Check_ACK();
    for(i=0;i<len;i++)
    {
        IIC_Send_Byte(buf[i]);
        if(!Check_ACK())
        {
           IIC_stop();//没有检测到应答信号就发送结束信号
           error_LED_toggle();
           return 1;//发送1错误
        }
    }
    IIC_stop();
    return 0;
}

/********************************************************
 * 函  数  名:MPU_Read_Len
 * 功       能:MPU连续读函数
 * 参       数:addr(MPU6050器件地址)、reg(寄存器地址)、len(连续写入长度)
 *          buf(存放读出的数据)
 * 注意事项:无
 ********************************************************/
uint8 MPU_Read_Len(uint8 addr,uint8 reg,uint8 len,uint8 *buf)
{
    IIC_start();//产生IIC开始信号
   IIC_Send_Byte((addr<<1)|0x00); //发送器件地址+写命令
   if(!Check_ACK())
   {
      IIC_stop();//没有检测到应答信号就发送结束信号
      return 1;//发送1错误
   }
   IIC_Send_Byte(reg);//发送寄存器地址
   Check_ACK();
   IIC_start();//产生IIC开始信号

   IIC_Send_Byte((addr<<1)|0x01); //发送器件地址+读命令
   Check_ACK();

   while(len)
   {
       if(len==1)
       {
           *buf=IIC_Read_Byte(0);//不应答
       }
       else
       {
           *buf=IIC_Read_Byte(1);//应答
       }
       len--;
       buf++;
   }
   IIC_stop();//发送停止信号
   return 0;
}

/********************************************************
 * 函  数  名:MPU_Get_Temp
 * 功       能:MPU读温度
 * 参       数:无
 * 注意事项:无
 ********************************************************/
extern uint8 tmp;
short MPU_Get_Temp()
{
    uint8 Temp_buf[2];

    short raw;
    float temp;

    MPU_Read_Len(MPU6050_ADDR,MPU_reg[TEMP_H],2,Temp_buf);

    raw=((uint8)Temp_buf[0]<<8)|Temp_buf[1];
    temp =36.53+((double)raw)/340;
    return temp*100;
}
/********************************************************
 * 函  数  名:MPU_Get_Gyro
 * 功       能:MPU获取角加速度
 * 参       数:*gx,*gy,*gz
 * 注意事项:读取x，y，z三轴角加速度
 ********************************************************/
uint8 MPU_Get_Gyro(short * gx,short * gy,short * gz)
{
    uint8 buf[6],res;
    res=MPU_Read_Len(MPU6050_ADDR,MPU_reg[GX_H],6,buf);
    if(res==0)
    {
        *gx=((uint16)buf[0]<<8)|buf[1];
        *gy=((uint16)buf[2]<<8)|buf[3];
        *gz=((uint16)buf[4]<<8)|buf[5];
    }
    return res;
}
/********************************************************
 * 函  数  名:MPU_Get_Acc
 * 功       能:MPU获取三轴加速度
 * 参       数:*ax,*ay,*az
 * 注意事项:读取x，y，z三轴角加速度
 ********************************************************/
uint8 MPU_Get_Acc(short * ax,short * ay,short * az)
{
    uint8 buf[6],res;
    res=MPU_Read_Len(MPU6050_ADDR,MPU_reg[AX_H],6,buf);
    if(res==0)
    {
        *ax = ((uint16)buf[0]<<8)|buf[1];
        *ay = ((uint16)buf[2]<<8)|buf[3];
        *az = ((uint16)buf[4]<<8)|buf[5];
    }
    return res;
}
/********************************************************
 * 函  数  名:MPU_Get_Angel
 * 功       能:MPU获取角度
 * 参       数:ax,ay,az,*roll,*pitch,*yaw
 * 注意事项:无
 ********************************************************/
short MPU_Get_Angel(short ax,short ay,short az,float * roll,float * pitch,float *yaw)
{
    float accAngelX,accAngelY,accAngelZ,AccX,AccY,AccZ;

    AccX=(float)ax/16384.0;
    AccY=(float)ay/16384.0;
    AccZ=(float)az/16384.0;

    accAngelZ = atan(sqrt(AccX*AccX+AccY*AccY)/AccZ );
    accAngelX = atan( AccX/sqrt(AccY*AccY+AccZ*AccZ));
    accAngelY = atan( AccY/sqrt(AccX*AccX+AccZ*AccZ));

    *pitch = accAngelX*180/PI;
    *roll = accAngelY*180/PI;
    *yaw = accAngelZ*180/PI;

    return 0;
}

float Low_filter(float K1,float angle_m, float gyro_m)
{
  float angle;
  angle = K1 * angle_m+ (1-K1) * (angle + gyro_m * 0.005);//0.005
  return angle;
}
#endif
