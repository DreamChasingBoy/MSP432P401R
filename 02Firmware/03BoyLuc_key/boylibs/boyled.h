/*
 * boyled.h
 *
 *  Created on: 2023年7月12日
 *      Author: BoyLuc追梦少年南南
 */

#ifndef BOYLIBS_BOYLED_H_
#define BOYLIBS_BOYLED_H_
#include "exinlibs\headfile.h"
#define BOYLED0 0x01<<0
#define BOYLED1 0x01<<1
#define BOYLED2 0x01<<2
#define BOYBEEP 0x01<<3
#define BOYLEDALL BOYLED0|BOYLED1|BOYLED2
#define BOYLED0_Toggle()  gpio_toggle(GPIO_PORT_P1, GPIO_PIN0)    //输出翻转
#define BOYLED0_ON()      gpio_set(GPIO_PORT_P1, GPIO_PIN0, 0)  //输出0，亮
#define BOYLED0_OFF()     gpio_set(GPIO_PORT_P1, GPIO_PIN0, 1)  //输出1，灭
#define BOYLED1_Toggle()  gpio_toggle(GPIO_PORT_P2, GPIO_PIN0)    //输出翻转
#define BOYLED1_ON()      gpio_set(GPIO_PORT_P2, GPIO_PIN0, 0)  //输出0，亮
#define BOYLED1_OFF()     gpio_set(GPIO_PORT_P2, GPIO_PIN0, 1)  //输出1，灭
#define BOYLED2_Toggle()  gpio_toggle(GPIO_PORT_P2, GPIO_PIN1)    //输出翻转
#define BOYLED2_ON()      gpio_set(GPIO_PORT_P2, GPIO_PIN1, 0)  //输出0，亮
#define BOYLED2_OFF()     gpio_set(GPIO_PORT_P2, GPIO_PIN1, 1)  //输出1，灭
#define BOYBEEP_Toggle()  gpio_toggle(GPIO_PORT_P9, GPIO_PIN1)    //输出翻转
#define BOYBEEP_ON()      gpio_set(GPIO_PORT_P9, GPIO_PIN1, 1)  //输出1，蜂鸣器响
#define BOYBEEP_OFF()     gpio_set(GPIO_PORT_P9, GPIO_PIN1, 0)  //输出0，蜂鸣器不响
extern void boy_led_or_beep_init(uint8 led);
#endif /* BOYLIBS_BOYLED_H_ */
