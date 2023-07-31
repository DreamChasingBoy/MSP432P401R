/*
 * boycamera.c
 *
 *  Created on: 2023��7��31��
 *      Author: BoyLuc׷����������
 */
#include "boycamera.h"
uint8_t RxCamera[BOYCAMERADATASIZE]={0};
/*************************************************
 * ��  ��  ��:boy_camera_receive_data
 * ��       ��:���ղ���������ͷ��openmv��k210�ȣ����������ݣ������������RxCamera[]�У���������ֱ�ӵ��ø����鼴��
 * ��       ��:com_data:�յ�������
 * ע �� �� ��:һ֡���ݵĸ�ʽ�����ϸ�Ĺ涨���������¸�ʽ������Ӧ�����ݡ�����BOYCAMERADATASIZE����ȷ���������ݵĳ��ȡ�
 *           ���磬��BOYCAMERADATASIZE����Ϊ4��ʱ��֡��ʽ��������������ͷ��openmv��k210�ȣ�����һ֡����ʱ�����������봫1��2��3��4��������RxCamera��õ�����������ʾ��
 *    ��ʽ   : |  ֡ͷ | ����1 | ����2 | ����3 | ����4 |  ֡β |
 *  camera  : | 0x41 | 0x01 | 0x02 | 0x03 | 0x04 | 0x46 |
 * RxBuffer1: | 0x41 | 0x01 | 0x02 | 0x03 | 0x04 | 0x46 |
 * RxCamera :        { 0x01 , 0x02 , 0x03 , 0x04 }
 *           RxBuffer1������ʱ������洢����ͷ���������ݣ�ʵ���ϲ���ȥ����������飬�����Ѿ�����ʵ�֡�
 *           ���������exinuart.c��EUSCIA2_IRQHandler()������á�
 *************************************************/
void boy_camera_receive_data(uint8_t com_data)
{
    uint8_t i,k;
    static uint8_t RxCounter1=0;//����
    static uint8_t RxBuffer1[BOYCAMERADATASIZE+2]={0};

    static uint8_t RxState1 = 0;//״̬��
    static uint8_t RxFlag1 = 0;//����

    if(RxState1==0&&com_data==0x41)  //0x41֡ͷ
    {
        RxState1=1;
        RxBuffer1[RxCounter1++]=com_data;
    }

    else if(RxState1==1)
    {
        RxBuffer1[RxCounter1++]=com_data;
        if(RxCounter1>=BOYCAMERADATASIZE+2||com_data == 0x46)       //RxBuffer1��������,�������ݽ���
        {
            RxState1=2;
            RxFlag1=1;
            RxCounter1=0;
            for(k=0;k<BOYCAMERADATASIZE;k++)
            {
                RxCamera[k]=RxBuffer1[k+1];
                RxBuffer1[k+1]=0;
            }
            /***************��Ӷ�RxCamera[BOYCAMERADATASIZE]�Ĵ���****************/

            /***************������RxCamera[BOYCAMERADATASIZE]�Ĵ���****************/
        }
    }

    else   //�����쳣
    {
        RxState1 = 0;
        RxCounter1=0;
        for(i=0;i<BOYCAMERADATASIZE+2;i++)
        {
            RxBuffer1[i]=0x00;      //�����������������
        }
    }

}




