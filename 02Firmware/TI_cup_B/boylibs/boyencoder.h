/*
 * boyencoder.h
 *
 *  Created on: 2023��7��13��
 *      Author: BoyLuc׷����������
 */

#ifndef BOYLIBS_BOYENCODER_H_
#define BOYLIBS_BOYENCODER_H_
#include "exinlibs\headfile.h"

extern float left_real_speed;
extern float right_real_speed;
extern float left_target_speed;
extern float right_target_speed;
extern float left_target_position;
extern float right_target_position;
extern float left_real_position;
extern float right_real_position;
extern float left_target_angle;
extern float right_target_angle;
extern void boy_encoder_init();
extern void boy_speed_and_position_get();
extern void boy_encoder_clear();
#endif /* BOYLIBS_BOYENCODER_H_ */
