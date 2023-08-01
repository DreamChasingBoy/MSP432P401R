/*
 * boyiic.h
 *
 *  Created on: 2023年8月1日
 *      Author: 26491
 */

#ifndef BOYLIBS_BOYIIC_H_
#define BOYLIBS_BOYIIC_H_

#include "exinlibs\headfile.h"
//宏定义区
#define IIC_SDA_Out P6DIR |= BIT5
#define IIC_SDA_In  P6DIR &= ~BIT5
#define IIC_SCL_Out P6DIR |= BIT4
#define SDA 5
#define SCL 4
#define IIC P6OUT

//函数声明
uint8_t I2C_Read_Bytes(uint8_t Slaveaddr, uint8_t REG_Address, uint8_t *ptr, uint8_t length);
uint8_t I2C_Read_Byte(uint8_t Slaveaddr, uint8_t REG_Address);
void I2C_Write_Byte(uint8_t Slaveaddr, uint8_t REG_Address, uint8_t REG_data);
void I2C_Init(void);



#endif /* BOYLIBS_BOYIIC_H_ */
