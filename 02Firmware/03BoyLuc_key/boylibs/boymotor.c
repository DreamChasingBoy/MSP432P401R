/*
 * boymotor.c
 *
 *  Created on: 2023年7月12日
 *      Author: BoyLuc追梦少年南南
 */
#include "boymotor.h"
/*************************************************
 * 函  数  名:boy_motor_init
 * 功       能:初始化方向控制引脚和速度控制引脚
 * 参       数: 无
 * 注 意 事 项:方向引脚默认全为0，速度引脚默认占空比为0，电机不转动
 *************************************************/
void boy_motor_init()
{
    gpio_init(GPIO_PORT_P8, GPIO_PIN7|GPIO_PIN6, GPO, 0);
    gpio_init(GPIO_PORT_P3, GPIO_PIN7|GPIO_PIN6, GPO, 0);
    pwm_init(pwm_CHA,10000,0);
    pwm_init(pwm_CHB,10000,0);
}
/*************************************************
 * 函  数  名:boy_duty_to_speed & boy_speed_to_duty
 * 功       能:占空比量与速度量之间的换算关系
 * 参       数:占空比量 & 速度量
 * 返   回   值:速度量 & 占空比量
 * 注 意 事 项:此处系数BOYSPEEDTODUTY是根据实际情况来计算的，你需要用串口打印出它每个速度量对应的占空比量，最后采用线性拟合的方式得到系数。
 *           在此我测试了五组数据，基本符合线性。使用者可以根据情况直接修改系数BOYSPEEDTODUTY
 *           此处系数BOYDEADDUTY为电机死区电压的占空比量。多数电机会存在死区电压，即电机两段虽有一定电压差但电机不转动，这种情况的临界值电压大小称之为死区电压。
 *           用位置环测的死区电压为duty=40，你也可以自己测一下你自己的死区电压。
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
 * 函  数  名:boy_position_to_distance & boy_distance_to_position
 * 功       能:位置量与距离量之间的换算关系
 * 参       数:位置量 & 距离量
 * 返   回   值:距离量 & 位置量
 * 注 意 事 项:此处系数BOYDISTANCETOPOSITION是根据实际情况来计算的，在本车中，车轮周长d=216mm，车轮转一圈输出的编码器脉冲n=390个，
 *           则系数BOYDISTANCETOPOSITION=n/d=390/216=1.805555(个/mm),1.04是误差系数
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
 * 函  数  名:boy_direction_and_speed_control
 * 功       能:控制左右轮子前进方向与占空比
 * 参       数:speedleft: 左轮的速度量，范围-480~480，大于0正转，小于0反转，等于0停转.
 *            speedright:右轮的速度量，范围-480~480，大于0正转，小于0反转，等于0停转.
 * 注 意 事 项:在boylibs中，所有的变量命名应遵循以下规则：
 *
 *           左轮：left_
 *           右轮：right_
 *
 *           预期值：_target_
 *           实际值：_real_
 *
 *           占空比量：_duty    范围: -4800~4800(这个数除以4800才是我们熟悉的占空比百分数的版本)
 *           速度量：_speed     单位: 编码量个/100ms 如：left_real_speed = 20 表示左轮实际转速为每100ms输出20个脉冲
 *                                              注：速度量和占空比量都是描述速度的量，二者之间存在换算关系
 *           位置量：_position  单位: 编码量个       如：left_real_position = 1500表示左轮在与初始值相距1500个脉冲的位置
 *           距离量：_distance  单位: mm           注：距离量和位置量都是描述路程的量，二者之间存在换算关系
 *           航向角：_angle     单位: °
 *
 *           例如：控制左轮以50%的占空比正转，控制右轮以50%的占空比反转:
 *           float left_real_duty = 0.5*4800;
 *           float right_real_duty = -0.5*4800;
 *           boy_direction_and_speed_control(left_real_duty,right_real_duty);
 *           这个函数在exinisr.c中TA3_0_IRQHandler()里面调用。
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

