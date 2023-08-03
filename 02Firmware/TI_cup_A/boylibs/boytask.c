/*
 * boytask.c
 *
 *  Created on: 2023年8月3日
 *      Author: 26491
 */

#include "boytask.h"
uint8_t task_state=0;
uint8_t if_control_start=0;
uint8_t go_where(uint16_t xpos,uint16_t ypos,uint8_t now_state,uint8_t dir_lock)
{

    static uint8_t okay_init=0;
    X_target_position=xpos;
    Y_target_position=ypos;
//    if(okay_init==0)
//    {
//        Y_flag_arrive=X_flag_arrive=0;
    boy_p_foot=((float)(abs)(X_last_position-X_target_position))/((float)(abs)(Y_last_position-Y_target_position));
    boy_steerpid_init();
//        okay_init=1;
//    }

//    if(steer_pid_control!=0)
//    {
//    if(dir_lock==0)//锁Y
//        {steer_pid_control_x=1;steer_pid_control_y=0;Y_flag_arrive=1;}
//    else if(dir_lock==1)//锁X
//        {steer_pid_control_x=0;steer_pid_control_y=1;X_flag_arrive=1;}
//    else if(dir_lock==2)//都不锁
//        {steer_pid_control_x=1;steer_pid_control_y=1;}
    if(Y_flag_arrive&&X_flag_arrive)
    {
        okay_init=0;
        Y_flag_arrive=X_flag_arrive=0;
        boy_kill_integral_and_lasterror(&pidsteerY);
        boy_kill_integral_and_lasterror(&pidsteerX);
        X_last_position=X_target_position;
        Y_last_position=Y_target_position;
        return now_state+1;
    }
    else
    {
        return now_state;
    }
//    }

}
