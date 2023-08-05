/*
 * boysteer.c
 *
 *  Created on: 2023��7��31��
 *      Author: BoyLuc׷����������
 */
#include "boysteer.h"
/*************************************************
 * ��  ��  ��:boy_angle_to_duty & boy_duty_to_angle
 * ��       ��:ռ�ձ�����Ƕ�֮��Ļ����ϵ
 * ��       ��:�Ƕ��� & ռ�ձ���
 * ��   ��   ֵ:ռ�ձ��� & �Ƕ���
 * ע �� �� ��:��
 *************************************************/
uint16_t X_target_position,Y_target_position;
uint16_t X_real_position,Y_real_position,X_last_position,Y_last_position;
int X_real_duty,Y_real_duty,X_last_duty,Y_last_duty;
uint8_t X_flag_arrive,Y_flag_arrive;
int boy_angle_to_duty(float angle)
{
    angle=angle>180?180:angle;
    angle=angle<0?0:angle;
    int duty = (300/9)*angle+1500;
    return duty;
}
float boy_duty_to_angle(int duty)
{
    duty=duty>7500?7500:duty;
    duty=duty<1500?1500:duty;
    float angle = 9*((float)duty-1500)/300;
    return angle;
}
/*************************************************
 * ��  ��  ��:boy_steer_init
 * ��       ��:��ʼ�����
 * ��       ��:angleA:���A�ĽǶ�
 *            angleB:���B�ĽǶ�
 * ע �� �� ��:��
 *************************************************/
void boy_steer_init(float angleA,float angleB)
{
    int dutyA = boy_angle_to_duty(angleA);
    int dutyB = boy_angle_to_duty(angleB);
    steer_pwm_init(steer_CHA,50,dutyA);
    steer_pwm_init(steer_CHB,50,dutyB);
}
/*************************************************
 * ��  ��  ��:boy_steer_init
 * ��       ��:��ʼ�����
 * ��       ��:angleA:���A�ĽǶ�
 *            angleB:���B�ĽǶ�
 * ע �� �� ��:��
 *************************************************/
void boy_steer_init_duty(uint16_t dutyA,uint16_t dutyB)
{
    dutyA=dutyA>7500?7500:dutyA; dutyA=dutyA<1500?1500:dutyA;
    dutyB=dutyB>7500?7500:dutyB; dutyB=dutyB<1500?1500:dutyB;
    steer_pwm_init(steer_CHA,50,dutyA);
    steer_pwm_init(steer_CHB,50,dutyB);
}
/*************************************************
 * ��  ��  ��:boy_steer_set
 * ��       ��:���ö���ĽǶ�
 * ��       ��:angleA:���A�ĽǶ�
 *            angleB:���B�ĽǶ�
 * ע �� �� ��:��
 *************************************************/
void boy_steer_set(float angleA,float angleB)
{
    int dutyA = boy_angle_to_duty(angleA);
    int dutyB = boy_angle_to_duty(angleB);
    pwm_duty(pwm_CHE,dutyA);
    pwm_duty(pwm_CHF,dutyB);
}
/*************************************************
 * ��  ��  ��:boy_steer_set_duty
 * ��       ��:���ö���ĽǶ�
 * ��       ��:angleA:���A�ĽǶ�
 *            angleB:���B�ĽǶ�
 * ע �� �� ��:��
 *************************************************/
void boy_steer_set_duty(uint16_t dutyA,uint16_t dutyB)
{
    dutyA=dutyA>7500?7500:dutyA; dutyA=dutyA<1500?1500:dutyA;
    dutyB=dutyB>7500?7500:dutyB; dutyB=dutyB<1500?1500:dutyB;
    pwm_duty(pwm_CHE,dutyA);
    pwm_duty(pwm_CHF,dutyB);
}
/********************/