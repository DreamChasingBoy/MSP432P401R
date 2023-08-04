/*
 * boytask.c
 *
 *  Created on: 2023Äê8ÔÂ3ÈÕ
 *      Author: 26491
 */

#include "boytask.h"
#include "math.h"
uint8_t task_state=0;
uint8_t if_control_start=0;
uint8_t go_where(uint16_t xpos,uint16_t ypos,uint8_t now_state)
{
    X_target_position=xpos;
    Y_target_position=ypos;
//    boy_p_foot=sqrt(((float)(abs)(X_last_position-X_target_position))/((float)(abs)(Y_last_position-Y_target_position)));
//    boy_steerpid_init();
    if(Y_flag_arrive&&X_flag_arrive)
    {
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

}
