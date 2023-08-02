/*
 * boysteer.h
 *
 *  Created on: 2023年7月31日
 *      Author: BoyLuc追梦少年南南
 */

#ifndef BOYLIBS_BOYSTEER_H_
#define BOYLIBS_BOYSTEER_H_
#include "exinlibs\headfile.h"

extern void boy_steer_init(float angleA,float angleB);
extern void boy_steer_set(float angleA,float angleB);
extern void boy_steer_set_duty(uint16_t dutyA,uint16_t dutyB);
extern void boy_steer_init_duty(uint16_t dutyA,uint16_t dutyB);
#endif /* BOYLIBS_BOYSTEER_H_ */
