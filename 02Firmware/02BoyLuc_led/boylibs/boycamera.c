/*
 * boycamera.c
 *
 *  Created on: 2023年7月31日
 *      Author: BoyLuc追梦少年南南
 */
#include "boycamera.h"
uint8_t RxCamera[BOYCAMERADATASIZE]={0};
/*************************************************
 * 函  数  名:boy_camera_receive_data
 * 功       能:接收并处理摄像头（openmv或k210等）传来的数据，将结果保存在RxCamera[]中，后续处理直接调用该数组即可
 * 参       数:com_data:收到的数据
 * 注 意 事 项:一帧数据的格式有着严格的规定，按照以下格式传输相应的数据。参数BOYCAMERADATASIZE用于确定传入数据的长度。
 *           例如，当BOYCAMERADATASIZE设置为4的时，帧格式被锁定，当摄像头（openmv或k210等）传来一帧数据时（假设我们想传1、2、3、4进来），RxCamera获得的数据如下所示。
 *    格式   : |  帧头 | 数据1 | 数据2 | 数据3 | 数据4 |  帧尾 |
 *  camera  : | 0x41 | 0x01 | 0x02 | 0x03 | 0x04 | 0x46 |
 * RxBuffer1: | 0x41 | 0x01 | 0x02 | 0x03 | 0x04 | 0x46 |
 * RxCamera :        { 0x01 , 0x02 , 0x03 , 0x04 }
 *           RxBuffer1用于临时接收与存储摄像头发来的数据，实际上不用去操作这个数组，函数已经帮你实现。
 *           这个函数在exinuart.c中EUSCIA2_IRQHandler()里面调用。
 *************************************************/
void boy_camera_receive_data(uint8_t com_data)
{
    uint8_t i,k;
    static uint8_t RxCounter1=0;//计数
    static uint8_t RxBuffer1[BOYCAMERADATASIZE+2]={0};

    static uint8_t RxState1 = 0;//状态量
    static uint8_t RxFlag1 = 0;//旗帜

    if(RxState1==0&&com_data==0x41)  //0x41帧头
    {
        RxState1=1;
        RxBuffer1[RxCounter1++]=com_data;
    }

    else if(RxState1==1)
    {
        RxBuffer1[RxCounter1++]=com_data;
        if(RxCounter1>=BOYCAMERADATASIZE+2||com_data == 0x46)       //RxBuffer1接受满了,接收数据结束
        {
            RxState1=2;
            RxFlag1=1;
            RxCounter1=0;
            for(k=0;k<BOYCAMERADATASIZE;k++)
            {
                RxCamera[k]=RxBuffer1[k+1];
                RxBuffer1[k+1]=0;
            }
            /***************添加对RxCamera[BOYCAMERADATASIZE]的处理****************/

            /***************结束对RxCamera[BOYCAMERADATASIZE]的处理****************/
        }
    }

    else   //接收异常
    {
        RxState1 = 0;
        RxCounter1=0;
        for(i=0;i<BOYCAMERADATASIZE+2;i++)
        {
            RxBuffer1[i]=0x00;      //将存放数据数组清零
        }
    }

}




