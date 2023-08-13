/*
 * boysteer.c
 *
 *  Created on: 2023年7月31日
 *      Author: BoyLuc追梦少年南南
 */
#include "boysteer.h"
/*************************************************
 * 函  数  名:boy_angle_to_duty & boy_duty_to_angle
 * 功       能:占空比量与角度之间的换算关系
 * 参       数:角度量 & 占空比量
 * 返   回   值:占空比量 & 角度量
 * 注 意 事 项:无
 *************************************************/
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
 * 函  数  名:boy_steer_init
 * 功       能:初始化舵机
 * 参       数:angleA:舵机A的角度
 *            angleB:舵机B的角度
 * 注 意 事 项:无
 *************************************************/
void boy_steer_init(int angleA,int angleB)
{
    int dutyA = boy_angle_to_duty(angleA);
    int dutyB = boy_angle_to_duty(angleB);
    steer_pwm_init(steer_CHA,50,dutyA);
    steer_pwm_init(steer_CHB,50,dutyB);
}
/*************************************************
 * 函  数  名:boy_steer_set
 * 功       能:设置舵机的角度
 * 参       数:angleA:舵机A的角度
 *            angleB:舵机B的角度
 * 注 意 事 项:无
 *************************************************/
void boy_steer_set(int angleA,int angleB)
{
    int dutyA = boy_angle_to_duty(angleA);
    int dutyB = boy_angle_to_duty(angleB);
    pwm_duty(pwm_CHE,dutyA);
    pwm_duty(pwm_CHF,dutyB);
}
