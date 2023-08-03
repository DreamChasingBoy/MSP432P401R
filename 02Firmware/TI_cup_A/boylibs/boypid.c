/*
 * boypid.c
 *
 *  Created on: 2023��7��12��
 *      Author: BoyLuc׷����������
 */

#include "boypid.h"
float boy_p_foot=1;
PID_Datatype pidSpeed,pidPosition,pidangle,pidsteerX,pidsteerY;
uint8_t speed_pid_control=1;//�ٶȻ����أ�1Ϊ������0Ϊ�ر�
uint8_t position_pid_control=1;//λ�û����أ�1Ϊ������0Ϊ�ر�
uint8_t angle_pid_control=0;//�ǶȻ����أ�1Ϊ������0Ϊ�ر�
uint8_t steer_pid_control=1;//����ǶȻ�
/*************************************************
 * ��  ��  ��:boy_speedpid_init
 * ��      ��:��ʼ���ٶȻ�pid�ṹ��
 * ��      ��:��
 * ע �� �� ��:һ��ע��pid�����С�����
 *           һ��ע��pid�����С�����
 *           һ��ע��pid�����С�����
 *           door_integral��֪����ɶ��ֱ����1��
 *           ����ʱ�������޸�kp��ki��kd�����в�����output_max�������������ٶ�������
 *************************************************/
void boy_speedpid_init()
{
    pidSpeed.kp=1.8;
    pidSpeed.ki=0.1;
    pidSpeed.kd=0;
    pidSpeed.door_integral=0.15;
    pidSpeed.max_integral=24;
    pidSpeed.min_integral=-24;
    pidSpeed.output_max=36;
    pidSpeed.output_min=-36;
}
/*************************************************
 * ��  ��  ��:boy_positionpid_init
 * ��      ��:��ʼ��λ�û�pid�ṹ��
 * ��      ��:��
 * ע �� �� ��:һ��ע��pid�����С�����
 *           һ��ע��pid�����С�����
 *           һ��ע��pid�����С�����
 *           door_integral��֪����ɶ��ֱ����1��
 *           ����ʱ�������޸�kp��ki��kd�����в�����output_max������������ٶȡ�
 *************************************************/
void boy_positionpid_init()
{
    pidPosition.kp=0.3;
    pidPosition.ki=0.1;
    pidPosition.kd=0;
    pidPosition.door_integral=1;
    pidPosition.max_integral=60;
    pidPosition.min_integral=-60;
    pidPosition.output_max=60;
    pidPosition.output_min=-60;
}
/*************************************************
 * ��  ��  ��:boy_anglepid_init
 * ��      ��:��ʼ���ǶȻ�pid�ṹ��
 * ��      ��:��
 * ע �� �� ��:һ��ע��pid�����С�����
 *           һ��ע��pid�����С�����
 *           һ��ע��pid�����С�����
 *           door_integral��֪����ɶ��ֱ����1��
 *           ����ʱ�������޸�kp��ki��kd�����в�����output_max��������������������
 *************************************************/
void boy_anglepid_init()
{
    pidangle.kp=0.9;
    pidangle.ki=0.1;
    pidangle.kd=0;
    pidangle.door_integral=1;
    pidangle.max_integral=15;
    pidangle.min_integral=-15;
    pidangle.output_max=30;
    pidangle.output_min=-30;
}
/*************************************************
 * ��  ��  ��:boy_steerpid_init
 * ��      ��:��ʼ������ǶȻ�pid�ṹ��
 * ��      ��:��
 * ע �� �� ��:һ��ע��pid�����С�����
 *           һ��ע��pid�����С�����
 *           һ��ע��pid�����С�����
 *           door_integral��֪����ɶ��ֱ����1��
 *           ����ʱ�������޸�kp��ki��kd�����в�����output_max�������������ٶ�������
 *************************************************/
void boy_steerpid_init()
{
    pidsteerX.kp=
    pidsteerY.kp=0.15;
    pidsteerX.ki=
    pidsteerY.ki=0.25;
    pidsteerX.kd=
    pidsteerY.kd=0.2;
    pidsteerY.door_integral=1;
    pidsteerY.max_integral=3;
    pidsteerY.min_integral=-3;
    pidsteerY.output_max=4*boy_p_foot;
    pidsteerY.output_min=-4*boy_p_foot;

    pidsteerX.door_integral=1;
    pidsteerX.max_integral=3;
    pidsteerX.min_integral=-3;
    pidsteerX.output_max=4/boy_p_foot;
    pidsteerX.output_min=-4/boy_p_foot;
}
/*************************************************
 * ��  ��  ��:pid_get_PID
 * ��      ��:PID�㷨ʵ��
 * ��      ��:pid:Ҫ�����PID�ṹ��ָ��
 *           target:Ŀ��ֵ
 *           real:ʵ��ֵ
 * ��  ��  ֵ:PID������
 * ע �� �� ��:���ù���׷�󿴶�Դ�룬���ü��ɣ�����
 *           ���ù���׷�󿴶�Դ�룬���ü��ɣ�����
 *           ���ù���׷�󿴶�Դ�룬���ü��ɣ�����
 *           ���������exinisr.c��TA3_0_IRQHandler()������á�
 *************************************************/
float pid_get_PID(PID_Datatype* pid, float target, float real)
{
    float max_door_integral=target*(1 + pid->door_integral);//door_integral��ֵ�����0.05����
    float min_door_integral=target*(1 - pid->door_integral);
    uint8_t Ki_flag;
    float error = target - real; // ���
    pid->integral += error; // �������
    if (real <= min_door_integral || real >= max_door_integral)//���ַ��룬����̬�����򿪻�����
    {
        Ki_flag=0;
    }
    else
    {
        Ki_flag=1;
    }
    if (pid->integral > pid->max_integral) // ���û������������ޣ���ֹ������С
    {
        pid->integral = pid->max_integral;
    }
    else if (pid->integral < pid->min_integral)
    {
        pid->integral = pid->min_integral;
    }

    float differential = error - pid->last_error; // ������
    float PID = pid->kp * error + pid->ki * Ki_flag * pid->integral + pid->kd * differential;
    if (PID > pid->output_max)  // ���ÿ�����PID�������ޣ���ֹ������С
    {
        PID = pid->output_max;
    }
    else if (PID < pid->output_min)
    {
        PID = pid->output_min;
    }
    pid->last_error = error; // ��¼������´β��ʹ��

    return PID;
}
