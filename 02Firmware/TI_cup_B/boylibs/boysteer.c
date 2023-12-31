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
 * 函  数  名:boy_steer_init
 * 功       能:初始化舵机
 * 参       数:angleA:舵机A的角度
 *            angleB:舵机B的角度
 * 注 意 事 项:无
 *************************************************/
void boy_steer_init(float angleA,float angleB)
{
    int dutyA = boy_angle_to_duty(angleA);
    int dutyB = boy_angle_to_duty(angleB);
    steer_pwm_init(steer_CHA,50,dutyA);
    steer_pwm_init(steer_CHB,50,dutyB);
}
/*************************************************
 * 函  数  名:boy_steer_init
 * 功       能:初始化舵机
 * 参       数:angleA:舵机A的角度
 *            angleB:舵机B的角度
 * 注 意 事 项:无
 *************************************************/
void boy_steer_init_duty(uint16_t dutyA,uint16_t dutyB)
{
    dutyA=dutyA>7500?7500:dutyA; dutyA=dutyA<1500?1500:dutyA;
    dutyB=dutyB>7500?7500:dutyB; dutyB=dutyB<1500?1500:dutyB;
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
void boy_steer_set(float angleA,float angleB)
{
    int dutyA = boy_angle_to_duty(angleA);
    int dutyB = boy_angle_to_duty(angleB);
    pwm_duty(pwm_CHE,dutyA);
    pwm_duty(pwm_CHF,dutyB);
}
/*************************************************
 * 函  数  名:boy_steer_set_duty
 * 功       能:设置舵机的角度
 * 参       数:angleA:舵机A的角度
 *            angleB:舵机B的角度
 * 注 意 事 项:无
 *************************************************/
void boy_steer_set_duty(uint16_t dutyA,uint16_t dutyB)
{
    dutyA=dutyA>7500?7500:dutyA; dutyA=dutyA<1500?1500:dutyA;
    dutyB=dutyB>7500?7500:dutyB; dutyB=dutyB<1500?1500:dutyB;
    pwm_duty(pwm_CHE,dutyA);
    pwm_duty(pwm_CHF,dutyB);
}
/********************/
