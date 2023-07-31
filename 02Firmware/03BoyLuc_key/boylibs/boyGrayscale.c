/*
 * boyGrayscale.c
 *
 *  Created on: 2023年7月12日
 *      Author: BoyLuc追梦少年南南
 */

#include "boyGrayscale.h"
uint8_t trail[9]={0};
/*************************************************
 * 函  数  名:boy_grayscale_init
 * 功       能:初始化灰度传感器
 * 参       数: 无
 * 注 意 事 项:无
 *************************************************/
void boy_grayscale_init()
{
    gpio_init(GPIO_PORT_P8, GPIO_PIN1|GPIO_PIN0, GPI, 1);
    gpio_init(GPIO_PORT_P7, GPIO_PIN7|GPIO_PIN6|GPIO_PIN5|GPIO_PIN4, GPI, 1);
    gpio_init(GPIO_PORT_P10, GPIO_PIN5|GPIO_PIN4, GPI, 1);
}
/*************************************************
 * 函  数  名:boy_read_grayscale
 * 功       能:读取灰度传感器
 * 参       数:无
 * 注 意 事 项:trail[1]~trail[8]为D1~D8端口，读取到深色为低电平，其余时刻为高电平；
 *           trail[0]为trail[1]~trail[8]加和，用于判断十字路口等等。
 *************************************************/
void boy_read_grayscale()
{
    trail[1]=gpio_get(GPIO_PORT_P8,GPIO_PIN1);//D1
    trail[2]=gpio_get(GPIO_PORT_P8,GPIO_PIN0);//D2
    trail[3]=gpio_get(GPIO_PORT_P7,GPIO_PIN7);//D3
    trail[4]=gpio_get(GPIO_PORT_P7,GPIO_PIN6);//D4
    trail[5]=gpio_get(GPIO_PORT_P7,GPIO_PIN5);//D5
    trail[6]=gpio_get(GPIO_PORT_P7,GPIO_PIN4);//D6
    trail[7]=gpio_get(GPIO_PORT_P10,GPIO_PIN5);//D7
    trail[8]=gpio_get(GPIO_PORT_P10,GPIO_PIN4);//D8
    trail[0]=trail[1]+trail[2]+trail[3]+trail[4]+
             trail[5]+trail[6]+trail[7]+trail[8];
}

