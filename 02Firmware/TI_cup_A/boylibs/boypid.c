/*
 * boypid.c
 *
 *  Created on: 2023年7月12日
 *      Author: BoyLuc追梦少年南南
 */

#include "boypid.h"
PID_Datatype pidSpeed,pidPosition,pidangle,pidsteer;
uint8_t speed_pid_control=1;//速度环开关，1为开启，0为关闭
uint8_t position_pid_control=1;//位置环开关，1为开启，0为关闭
uint8_t angle_pid_control=0;//角度环开关，1为开启，0为关闭
uint8_t steer_pid_control=1;//舵机角度环
/*************************************************
 * 函  数  名:boy_speedpid_init
 * 功      能:初始化速度环pid结构体
 * 参      数:无
 * 注 意 事 项:一定注意pid最大最小输出！
 *           一定注意pid最大最小输出！
 *           一定注意pid最大最小输出！
 *           door_integral不知道干啥的直接填1！
 *           调试时按需求修改kp、ki、kd等下列参数，output_max用于限制最大的速度增量。
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
 * 函  数  名:boy_positionpid_init
 * 功      能:初始化位置环pid结构体
 * 参      数:无
 * 注 意 事 项:一定注意pid最大最小输出！
 *           一定注意pid最大最小输出！
 *           一定注意pid最大最小输出！
 *           door_integral不知道干啥的直接填1！
 *           调试时按需求修改kp、ki、kd等下列参数，output_max用于限制最大速度。
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
 * 函  数  名:boy_anglepid_init
 * 功      能:初始化角度环pid结构体
 * 参      数:无
 * 注 意 事 项:一定注意pid最大最小输出！
 *           一定注意pid最大最小输出！
 *           一定注意pid最大最小输出！
 *           door_integral不知道干啥的直接填1！
 *           调试时按需求修改kp、ki、kd等下列参数，output_max用于限制最大差速增量。
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
 * 函  数  名:boy_steerpid_init
 * 功      能:初始化舵机角度环pid结构体
 * 参      数:无
 * 注 意 事 项:一定注意pid最大最小输出！
 *           一定注意pid最大最小输出！
 *           一定注意pid最大最小输出！
 *           door_integral不知道干啥的直接填1！
 *           调试时按需求修改kp、ki、kd等下列参数，output_max用于限制最大的速度增量。
 *************************************************/
void boy_steerpid_init()
{
    pidsteer.kp=1.8;
    pidsteer.ki=0.1;
    pidsteer.kd=0;
    pidsteer.door_integral=0.15;
    pidsteer.max_integral=24;
    pidsteer.min_integral=-24;
    pidsteer.output_max=36;
    pidsteer.output_min=-36;
}
/*************************************************
 * 函  数  名:pid_get_PID
 * 功      能:PID算法实现
 * 参      数:pid:要传入的PID结构体指针
 *           target:目标值
 *           real:实际值
 * 返  回  值:PID结果输出
 * 注 意 事 项:不用过分追求看懂源码，会用即可！！！
 *           不用过分追求看懂源码，会用即可！！！
 *           不用过分追求看懂源码，会用即可！！！
 *           这个函数在exinisr.c中TA3_0_IRQHandler()里面调用。
 *************************************************/
float pid_get_PID(PID_Datatype* pid, float target, float real)
{
    float max_door_integral=target*(1 + pid->door_integral);//door_integral的值大概在0.05左右
    float min_door_integral=target*(1 - pid->door_integral);
    uint8_t Ki_flag;
    float error = target - real; // 误差
    pid->integral += error; // 积分误差
    if (real <= min_door_integral || real >= max_door_integral)//积分分离，在稳态附近打开积分器
    {
        Ki_flag=0;
    }
    else
    {
        Ki_flag=1;
    }
    if (pid->integral > pid->max_integral) // 设置积分误差的上下限，防止过大或过小
    {
        pid->integral = pid->max_integral;
    }
    else if (pid->integral < pid->min_integral)
    {
        pid->integral = pid->min_integral;
    }

    float differential = error - pid->last_error; // 差分误差
    float PID = pid->kp * error + pid->ki * Ki_flag * pid->integral + pid->kd * differential;
    if (PID > pid->output_max)  // 设置控制量PID的上下限，防止过大或过小
    {
        PID = pid->output_max;
    }
    else if (PID < pid->output_min)
    {
        PID = pid->output_min;
    }
    pid->last_error = error; // 记录这次误差供下次差分使用

    return PID;
}
