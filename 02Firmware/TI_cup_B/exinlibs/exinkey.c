/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2019年1月23日22:29:47
-------------------------------------------------------------------------------------------------------*/
#include "headfile.h"
#include "exinkey.h"
/***********************************/
/* key_init
 *
 * 按键初始化
 *
 *
 *key_init(uint8 key1|key2|key3|key4)//四个按键全部初始化
 *
 */
/**********************************/
void key_init(uint8 key)
{
    if(key&KEY1 )
    {
//        gpio_init(GPIO_PORT_P8,GPIO_PIN5,GPO,1);
        gpio_init(GPIO_PORT_P1,GPIO_PIN4,GPO,1);
    }
    else if(key&KEY2 )
    {
        gpio_init(GPIO_PORT_P9,GPIO_PIN0,GPO,1);
    }
    else if(key&KEY3 )
    {
        gpio_init(GPIO_PORT_P8,GPIO_PIN4,GPO,1);
    }
    else if(key&KEY4 )
    {
        gpio_init(GPIO_PORT_P8,GPIO_PIN3,GPO,1);
    }
}

/***********************************/
/*  key_get()
 *
 * 按键状态获取
 *
 *
 *key_init(uint8 key1)//四个按键全部初始化
 *
 */
/**********************************/
uint8 key_get(uint8 key)
{
        if(key&KEY1 )
        {
//            return gpio_get(GPIO_PORT_P8,GPIO_PIN5);
            return gpio_get(GPIO_PORT_P1,GPIO_PIN4);
        }
        else if(key&KEY2 )
        {
            return gpio_get(GPIO_PORT_P9,GPIO_PIN0);
        }
        else if(key&KEY3 )
        {
            return gpio_get(GPIO_PORT_P8,GPIO_PIN4);
        }
        else if(key&KEY4 )
        {
            return gpio_get(GPIO_PORT_P8,GPIO_PIN3);
        }
}

void key_test()
{
    while(1)
       {
           OLED_Show_String(0,1,"NO    KEY!",8);
           if(!key_get(KEY1))
           {
               delay_ms(10);
               if(!key_get(KEY1))
               {
                   OLED_clr();
                   OLED_Show_String(0,1,"KEY1 DOWN!",8);
               }
               while(!key_get(KEY1));
           }
           else if(!key_get(KEY2))
           {
               delay_ms(10);
               if(!key_get(KEY2))
               {
                   OLED_clr();
                   OLED_Show_String(0,1,"KEY2 DOWN!",8);
               }
               while(!key_get(KEY2));
           }
           else if(!key_get(KEY3))
             {
                 delay_ms(10);
                 if(!key_get(KEY3))
                 {
                     OLED_clr();
                     OLED_Show_String(0,1,"KEY3 DOWN!",8);
                 }
                 while(!key_get(KEY3));
             }
           else if(!key_get(KEY4))
             {
                 delay_ms(10);
                 if(!key_get(KEY4))
                 {
                     OLED_clr();
                     OLED_Show_String(0,1,"KEY4 DOWN!",8);
                 }
                 while(!key_get(KEY4));
             }
       }
}
