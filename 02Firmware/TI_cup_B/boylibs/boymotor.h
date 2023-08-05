/*
 * boymotor.h
 *
 *  Created on: 2023��7��12��
 *      Author: BoyLuc׷����������
 */

#ifndef BOYLIBS_BOYMOTOR_H_
#define BOYLIBS_BOYMOTOR_H_
#include "exinlibs\headfile.h"
#define BOYSPEEDTODUTY 10
#define BOYDEADDUTY 40
#define BOYDISTANCETOPOSITION 1.805555
#define BOYLEFTGO()    gpio_set(GPIO_PORT_P8, GPIO_PIN7, 0),gpio_set(GPIO_PORT_P8, GPIO_PIN6, 1)//����ǰ��
#define BOYLEFTBACK()  gpio_set(GPIO_PORT_P8, GPIO_PIN7, 1),gpio_set(GPIO_PORT_P8, GPIO_PIN6, 0)//���ֺ���
#define BOYLEFTSTOP()  gpio_set(GPIO_PORT_P8, GPIO_PIN7, 0),gpio_set(GPIO_PORT_P8, GPIO_PIN6, 0)//����ͣת
#define BOYRIGHTGO()   gpio_set(GPIO_PORT_P3, GPIO_PIN7, 1),gpio_set(GPIO_PORT_P3, GPIO_PIN6, 0)//����ǰ��
#define BOYRIGHTBACK() gpio_set(GPIO_PORT_P3, GPIO_PIN7, 0),gpio_set(GPIO_PORT_P3, GPIO_PIN6, 1)//���ֺ���
#define BOYRIGHTSTOP() gpio_set(GPIO_PORT_P3, GPIO_PIN7, 0),gpio_set(GPIO_PORT_P3, GPIO_PIN6, 0)//����ͣת
extern void boy_motor_init();
extern void boy_direction_and_speed_control(int speedleft, int speedright);
extern int boy_position_to_distance(int position);
extern int boy_distance_to_position(int distance);

#endif /* BOYLIBS_BOYMOTOR_H_ */
