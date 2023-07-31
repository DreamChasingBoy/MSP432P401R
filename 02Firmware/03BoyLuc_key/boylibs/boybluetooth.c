/*
 * boybluetooth.c
 *
 *  Created on: 2023年7月31日
 *      Author: BoyLuc追梦少年南南
 */
#include "boybluetooth.h"
uint8_t RxBluetooth[4]={0};
uint8_t TxBluetooth[6]={0x28,0,0,0,0,0x29};
/*************************************************
 * 函  数  名:boy_bluetooth_taskn
 * 功       能:发送指令的回调函数
 * 参       数:rx_cmd:传入函数的参数
 * 注 意 事 项:以下四个函数按顺序执行，只需要在函数中写出相应的动作和填入动作的参数即可
 *************************************************/
void boy_bluetooth_task1(uint8_t rx_cmd)
{
    /***************添加第一个要执行的任务****************/

    /***************结束第一个要执行的任务****************/
}
void boy_bluetooth_task2(uint8_t rx_cmd)
{
    /***************添加第二个要执行的任务****************/

    /***************结束第二个要执行的任务****************/
}
void boy_bluetooth_task3(uint8_t rx_cmd)
{
    /***************添加第三个要执行的任务****************/

    /***************结束第三个要执行的任务****************/
}
void boy_bluetooth_task4(uint8_t rx_cmd)
{
    /***************添加第四个要执行的任务****************/

    /***************结束第四个要执行的任务****************/
}
/*************************************************
 * 函  数  名:boy_bluetooth_send_data
 * 功       能:作为发送方向接收方发送指令
 * 参       数:cmd1:传入任务1的参数
 *            cmd2:传入任务2的参数
 *            cmd3:传入任务3的参数
 *            cmd4:传入任务4的参数
 * 注 意 事 项:此处设置为通过串口3发送数据，测试时可将串口3改成串口0。
 *           与boy_bluetooth_receive_data配合使用。
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
 * 函  数  名:boy_bluetooth_receive_data
 * 功       能:作为接收方接收发送方的指令
 * 参       数:com_data:收到的数据
 * 注 意 事 项:不需要理解或操作这个函数！！！不需要理解或操作这个函数！！！不需要理解或操作这个函数！！！
 *           你只需要完善下面的回调函数即可！！！你只需要完善下面的回调函数即可！！！你只需要完善下面的回调函数即可！！！
 *           一帧数据的格式有着严格的规定，按照以下格式传输相应的数据。每次只能传入四个指令！！！
 *           例如，当发送方传来一帧指令数据时（假设我们想传1、2、3、4进来），RxCamera获得的数据如下所示。
 *    格式   :  |  帧头 | cmd1 | cmd2 | cmd3 | cmd4 |  帧尾 |
 * TxBluetooth:| 0x28 | 0x01 | 0x02 | 0x03 | 0x04 | 0x29 |
 * RxBuffer2:  | 0x28 | 0x01 | 0x02 | 0x03 | 0x04 | 0x29 |
 * RxBluetooth:       { 0x01 , 0x02 , 0x03 , 0x04 }
 *           RxBuffer2用于临时接收发送方发来的数据，实际上不用去操作这个数组，函数已经帮你实现。
 *           这个函数在exinuart.c中EUSCIA2_IRQHandler()里面调用。
 *************************************************/
void boy_bluetooth_receive_data(uint8_t com_data)
{
    uint8_t i,k;
    static uint8_t RxCounter2=0;//计数
    static uint8_t RxBuffer2[6]={0};

    static uint8_t RxState2 = 0;//状态量
    static uint8_t RxFlag2 = 0;//旗帜

    if(RxState2==0&&com_data==0x28)  //0x28帧头
    {
        RxState2=1;
        RxBuffer2[RxCounter2++]=com_data;
    }

    else if(RxState2==1)
    {
        RxBuffer2[RxCounter2++]=com_data;
        if(RxCounter2>=6||com_data == 0x29)       //RxBuffer2接受满了,接收数据结束
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

    else   //接收异常
    {
        RxState2 = 0;
        RxCounter2=0;
        for(i=0;i<6;i++)
        {
            RxBuffer2[i]=0x00;      //将存放数据数组清零
        }
    }

}


