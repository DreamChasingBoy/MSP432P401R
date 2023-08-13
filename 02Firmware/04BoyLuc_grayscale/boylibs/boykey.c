/*
 * boykey.c
 *
 *  Created on: 2023年7月12日
 *      Author: BoyLuc追梦少年南南
 */
#include "boykey.h"
/*************************************************
 * 函  数  名:boy_key_init
 * 功       能:初始化按键
 * 参       数:key:要初始化的按键
 * 注 意 事 项:boy_key_init(BOYLEDALL|BOYBEEP)//所有按键和LED全部初始化
 *************************************************/
void boy_key_init(uint8 key)
{
    if(key & BOYKEY0)
    {
        gpio_init(GPIO_PORT_P1,GPIO_PIN1,GPI,1);
    }
    if(key & BOYKEY1)
    {
        gpio_init(GPIO_PORT_P1,GPIO_PIN4,GPI,1);
    }
    if(key & BOYKEY2)
    {
        gpio_init(GPIO_PORT_P10,GPIO_PIN3,GPI,1);
    }
    if(key & BOYKEY3)
    {
        gpio_init(GPIO_PORT_P10,GPIO_PIN2,GPI,1);
    }
    if(key & BOYKEY4)
    {
        gpio_init(GPIO_PORT_P10,GPIO_PIN1,GPI,1);
    }
}
/*************************************************
 * 函  数  名:boy_key_get
 * 功       能:按键状态获取
 * 参       数:key:要获取状态的按键
 * 注 意 事 项:使用方法见函数boy_key_test
 *************************************************/
uint8 boy_key_get(uint8 key)
{
    if(key & BOYKEY0)
    {
        return gpio_get(GPIO_PORT_P1,GPIO_PIN1);
    }
    else if(key & BOYKEY1)
    {
        return gpio_get(GPIO_PORT_P1,GPIO_PIN4);
    }
    else if(key & BOYKEY2)
    {
        return gpio_get(GPIO_PORT_P10,GPIO_PIN3);
    }
    else if(key & BOYKEY3)
    {
        return gpio_get(GPIO_PORT_P10,GPIO_PIN2);
    }
    else if(key & BOYKEY4)
    {
        return gpio_get(GPIO_PORT_P10,GPIO_PIN1);
    }
}

void boy_key_test()
{
   while(1)
   {
       OLED_Show_String(0,1,"NO    KEY!",8);
       if(!boy_key_get(BOYKEY0))//当有按键按下
       {
           delay_ms(10);//延时消抖
           if(!boy_key_get(BOYKEY0))
           {
               OLED_clr();//执行相关命令
               OLED_Show_String(0,1,"KEY0 DOWN!",8);
           }
           while(!boy_key_get(BOYKEY0));//等待松手
       }
       else if(!boy_key_get(BOYKEY1))
       {
           delay_ms(10);
           if(!boy_key_get(BOYKEY1))
           {
               OLED_clr();
               OLED_Show_String(0,1,"KEY1 DOWN!",8);
           }
           while(!boy_key_get(BOYKEY1));
       }
   }
}
