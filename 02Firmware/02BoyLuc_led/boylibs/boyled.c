/*
 * boyled.c
 *
 *  Created on: 2023年7月12日
 *      Author: BoyLuc追梦少年南南
 */
/*************************************************
 * 函  数  名:boy_led_or_beep_init
 * 功       能:初始化led或蜂鸣器
 * 参       数:led:要初始化的led或蜂鸣器
 * 注 意 事 项:boy_led_or_beep_init(BOYLEDALL|BOYBEEP)//三个LED和一个蜂鸣器全部初始化
 *************************************************/
#include "boyled.h"
void boy_led_or_beep_init(uint8 led)
{
    if(led & BOYLED0)
    {
        gpio_init(GPIO_PORT_P1,GPIO_PIN0,GPO,1);
    }
    if(led & BOYLED1)
    {
        gpio_init(GPIO_PORT_P2,GPIO_PIN0,GPO,1);
    }
    if(led & BOYLED2)
    {
        gpio_init(GPIO_PORT_P2,GPIO_PIN1,GPO,1);
    }
    if(led & BOYBEEP)
    {
        gpio_init(GPIO_PORT_P9,GPIO_PIN1,GPO,0);
    }
}



