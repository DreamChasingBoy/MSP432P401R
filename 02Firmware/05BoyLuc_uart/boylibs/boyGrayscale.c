/*
 * boyGrayscale.c
 *
 *  Created on: 2023��7��12��
 *      Author: BoyLuc׷����������
 */

#include "boyGrayscale.h"
uint8_t trail[9]={0};
/*************************************************
 * ��  ��  ��:boy_grayscale_init
 * ��       ��:��ʼ���Ҷȴ�����
 * ��       ��: ��
 * ע �� �� ��:��
 *************************************************/
void boy_grayscale_init()
{
    gpio_init(GPIO_PORT_P8, GPIO_PIN1|GPIO_PIN0, GPI, 1);
    gpio_init(GPIO_PORT_P7, GPIO_PIN7|GPIO_PIN6|GPIO_PIN5|GPIO_PIN4, GPI, 1);
    gpio_init(GPIO_PORT_P10, GPIO_PIN5|GPIO_PIN4, GPI, 1);
}
/*************************************************
 * ��  ��  ��:boy_read_grayscale
 * ��       ��:��ȡ�Ҷȴ�����
 * ��       ��:��
 * ע �� �� ��:trail[1]~trail[8]ΪD1~D8�˿ڣ���ȡ����ɫΪ�͵�ƽ������ʱ��Ϊ�ߵ�ƽ��
 *           trail[0]Ϊtrail[1]~trail[8]�Ӻͣ������ж�ʮ��·�ڵȵȡ�
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

