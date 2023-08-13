/*****************************************************************************************************
  * @project    uart
  * @author     BoyLuc追梦少年南南
  * @version    V1.0
  * @date       2023-08-13
  * @brief      串口调试
  * @phenomenon 每秒输出一次Hello!I'm DreamChasingBoy!，并自动换行
  * @attention  编译前注意自己的dirverlib路径；
  *             在e芯工作室的代码基础上进行二次封装与算法设计，可以视为为该板的BSP；
  *             非商业用途，盗版侵权必究！
  ****************************************************************************************************/
#include "boylibs\headfile.h"
void main(void)
{
    system_init(0);
    set_DCO_48MH();
    UART_init(UART0,115200);
    while(1)
    {
        UART_send_string(UART0, "Hello!I'm DreamChasingBoy!\r\n");
        delay_ms(1000);
    }
}
