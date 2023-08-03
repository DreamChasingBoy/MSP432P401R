/*
 * boysteer.h
 *
 *  Created on: 2023年7月31日
 *      Author: BoyLuc追梦少年南南
 */

#ifndef BOYLIBS_BOYSTEER_H_
#define BOYLIBS_BOYSTEER_H_
#include "exinlibs\headfile.h"
extern uint8_t X_target_position,Y_target_position;
extern uint16_t X_real_duty,Y_real_duty,X_last_duty,Y_last_duty;
uint8_t X_real_position,Y_real_position,X_last_position,Y_last_position;
extern uint8_t X_flag_arrive,Y_flag_arrive;
extern void boy_steer_init(float angleA,float angleB);
extern void boy_steer_set(float angleA,float angleB);
extern void boy_steer_set_duty(uint16_t dutyA,uint16_t dutyB);
extern void boy_steer_init_duty(uint16_t dutyA,uint16_t dutyB);
extern uint8_t go_direct(uint16_t xpos,uint16_t ypos);
#endif /* BOYLIBS_BOYSTEER_H_ */
