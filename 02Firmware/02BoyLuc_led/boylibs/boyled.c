/*
 * boyled.c
 *
 *  Created on: 2023��7��12��
 *      Author: BoyLuc׷����������
 */
/*************************************************
 * ��  ��  ��:boy_led_or_beep_init
 * ��       ��:��ʼ��led�������
 * ��       ��:led:Ҫ��ʼ����led�������
 * ע �� �� ��:boy_led_or_beep_init(BOYLEDALL|BOYBEEP)//����LED��һ��������ȫ����ʼ��
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



