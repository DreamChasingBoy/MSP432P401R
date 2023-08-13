/*
 * boybluetooth.c
 *
 *  Created on: 2023��7��31��
 *      Author: BoyLuc׷����������
 */
#include "boybluetooth.h"
uint8_t RxBluetooth[4]={0};
uint8_t TxBluetooth[6]={0x28,0,0,0,0,0x29};
/*************************************************
 * ��  ��  ��:boy_bluetooth_taskn
 * ��       ��:����ָ��Ļص�����
 * ��       ��:rx_cmd:���뺯���Ĳ���
 * ע �� �� ��:�����ĸ�������˳��ִ�У�ֻ��Ҫ�ں�����д����Ӧ�Ķ��������붯���Ĳ�������
 *************************************************/
void boy_bluetooth_task1(uint8_t rx_cmd)
{
    /***************��ӵ�һ��Ҫִ�е�����****************/

    /***************������һ��Ҫִ�е�����****************/
}
void boy_bluetooth_task2(uint8_t rx_cmd)
{
    /***************��ӵڶ���Ҫִ�е�����****************/

    /***************�����ڶ���Ҫִ�е�����****************/
}
void boy_bluetooth_task3(uint8_t rx_cmd)
{
    /***************��ӵ�����Ҫִ�е�����****************/

    /***************����������Ҫִ�е�����****************/
}
void boy_bluetooth_task4(uint8_t rx_cmd)
{
    /***************��ӵ��ĸ�Ҫִ�е�����****************/

    /***************�������ĸ�Ҫִ�е�����****************/
}
/*************************************************
 * ��  ��  ��:boy_bluetooth_send_data
 * ��       ��:��Ϊ���ͷ�����շ�����ָ��
 * ��       ��:cmd1:��������1�Ĳ���
 *            cmd2:��������2�Ĳ���
 *            cmd3:��������3�Ĳ���
 *            cmd4:��������4�Ĳ���
 * ע �� �� ��:�˴�����Ϊͨ������3�������ݣ�����ʱ�ɽ�����3�ĳɴ���0��
 *           ��boy_bluetooth_receive_data���ʹ�á�
 *************************************************/
void boy_bluetooth_send_data(uint8_t cmd1,uint8_t cmd2,uint8_t cmd3,uint8_t cmd4)
{
    TxBluetooth[1]=cmd1;
    TxBluetooth[2]=cmd2;
    TxBluetooth[3]=cmd3;
    TxBluetooth[4]=cmd4;
    UART_send_string(UART3,TxBluetooth);
    TxBluetooth[1]=TxBluetooth[2]=TxBluetooth[3]=TxBluetooth[4]=0;
}
/*************************************************
 * ��  ��  ��:boy_bluetooth_receive_data
 * ��       ��:��Ϊ���շ����շ��ͷ���ָ��
 * ��       ��:com_data:�յ�������
 * ע �� �� ��:����Ҫ������������������������Ҫ������������������������Ҫ��������������������
 *           ��ֻ��Ҫ��������Ļص��������ɣ�������ֻ��Ҫ��������Ļص��������ɣ�������ֻ��Ҫ��������Ļص��������ɣ�����
 *           һ֡���ݵĸ�ʽ�����ϸ�Ĺ涨���������¸�ʽ������Ӧ�����ݡ�ÿ��ֻ�ܴ����ĸ�ָ�����
 *           ���磬�����ͷ�����һָ֡������ʱ�����������봫1��2��3��4��������RxCamera��õ�����������ʾ��
 *    ��ʽ   :  |  ֡ͷ | cmd1 | cmd2 | cmd3 | cmd4 |  ֡β |
 * TxBluetooth:| 0x28 | 0x01 | 0x02 | 0x03 | 0x04 | 0x29 |
 * RxBuffer2:  | 0x28 | 0x01 | 0x02 | 0x03 | 0x04 | 0x29 |
 * RxBluetooth:       { 0x01 , 0x02 , 0x03 , 0x04 }
 *           RxBuffer2������ʱ���շ��ͷ����������ݣ�ʵ���ϲ���ȥ����������飬�����Ѿ�����ʵ�֡�
 *           ���������exinuart.c��EUSCIA2_IRQHandler()������á�
 *************************************************/
void boy_bluetooth_receive_data(uint8_t com_data)
{
    uint8_t i,k;
    static uint8_t RxCounter2=0;//����
    static uint8_t RxBuffer2[6]={0};

    static uint8_t RxState2 = 0;//״̬��
    static uint8_t RxFlag2 = 0;//����

    if(RxState2==0&&com_data==0x28)  //0x28֡ͷ
    {
        RxState2=1;
        RxBuffer2[RxCounter2++]=com_data;
    }

    else if(RxState2==1)
    {
        RxBuffer2[RxCounter2++]=com_data;
        if(RxCounter2>=6||com_data == 0x29)       //RxBuffer2��������,�������ݽ���
        {
            RxState2=0;
            RxFlag2=1;
            RxCounter2=0;
            for(k=0;k<4;k++)
            {
                RxBluetooth[k]=RxBuffer2[k+1];
                RxBuffer2[k+1]=0;
            }
            boy_bluetooth_task1(RxBluetooth[0]);
            boy_bluetooth_task2(RxBluetooth[1]);
            boy_bluetooth_task3(RxBluetooth[2]);
            boy_bluetooth_task4(RxBluetooth[3]);
        }
    }

    else   //�����쳣
    {
        RxState2 = 0;
        RxCounter2=0;
        for(i=0;i<6;i++)
        {
            RxBuffer2[i]=0x00;      //�����������������
        }
    }

}


