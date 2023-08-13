/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2021��10��5��21:10:17
-------------------------------------------------------------------------------------------------------*/


#include "headfile.h"
#include "exinMPU6050.h"
#define MPU6050_ADDR      0x68

/*********************MPU6050�Ĵ�����ַ��********************************/
const uint8 MPU_reg[50]={
                    0x6b,//��Դ
                    0X6C,//��Դ2
                    0x19,//������
                    0x1a,//��ͨ�˲�
                    0x1b,//����
                    0x1c,//���ٶȼ�����
                    0x3B,//x����ٶȸ߰�λ
                    0x3C,//x����ٶȵͰ�λ
                    0x3D,//Y����ٶȸ߰�λ
                    0x3E,//Y����ٶȵͰ�λ
                    0x3F,//Z����ٶȸ߰�λ
                    0x40,//Z����ٶȵͰ�λ
                    0x41,//�¶ȸ߰�λ
                    0x42,//�¶ȵͰ�λ
                    0x43,//x��Ǽ��ٶ�
                    0x44,
                    0x45,//y��Ǽ��ٶ�
                    0x46,
                    0x47,//z��Ǽ��ٶ�
                    0x48,
                    0x23,//FIFO���üĴ���
                    0x24,//IIC��������
                    0x38,//�ж�ʹ��
                    0x37,//INT���ŵ�ƽ
                    0x6A,//�û����ƼĴ���
                    0x75,//��ַ�Ĵ���
};
/*********************MPU6050�Ĵ�����ַ��********************************/



/************************
 * ��  ��  ��:error_LED_toggle
 * ��       ��:�������ƣ���IICЭ�����ʱ��P1^0LED����˸
 * ��       ��:��
 * ע������:��
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
 * ��  ��  ��:MPU6050_write_Byte
 * ��       ��:��MPU6050дһ���ֽ�
 * ��       ��:reg(�Ĵ�����ַ),data(��Ҫд�������)
 * ע������:���˷���ֵ�������ж�����һ�׶γ��ִ���
 *****************************/
uint8 MPU6050_write_Byte(uint8 reg,uint8 data)
{
    IIC_start();//����IIC��ʼ�ź�
    IIC_Send_Byte((MPU6050_ADDR<<1)|0x00); //����������ַ+д����
    if(!Check_ACK())
    {
        IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
        error_LED_toggle();
        return 1;//����1����
    }
    IIC_Send_Byte(reg);//���ͼĴ�����ַ
    if(!Check_ACK())
    {
        IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
       // error_LED_toggle();
        return 2;//����2����
    }
    IIC_Send_Byte(data);//��������
    if(!Check_ACK())
     {
        IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
       // error_LED_toggle();
        return 3;//����2����
     }
    IIC_stop();
    return 0;//û�д���
}

/************************
 * ��  ��  ��:MPU_read_Byte
 * ��       ��:��MPU6050��ȡһ���ֽ�����
 * ��       ��:reg(�Ĵ�����ַ),data(��Ҫд�������)
 * ע������:���˷���ֵ�������ж�����һ�׶γ��ִ���
 *****************************/
uint8 MPU_read_Byte(uint8 reg)
{
    uint8 res;//�Ĵ��ȡ������
    IIC_start();//����IIC��ʼ�ź�
    IIC_Send_Byte((MPU6050_ADDR<<1)|0x00); //����������ַ+д����
    if(!Check_ACK())
    {
        IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
        //error_LED_toggle();
        return 4;//����4����
    }
    IIC_Send_Byte(reg); //д��Ĵ�����ַ
    if(!Check_ACK())
    {
        IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
        //error_LED_toggle();
        return 5;//����5����
    }
    IIC_start();//����IIC��ʼ�ź�
    IIC_Send_Byte((MPU6050_ADDR<<1)|0x010); //����������ַ+������
    if(!Check_ACK())
    {
       IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
      // error_LED_toggle();
       return 6;//����6����
    }
    res = IIC_Read_Byte(0);//������Ӧ��
    IIC_stop();
    return res;
}


/********************************************************
 * ��  ��  ��:MPU_init
 * ��       ��:MPU��ʼ������
 * ��       ��:��
 * ע������:
                    ����������:  ��2000dps
                    ���ٶ�����:  ��2g
                    ��   ��    ��:  50hz

  ��ʹ����������غ���֮ǰ��Ҫ�ȵ��øú������г�ʼ��
 ********************************************************/
void MPU_init()
{
    IIC_init();//��ʼ��IIC����
    IIC_reset();//��λIIC
    MPU6050_write_Byte(MPU_reg[POWER1],0x80);//��λMPU6050,���Դ�����Ĵ���д��0x80�Ը�λ
    delay_ms(100);//�ȴ�MPU6050��λ
    MPU6050_write_Byte(MPU_reg[POWER1],0x00);//����MPU6050
    MPU6050_write_Byte(MPU_reg[GYRO_CONFIG],3<<3);//�������������̡�2000dps
    MPU6050_write_Byte(MPU_reg[ACCEL_CONFIG],3<<3);//���ü��ٶ����̡�2g
    uint8 DIV_NUM=0;
    uint8 rate = 50;//������50hz
    DIV_NUM=1000/rate-1;//���ò�����Ϊ50HZ  1000/������  -  1
    MPU6050_write_Byte(MPU_reg[SMPLRT_DIV],DIV_NUM);//���ò�����
    MPU6050_write_Byte(MPU_reg[FILTER],4);//�����˲�������4

    MPU6050_write_Byte(MPU_reg[INT_ENABLE],0x00);//�ر������ж�
    MPU6050_write_Byte(MPU_reg[FIFO],0x00);//�ر�FIFO
    MPU6050_write_Byte(MPU_reg[USER],0x00);//I2C��ģʽ�ر�INT_PIN
    MPU6050_write_Byte(MPU_reg[INT_PIN],0x00);//���ŵ�ƽΪ0��Ч

    MPU6050_write_Byte(MPU_reg[POWER1],0x01);//ʱ��Դ
    MPU6050_write_Byte(MPU_reg[POWER2],0x00);//���ٶ��������Ǿ�����
}


/********************************************************
 * ��  ��  ��:MPU_Write_Len
 * ��       ��:MPU����д����
 * ��       ��:addr(MPU6050������ַ)��reg(�Ĵ�����ַ)��len(����д�볤��)
 *          buf(��Ҫд�����������)
 * ע������:��
 ********************************************************/
uint8 MPU_Write_Len(uint8 addr,uint8 reg,uint8 len,uint8 *buf)
{
    uint8 i;
    IIC_start();//����IIC��ʼ�ź�
    IIC_Send_Byte((addr<<1)|0x00); //����������ַ+д����
    if(!Check_ACK())
    {
       IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
       error_LED_toggle();
       return 1;//����1����
    }
    IIC_Send_Byte(reg);//���ͼĴ�����ַ
    Check_ACK();
    for(i=0;i<len;i++)
    {
        IIC_Send_Byte(buf[i]);
        if(!Check_ACK())
        {
           IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
           error_LED_toggle();
           return 1;//����1����
        }
    }
    IIC_stop();
    return 0;
}

/********************************************************
 * ��  ��  ��:MPU_Read_Len
 * ��       ��:MPU����������
 * ��       ��:addr(MPU6050������ַ)��reg(�Ĵ�����ַ)��len(����д�볤��)
 *          buf(��Ŷ���������)
 * ע������:��
 ********************************************************/
uint8 MPU_Read_Len(uint8 addr,uint8 reg,uint8 len,uint8 *buf)
{
    IIC_start();//����IIC��ʼ�ź�
   IIC_Send_Byte((addr<<1)|0x00); //����������ַ+д����
   if(!Check_ACK())
   {
      IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
      return 1;//����1����
   }
   IIC_Send_Byte(reg);//���ͼĴ�����ַ
   Check_ACK();
   IIC_start();//����IIC��ʼ�ź�

   IIC_Send_Byte((addr<<1)|0x01); //����������ַ+������
   Check_ACK();

   while(len)
   {
       if(len==1)
       {
           *buf=IIC_Read_Byte(0);//��Ӧ��
       }
       else
       {
           *buf=IIC_Read_Byte(1);//Ӧ��
       }
       len--;
       buf++;
   }
   IIC_stop();//����ֹͣ�ź�
   return 0;
}

/********************************************************
 * ��  ��  ��:MPU_Get_Temp
 * ��       ��:MPU���¶�
 * ��       ��:��
 * ע������:��
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
 * ��  ��  ��:MPU_Get_Gyro
 * ��       ��:MPU��ȡ�Ǽ��ٶ�
 * ��       ��:*gx,*gy,*gz
 * ע������:��ȡx��y��z����Ǽ��ٶ�
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
 * ��  ��  ��:MPU_Get_Acc
 * ��       ��:MPU��ȡ������ٶ�
 * ��       ��:*ax,*ay,*az
 * ע������:��ȡx��y��z����Ǽ��ٶ�
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
 * ��  ��  ��:MPU_Get_Angel
 * ��       ��:MPU��ȡ�Ƕ�
 * ��       ��:ax,ay,az,*roll,*pitch,*yaw
 * ע������:��
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