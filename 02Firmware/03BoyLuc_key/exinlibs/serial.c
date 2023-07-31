/*-----------------------------------------------------------------------------------------------------
銆愬钩    鍙般�慍CS
銆愰�� 鐢� 鍗� 鐗� 鏈恒�憁sp432P401R
銆愬簳 灞� 搴撱�慣IVA WARE /msp432p4xx
銆愬紑 鍙戙�慹鑺伐浣滃
/*@@ 搴撲粎渚涘弬鑰� 鍚庢灉鑷礋
 *
 * 鐗堟湰 v1.0
 * 鏃堕棿 2019骞�1鏈�23鏃�22:29:47
-------------------------------------------------------------------------------------------------------*/
#include "headfile.h"
#include "serial.h"

RX_STACK rx_stack;
TX_STACK tx_stack;
uint8 data_receive;

uint8 serial[12]={1,2,3,4};
extern int get_da_temp[5];
int test1=0;
void serial_transmit_process() //闁稿繐鐗呯紞锟�8闁告艾閰ｉ悵锟�8
{
	uint8 data_prcc = 0;
	//test1=ADS_RCV_GetString(7);
	tx_stack.data[data_prcc++] |= (unsigned int)LMT_DataHandle();
	tx_stack.data[data_prcc++] |= ADS_RCV_GetString(6);
	tx_stack.data[data_prcc++] |= ADS_RCV_GetString(7);
	tx_stack.data[data_prcc++] |=ADS_RCV_GetString(8);
	tx_stack.data[data_prcc++] |=ADS_RCV_GetString(9);

	serial_send();
	serial_transmit_init();
}
/*
void serial_receive_process(void)
{
	flag[serial_synchronization] = 0;
	uint8 sum = 0, i = 0;
	uint8 data_prc = 0;
	if (rx_stack.lock_flag == LOCKED)
	{
		for (i = 0; i < DATA_RECEIVE_NUM; i++)
		{
			sum += rx_stack.data[i];
		}

		if (rx_stack.verify == sum)
		{

			flag[get] = rx_stack.data[data_prc++];

			data_prc = 0;
		}
		rx_stack.lock_flag = UNLOCK;
	}
}*/

void serial_send()
{
    uint8 i = 0;
	tx_stack.verify = 0;
	  MAP_UART_transmitData(EUSCI_A3_BASE,  0xA5);
	for ( i = 0; i < DATA_TRANSMIT_NUM; i++)
	{
	    MAP_UART_transmitData(EUSCI_A3_BASE, tx_stack.data[i]);
		tx_stack.verify += tx_stack.data[i];
	}
	//闁告瑦鍨块敓鎴掔劍閻楀孩顨ョ仦鐣屾憻闁肩尨鎷�
	 MAP_UART_transmitData(EUSCI_A3_BASE, tx_stack.verify);
	//闁告瑦鍨块敓鎴掕兌缁劑寮堕悢椋庢憻闁肩尨鎷�
	 MAP_UART_transmitData(EUSCI_A3_BASE, 0X5A);
}
/*
void serial_receive(UART_Type *uratn)
{
	if (rx_stack.lock_flag == UNLOCK)
	{
		for (uint8 i = 0; i < DATA_RECEIVE_NUM + 3; i++)
		{
			timee[serial_start] = systime.get_time_ms();
			data_receive = UART_GetChar(uratn);
			if (flag[serial_skip] == 1)
			{
				serial_receive_init();
				flag[serial_skip] = 0;
				break;
			}
			else
			{
				switch (i)
				{
				case 0:
					flag[serial_select] = 0;
					break;
				case DATA_RECEIVE_NUM + 1:
					flag[serial_select] = 2;
					break;
				case DATA_RECEIVE_NUM + 2:
					flag[serial_select] = 3;
					break;
				default:
					flag[serial_select] = 1;
					break;
				}
				switch (flag[serial_select])
				{
				case 0:
					rx_stack.head = data_receive;
					break;
				case 1:
					rx_stack.data[rx_stack.pr++] = data_receive;
					break;
				case 2:
					rx_stack.verify = data_receive;
					break;
				case 3:
					rx_stack.tail = data_receive;
					rx_stack.lock_flag = LOCKED;
					break;
				default:
					break;
				}
				if (rx_stack.head != 0xA5)
					flag[serial_skip] = 1;
			}
			if (rx_stack.tail == 0x5A)
			{
				flag[serial_synchronization] = 1;
				break;
			}
		}
		if (flag[serial_synchronization] == 1)
			serial_receive_process();
		serial_receive_init();
	}
}

void serial_receive_init()
{
	rx_stack.pr = 0;
	for (uint8 i = 0; i < DATA_RECEIVE_NUM; i++)
		rx_stack.data[i] = 0;
	rx_stack.lock_flag = UNLOCK;
	rx_stack.head = 0;
	rx_stack.tail = 0;
	flag[serial_while] = 1;
}
*/
void serial_transmit_init()
{
    uint8 i = 0;
	for (i = 0; i < DATA_TRANSMIT_NUM; i++)
		tx_stack.data[i] = 0;
}

// //-------------------------------------------------------------------------*
// //闁告垼濮ら弳鐔煎触閿燂拷: UART_GetChar
// //闁告棑鎷�  闁肩鎷�: 闁告瑦鍨块敓鎴掔閻⊙呯箔閿旇儻顩�(闂侇剨鎷� NULL 闁稿绮嶉娑㈠矗閹达讣鎷烽敓锟�)
// //闁告瑱鎷�  闁轰緤鎷�: uratn:婵☆垪锟借櫕鍋ラ柛姘Т椤┭囨晬濮濆盯RT0
// //閺夆晪鎷�  闁搞儻鎷�: 濞戞挻褰冭ぐ娑㈠绩鐠哄搫鐓傞柣銊ュ閺嗙喖骞戦敓锟�
// //缂佺媴鎷�  濞撴熬鎷�: UART_GetChar (UART4); 闁兼儳鍢茶ぐ鍥ㄧ▔閹绘帒缍撻柡锟界捄鍝勭厒闁汇劌瀚弳鐔煎箲閿燂拷
// //-------------------------------------------------------------------------*
// char UART_GetChar(UART_Type * uratn)
// {
//      /* 缂佹稑顦欢鐔煎箳閵夛附鏆繝濞撅拷鑼晩 */
//     while (!(UART_S1_REG(uratn) & UART_S1_RDRF_MASK))
//     {
// //      if(enable[serial_while])  //闁藉啯绻勬晶顔炬嫬閸愵厾妲搁柛锝冨妺婵炲洭鎳楅敓锟�
// //          timee[serial_start]=systime.get_time_ms();
//       if(systime.get_time_ms() - timee[serial_start] > SERIAL_TIMEOUT )
//             {
//               flag[serial_skip]=1;
//               break;
//             }
//     }

//     /* 闁兼儳鍢茶ぐ鍥箳閵夛附鏆柛鎺撳濞堬拷8濞达絽绉甸弳鐔煎箲閿燂拷 */
//     return UART_D_REG(uratn);
// }
