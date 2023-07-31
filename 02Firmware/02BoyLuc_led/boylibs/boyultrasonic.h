/*
 * boyultrasonic.h
 *
 *  Created on: 2023Äê7ÔÂ14ÈÕ
 *      Author: 26491
 */

#ifndef BOYLIBS_BOYULTRASONIC_H_
#define BOYLIBS_BOYULTRASONIC_H_
#include "exinlibs\headfile.h"
#define MAX(a,b) (a>b?a:b)
#define MIN(a,b) (a<b?a:b)
#define BOYULTRASONICBUFFSIZE 9
extern void boy_ultrasonic_init();
extern float boy_ultrasonic_get_distance(int size);
#endif /* BOYLIBS_BOYULTRASONIC_H_ */
