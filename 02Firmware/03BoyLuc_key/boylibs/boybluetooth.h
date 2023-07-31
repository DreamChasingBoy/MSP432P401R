/*
 * boybluetooth.h
 *
 *  Created on: 2023年7月31日
 *      Author: BoyLuc追梦少年南南
 */

#ifndef BOYLIBS_BOYBLUETOOTH_H_
#define BOYLIBS_BOYBLUETOOTH_H_

#include "exinlibs\headfile.h"
extern uint8_t RxBluetooth[4];
extern uint8_t TxBluetooth[6];
extern void boy_bluetooth_receive_data(uint8_t com_data);
extern void boy_bluetooth_send_data(uint8_t cmd1,uint8_t cmd2,uint8_t cmd3,uint8_t cmd4);

#endif /* BOYLIBS_BOYBLUETOOTH_H_ */
