/*
 * boykey.h
 *
 *  Created on: 2023��7��12��
 *      Author: BoyLuc׷����������
 */

#ifndef BOYLIBS_BOYKEY_H_
#define BOYLIBS_BOYKEY_H_

#include "exinlibs\headfile.h"
#define BOYKEY0 0x01<<0
#define BOYKEY1 0x01<<1
#define BOYKEY2 0x01<<2
#define BOYKEY3 0x01<<3
#define BOYKEY4 0x01<<4
#define BOYKEYALL BOYKEY0|BOYKEY1|BOYKEY2|BOYKEY3|BOYKEY4
extern void boy_key_init(uint8 key);
extern uint8 boy_key_get(uint8 key);
extern void boy_key_test();
#endif /* BOYLIBS_BOYKEY_H_ */
