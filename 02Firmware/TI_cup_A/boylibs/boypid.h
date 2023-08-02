/*
 * boypid.h
 *
 *  Created on: 2023年7月12日
 *      Author: BoyLuc追梦少年南南
 */

#ifndef BOYLIBS_BOYPID_H_
#define BOYLIBS_BOYPID_H_
#include "exinlibs\headfile.h"
typedef struct {
    float kp;
    float ki;
    float kd;

    float integral;
    float last_error;

    float max_integral;
    float min_integral;
    float door_integral;//积分分离

    float output_max;
    float output_min;
} PID_Datatype;
PID_Datatype pidSpeed,pidPosition,pidangle,pidsteerX,pidsteerY;
extern uint8_t speed_pid_control;
extern uint8_t position_pid_control;
extern uint8_t angle_pid_control;
extern uint8_t steer_pid_control;//舵机角度环
extern float boy_p_foot;
extern float pid_get_PID(PID_Datatype* pid, float target, float real);
extern void boy_speedpid_init();
extern void boy_positionpid_init();
extern void boy_anglepid_init();
extern void boy_steerpid_init();

#endif /* BOYLIBS_BOYPID_H_ */
