/*
 * boymotor.h
 *
 *  Created on: 2023年7月12日
 *      Author: BoyLuc追梦少年南南
 */

#ifndef BOYLIBS_BOYMOTOR_H_
#define BOYLIBS_BOYMOTOR_H_
#include "exinlibs\headfile.h"
#define BOYSPEEDTODUTY 10
#define BOYDEADDUTY 40
#define BOYDISTANCETOPOSITION 1.805555
#define BOYLEFTGO()    gpio_set(GPIO_PORT_P8, GPIO_PIN7, 0),gpio_set(GPIO_PORT_P8, GPIO_PIN6, 1)//左轮前进
#define BOYLEFTBACK()  gpio_set(GPIO_PORT_P8, GPIO_PIN7, 1),gpio_set(GPIO_PORT_P8, GPIO_PIN6, 0)//左轮后退
#define BOYLEFTSTOP()  gpio_set(GPIO_PORT_P8, GPIO_PIN7, 0),gpio_set(GPIO_PORT_P8, GPIO_PIN6, 0)//左轮停转
#define BOYRIGHTGO()   gpio_set(GPIO_PORT_P3, GPIO_PIN7, 1),gpio_set(GPIO_PORT_P3, GPIO_PIN6, 0)//右轮前进
#define BOYRIGHTBACK() gpio_set(GPIO_PORT_P3, GPIO_PIN7, 0),gpio_set(GPIO_PORT_P3, GPIO_PIN6, 1)//右轮后退
#define BOYRIGHTSTOP() gpio_set(GPIO_PORT_P3, GPIO_PIN7, 0),gpio_set(GPIO_PORT_P3, GPIO_PIN6, 0)//右轮停转
extern void boy_motor_init();
extern void boy_direction_and_speed_control(int speedleft, int speedright);
extern int boy_position_to_distance(int position);
extern int boy_distance_to_position(int distance);

#endif /* BOYLIBS_BOYMOTOR_H_ */
