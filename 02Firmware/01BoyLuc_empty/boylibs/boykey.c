/*
 * boykey.c
 *
 *  Created on: 2023��7��12��
 *      Author: BoyLuc׷����������
 */
#include "boykey.h"
/*************************************************
 * ��  ��  ��:boy_key_init
 * ��       ��:��ʼ������
 * ��       ��:key:Ҫ��ʼ���İ���
 * ע �� �� ��:boy_key_init(BOYLEDALL|BOYBEEP)//���а�����LEDȫ����ʼ��
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
 * ��  ��  ��:boy_key_get
 * ��       ��:����״̬��ȡ
 * ��       ��:key:Ҫ��ȡ״̬�İ���
 * ע �� �� ��:ʹ�÷���������boy_key_test
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
       if(!boy_key_get(BOYKEY0))//���а�������
       {
           delay_ms(10);//��ʱ����
           if(!boy_key_get(BOYKEY0))
           {
               OLED_clr();//ִ���������
               OLED_Show_String(0,1,"KEY0 DOWN!",8);
           }
           while(!boy_key_get(BOYKEY0));//�ȴ�����
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
