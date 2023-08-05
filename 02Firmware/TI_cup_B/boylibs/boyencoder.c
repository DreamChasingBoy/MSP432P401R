/*
 * boyencoder.c
 *
 *  Created on: 2023��7��13��
 *      Author: BoyLuc׷����������
 */
#include "boyencoder.h"
float left_real_speed=0;//�⼸�������������boymotor.c�ļ�boy_direction_and_speed_control()����ע��
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
 * ��  ��  ��:boy_encoder_init
 * ��       ��:��ʼ��������
 * ��       ��: ��
 * ע �� �� ��:��
 *************************************************/
void boy_encoder_init()
{
    encoder_init(ENCODER_CHA,INT);
    encoder_init(ENCODER_CHB,INT);
}
/*************************************************
 * ��  ��  ��:boy_speed_and_position_get
 * ��       ��:��õ�ǰ���ٶ�����λ����������������С�
 * ��       ��: ��
 * ע �� �� ��:����100ms�Ķ�ʱ����ִ��
 *************************************************/
void boy_speed_and_position_get()
{
    left_real_speed=encoder_A.encoder;
    right_real_speed=encoder_B.encoder;
    left_real_position+=left_real_speed;
    right_real_position+=right_real_speed;
}
/*************************************************
 * ��  ��  ��:boy_encoder_clear
 * ��       ��:��ձ���������ֵ
 * ��       ��: ��
 * ע �� �� ��:����100ms�Ķ�ʱ����ִ��
 *************************************************/
void boy_encoder_clear()
{
    Encoder_clr(ENCODER_CHA);
    Encoder_clr(ENCODER_CHB);
}
