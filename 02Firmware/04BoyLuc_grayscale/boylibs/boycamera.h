/*
 * boycamera.h
 *
 *  Created on: 2023��7��31��
 *      Author: BoyLuc׷����������
 */

#ifndef BOYLIBS_BOYCAMERA_H_
#define BOYLIBS_BOYCAMERA_H_
#include "exinlibs\headfile.h"

#define BOYCAMERADATASIZE 4
extern uint8_t RxCamera[BOYCAMERADATASIZE];
extern void boy_camera_receive_data(uint8_t com_data);


#endif /* BOYLIBS_BOYCAMERA_H_ */
