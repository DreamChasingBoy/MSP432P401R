/*
 * boyiic.c
 *
 *  Created on: 2023��8��1��
 *      Author: 26491
 */

#include "boyiic.h"
//˽�к�����
void IIC_SendByte(uint32_t dat);
void IIC_RecvACK(void);
void IIC_SendACK(uint32_t ack);
void IIC_Stop(void);
uint32_t IIC_RecvByte(void);
void IIC_Start(void);

//˽�б�����
unsigned char Ack_Count = 0;

/******************************************************************************
  * �������ƣ�I2C_Init
  * ������������ʼ��I2c����
  * ��    �룺void
  * ��    ����void
  * ��    �أ�void
  * ��    ע��null
  *
  *
******************************************************************************/
void I2C_Init(void)
{
    P6DIR |= (1 << SCL);
}

/******************************************************************************
  * �������ƣ�delay
  * ����������I2c��ʱ
  * ��    �룺
  * uint32_t n:��ʱ������
  * ��    ����void
  * ��    �أ�void
  * ��    ע��null
  *
  *
******************************************************************************/
void delay(uint32_t n)
{
    n = n * 2;
    while (n--)
        ;
}

/******************************************************************************
  * �������ƣ�IIC_Start
  * ����������I2c��ʼ�ź�
  * ��    �룺void
  * ��    ����void
  * ��    �أ�void
  * ��    ע��null
  *
  *
******************************************************************************/
void IIC_Start(void)
{
    P6DIR |= (1 << SDA);
    IIC |= (1 << SDA);
    //    delay(1);
    IIC |= (1 << SCL);
    delay(1);
    IIC &= ~(1 << SDA);
    delay(1);
    IIC &= ~(1 << SCL);
    delay(1);
}

/******************************************************************************
  * �������ƣ�IIC_Stop
  * ����������I2cֹͣ�ź�
  * ��    �룺void
  * ��    ����void
  * ��    �أ�void
  * ��    ע��null
  *
  *
******************************************************************************/
void IIC_Stop(void)
{
    P6DIR |= (1 << SDA);
    IIC &= ~(1 << SCL);
    IIC &= ~(1 << SDA);
    delay(1);
    IIC |= (1 << SCL);
    delay(1);
    IIC |= (1 << SDA);
}

/******************************************************************************
  * �������ƣ�IIC_SendACK
  * ��������������ACK
  * ��    �룺void
  * ��    ����void
  * ��    �أ�void
  * ��    ע��null
  *
  *
******************************************************************************/
void IIC_SendACK(uint32_t ack)
{
    P6DIR |= (1 << SDA);
    IIC &= ~(1 << SCL);
    delay(1);
    if (!ack)
    {
        IIC |= (1 << SDA);
    }
    else
    {
        IIC &= ~(1 << SDA);
    }
    delay(1);
    IIC |= (1 << SCL);
    delay(1);
    IIC &= ~(1 << SCL);
    delay(1);
    P6DIR &= ~(1 << SDA); //�ͷ�����
}

/******************************************************************************
  * �������ƣ�IIC_RecvACK
  * ��������������ACk
  * ��    �룺void
  * ��    ����void
  * ��    �أ�void
  * ��    ע��null
  *
  *
******************************************************************************/
void IIC_RecvACK(void)
{
    P6DIR &= ~(1 << SDA);

    IIC |= (1 << SCL);
    while ((P6IN & (1 << SDA)))
    {
        Ack_Count++;
        if (Ack_Count > 5)
        {
            IIC_Stop();
            Ack_Count = 0;
            break;
        }
    }

    IIC &= ~(1 << SCL);
    delay(1);
}

/******************************************************************************
  * �������ƣ�IIC_SendByte
  * ����������I2c����һ��byte
  * ��    �룺
  * uint32_t dat:Ҫ���͵�����
  * ��    ����void
  * ��    �أ�void
  * ��    ע��null
  *
  *
******************************************************************************/
void IIC_SendByte(uint32_t dat)
{
    uint8_t i;

    P6DIR |= (1 << SDA);
    i = 8;
    //  IIC &= ~(1 << SCL);
    //  delay(1);
    while (i--)
    {
        if ((dat & 0x80))
        {
            IIC |= (1 << SDA);
        }
        else
        {
            IIC &= ~(1 << SDA);
        }
        dat <<= 1;
        delay(1);
        IIC |= (1 << SCL);
        delay(1);
        IIC &= ~(1 << SCL);
        delay(1);
    }
    P6DIR &= ~(1 << SDA); //�ͷ�����
    //  IIC |= (1 << SDA);
    //  IIC_RecvACK();
}

/******************************************************************************
  * �������ƣ�IIC_RecvByte
  * ����������I2c����һ��byte
  * ��    �룺void
  * ��    ����void
  * ��    �أ����յ�������
  * ��    ע��null
  *
  *
******************************************************************************/
uint32_t IIC_RecvByte()
{
    uint8_t i;
    uint8_t dat = 0;

    P6DIR &= ~(1 << SDA);
    i = 8;
    while (i--)
    {
        //    IIC &= ~(1 << SCL);
        //    delay(1);
        IIC |= (1 << SCL);
        dat <<= 1;
        if (P6IN & (1 << SDA))
        {
            dat |= 1;
        }
        else
        {
            dat |= 0;
        }
        IIC &= ~(1 << SCL);
        delay(1);
    }
    return dat;
}

/******************************************************************************
  * �������ƣ�I2C_Write_Byte
  * ����������I2c���ӻ��Ĵ�����ַд����
  * ��    �룺
  * uint32_t Slaveaddr:�ӻ���ַ
  * uint32_t REG_Address:�Ĵ�����ַ
  * uint32_t REG_data���Ĵ�������
  * ��    ����void
  * ��    �أ�void
  * ��    ע��null
  *
  *
******************************************************************************/
void I2C_Write_Byte(uint8_t Slaveaddr, uint8_t REG_Address, uint8_t REG_data)
{
    IIC_Start();
    IIC_SendByte(Slaveaddr);
    IIC_RecvACK();
    IIC_SendByte(REG_Address);
    IIC_RecvACK();
    IIC_SendByte(REG_data);
    IIC_RecvACK();
    IIC_Stop();
}

/******************************************************************************
  * �������ƣ�I2C_Read_Byte
  * ����������I2c���ӻ��Ĵ���������
  * ��    �룺
  * uint32_t Slaveaddr���ӻ���ַ
  * uint32_t REG_Address:�Ĵ�����ַ
  * ��    ����void
  * ��    �أ���ȡ��������
  * ��    ע��null
  *
  *
******************************************************************************/
uint8_t I2C_Read_Byte(uint8_t Slaveaddr, uint8_t REG_Address)
{
    uint32_t REG_data;
    IIC_Start();
    IIC_SendByte(Slaveaddr);
    IIC_RecvACK();
    IIC_SendByte(REG_Address);
    IIC_RecvACK();
    IIC_Start();
    IIC_SendByte(Slaveaddr + 1);
    IIC_RecvACK();
    REG_data = IIC_RecvByte();
    IIC_SendACK(0);
    IIC_Stop();
    return REG_data;
}

uint8_t I2C_Read_Bytes(uint8_t Slaveaddr, uint8_t REG_Address, uint8_t *ptr, uint8_t len)
{
    IIC_Start();
    IIC_SendByte(Slaveaddr);
    IIC_RecvACK();
    IIC_SendByte(REG_Address);
    IIC_RecvACK();
    IIC_Start();
    IIC_SendByte(Slaveaddr + 1);
    IIC_RecvACK();
    while (len)
    {
        if (len == 1)
        {
            *ptr = IIC_RecvByte();
            IIC_SendACK(0);
        }
        else
        {
            *ptr = IIC_RecvByte();
            IIC_SendACK(1);
        }
        ptr++;
        len--;
    }
    IIC_Stop();
    return 0;
}

