/*
 * boymotor.c
 *
 *  Created on: 2023��7��12��
 *      Author: BoyLuc׷����������
 */
#include "boymotor.h"
/*************************************************
 * ��  ��  ��:boy_motor_init
 * ��       ��:��ʼ������������ź��ٶȿ�������
 * ��       ��: ��
 * ע �� �� ��:��������Ĭ��ȫΪ0���ٶ�����Ĭ��ռ�ձ�Ϊ0�������ת��
 *************************************************/
void boy_motor_init()
{
    gpio_init(GPIO_PORT_P8, GPIO_PIN7|GPIO_PIN6, GPO, 0);
    gpio_init(GPIO_PORT_P3, GPIO_PIN7|GPIO_PIN6, GPO, 0);
    pwm_init(pwm_CHA,10000,0);
    pwm_init(pwm_CHB,10000,0);
}
/*************************************************
 * ��  ��  ��:boy_duty_to_speed & boy_speed_to_duty
 * ��       ��:ռ�ձ������ٶ���֮��Ļ����ϵ
 * ��       ��:ռ�ձ��� & �ٶ���
 * ��   ��   ֵ:�ٶ��� & ռ�ձ���
 * ע �� �� ��:�˴�ϵ��BOYSPEEDTODUTY�Ǹ���ʵ�����������ģ�����Ҫ�ô��ڴ�ӡ����ÿ���ٶ�����Ӧ��ռ�ձ�����������������ϵķ�ʽ�õ�ϵ����
 *           �ڴ��Ҳ������������ݣ������������ԡ�ʹ���߿��Ը������ֱ���޸�ϵ��BOYSPEEDTODUTY
 *           �˴�ϵ��BOYDEADDUTYΪ���������ѹ��ռ�ձ�����������������������ѹ���������������һ����ѹ������ת��������������ٽ�ֵ��ѹ��С��֮Ϊ������ѹ��
 *           ��λ�û����������ѹΪduty=40����Ҳ�����Լ���һ�����Լ���������ѹ��
 *          |  duty  |  speed  |
 *          |  40    |   0     |
 *          |  240   |   24    |
 *          |  480   |   44    |
 *          |  720   |   68    |
 *          |  960   |   92    |
 *          |  1200  |   116   |
 *************************************************/
int boy_duty_to_speed(int duty)
{
    int speed;
    if(duty>0)
        speed=(duty-BOYDEADDUTY)/BOYSPEEDTODUTY;
    else if(duty<0)
        speed=(duty+BOYDEADDUTY)/BOYSPEEDTODUTY;
    else
        speed=0;
    return speed;
}
int boy_speed_to_duty(int speed)
{
    int duty;
    if(speed>0)
        duty=speed*BOYSPEEDTODUTY+BOYDEADDUTY;
    else if(speed<0)
        duty=speed*BOYSPEEDTODUTY-BOYDEADDUTY;
    else
        duty=0;
    return duty;
}
/*************************************************
 * ��  ��  ��:boy_position_to_distance & boy_distance_to_position
 * ��       ��:λ�����������֮��Ļ����ϵ
 * ��       ��:λ���� & ������
 * ��   ��   ֵ:������ & λ����
 * ע �� �� ��:�˴�ϵ��BOYDISTANCETOPOSITION�Ǹ���ʵ�����������ģ��ڱ����У������ܳ�d=216mm������תһȦ����ı���������n=390����
 *           ��ϵ��BOYDISTANCETOPOSITION=n/d=390/216=1.805555(��/mm),1.04�����ϵ��
 *************************************************/
int boy_position_to_distance(int position)
{
    float distance;
    distance=(float)position / BOYDISTANCETOPOSITION ;
    return (int)distance;
}
int boy_distance_to_position(int distance)
{
    float position;
    position=(float)distance * BOYDISTANCETOPOSITION ;
    return (int)position;
}
/*************************************************
 * ��  ��  ��:boy_direction_and_speed_control
 * ��       ��:������������ǰ��������ռ�ձ�
 * ��       ��:speedleft: ���ֵ��ٶ�������Χ-480~480������0��ת��С��0��ת������0ͣת.
 *            speedright:���ֵ��ٶ�������Χ-480~480������0��ת��С��0��ת������0ͣת.
 * ע �� �� ��:��boylibs�У����еı�������Ӧ��ѭ���¹���
 *
 *           ���֣�left_
 *           ���֣�right_
 *
 *           Ԥ��ֵ��_target_
 *           ʵ��ֵ��_real_
 *
 *           ռ�ձ�����_duty    ��Χ: -4800~4800(���������4800����������Ϥ��ռ�ձȰٷ����İ汾)
 *           �ٶ�����_speed     ��λ: ��������/100ms �磺left_real_speed = 20 ��ʾ����ʵ��ת��Ϊÿ100ms���20������
 *                                              ע���ٶ�����ռ�ձ������������ٶȵ���������֮����ڻ����ϵ
 *           λ������_position  ��λ: ��������       �磺left_real_position = 1500��ʾ���������ʼֵ���1500�������λ��
 *           ��������_distance  ��λ: mm           ע����������λ������������·�̵���������֮����ڻ����ϵ
 *           ����ǣ�_angle     ��λ: ��
 *
 *           ���磺����������50%��ռ�ձ���ת������������50%��ռ�ձȷ�ת:
 *           float left_real_duty = 0.5*4800;
 *           float right_real_duty = -0.5*4800;
 *           boy_direction_and_speed_control(left_real_duty,right_real_duty);
 *           ���������exinisr.c��TA3_0_IRQHandler()������á�
 *************************************************/
void boy_direction_and_speed_control(int speedleft, int speedright)
{
    int dutyleft=boy_speed_to_duty(speedleft);
    int dutyright=boy_speed_to_duty(speedright);
    dutyleft=dutyleft>4800?4800:dutyleft;   dutyleft=dutyleft<-4800?-4800:dutyleft;
    dutyright=dutyright>4800?4800:dutyright;dutyright=dutyright<-4800?-4800:dutyright;
    if(dutyleft>0) BOYLEFTGO();
    else if(dutyleft<0) BOYLEFTBACK();
    else BOYLEFTSTOP();
    if(dutyright>0) BOYRIGHTGO();
    else if(dutyright<0) BOYRIGHTBACK();
    else BOYRIGHTSTOP();
    pwm_duty(pwm_CHA,abs((int)dutyleft));
    pwm_duty(pwm_CHB,abs((int)dutyright));
}

