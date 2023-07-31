/*
 * boyled.h
 *
 *  Created on: 2023��7��12��
 *      Author: BoyLuc׷����������
 */

#ifndef BOYLIBS_BOYLED_H_
#define BOYLIBS_BOYLED_H_
#include "exinlibs\headfile.h"
#define BOYLED0 0x01<<0
#define BOYLED1 0x01<<1
#define BOYLED2 0x01<<2
#define BOYBEEP 0x01<<3
#define BOYLEDALL BOYLED0|BOYLED1|BOYLED2
#define BOYLED0_Toggle()  gpio_toggle(GPIO_PORT_P1, GPIO_PIN0)    //�����ת
#define BOYLED0_ON()      gpio_set(GPIO_PORT_P1, GPIO_PIN0, 0)  //���0����
#define BOYLED0_OFF()     gpio_set(GPIO_PORT_P1, GPIO_PIN0, 1)  //���1����
#define BOYLED1_Toggle()  gpio_toggle(GPIO_PORT_P2, GPIO_PIN0)    //�����ת
#define BOYLED1_ON()      gpio_set(GPIO_PORT_P2, GPIO_PIN0, 0)  //���0����
#define BOYLED1_OFF()     gpio_set(GPIO_PORT_P2, GPIO_PIN0, 1)  //���1����
#define BOYLED2_Toggle()  gpio_toggle(GPIO_PORT_P2, GPIO_PIN1)    //�����ת
#define BOYLED2_ON()      gpio_set(GPIO_PORT_P2, GPIO_PIN1, 0)  //���0����
#define BOYLED2_OFF()     gpio_set(GPIO_PORT_P2, GPIO_PIN1, 1)  //���1����
#define BOYBEEP_Toggle()  gpio_toggle(GPIO_PORT_P9, GPIO_PIN1)    //�����ת
#define BOYBEEP_ON()      gpio_set(GPIO_PORT_P9, GPIO_PIN1, 1)  //���1����������
#define BOYBEEP_OFF()     gpio_set(GPIO_PORT_P9, GPIO_PIN1, 0)  //���0������������
extern void boy_led_or_beep_init(uint8 led);
#endif /* BOYLIBS_BOYLED_H_ */
