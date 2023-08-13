/*
 * boyencoder.c
 *
 *  Created on: 2023年7月13日
 *      Author: BoyLuc追梦少年南南
 */
#include "boyencoder.h"
float left_real_speed=0;//这几个变量命名详见boymotor.c文件boy_direction_and_speed_control()函数注释
float right_real_speed=0;
float left_target_speed=0;
float right_target_speed=0;
float left_target_position=0;
float right_target_position=0;
float left_real_position=0;
float right_real_position=0;
float left_target_angle=0;
float right_target_angle=0;
/*************************************************
 * 函  数  名:boy_encoder_init
 * 功       能:初始化编码器
 * 参       数: 无
 * 注 意 事 项:无
 *************************************************/
void boy_encoder_init()
{
    encoder_init(ENCODER_CHA,INT);
    encoder_init(ENCODER_CHB,INT);
}
/*************************************************
 * 函  数  名:boy_speed_and_position_get
 * 功       能:获得当前的速度量与位置量，并存入变量中。
 * 参       数: 无
 * 注 意 事 项:放在100ms的定时器中执行
 *************************************************/
void boy_speed_and_position_get()
{
    left_real_speed=encoder_A.encoder;
    right_real_speed=encoder_B.encoder;
    left_real_position+=left_real_speed;
    right_real_position+=right_real_speed;
}
/*************************************************
 * 函  数  名:boy_encoder_clear
 * 功       能:清空编码器计数值
 * 参       数: 无
 * 注 意 事 项:放在100ms的定时器中执行
 *************************************************/
void boy_encoder_clear()
{
    Encoder_clr(ENCODER_CHA);
    Encoder_clr(ENCODER_CHB);
}
