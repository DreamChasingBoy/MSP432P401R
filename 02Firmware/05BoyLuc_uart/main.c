/*****************************************************************************************************
  * @project    uart
  * @author     BoyLuc׷����������
  * @version    V1.0
  * @date       2023-08-13
  * @brief      ���ڵ���
  * @phenomenon ÿ�����һ��Hello!I'm DreamChasingBoy!�����Զ�����
  * @attention  ����ǰע���Լ���dirverlib·����
  *             ��eо�����ҵĴ�������Ͻ��ж��η�װ���㷨��ƣ�������ΪΪ�ð��BSP��
  *             ����ҵ��;��������Ȩ�ؾ���
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
