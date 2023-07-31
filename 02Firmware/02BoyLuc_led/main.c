/*****************************************************************************************************
  * @project    led
  * @author     BoyLuc׷����������
  * @version    V1.0
  * @date       2023-08-01
  * @brief      led�������
  * @phenomenon ����led��һ��������ÿ��һ�������죩һ�Ρ�
  * @attention  ����ǰע���Լ���dirverlib·����
  *             ��eо�����ҵĴ�������Ͻ��ж��η�װ���㷨��ƣ�������ΪΪ�ð��BSP��
  *             ����ҵ��;��������Ȩ�ؾ���
  ****************************************************************************************************/
#include "boylibs\headfile.h"
void main(void)
{
    system_init(0);
    set_DCO_48MH();
    boy_led_or_beep_init(BOYLEDALL);
    boy_led_or_beep_init(BOYBEEP);
    while(1)
    {
        BOYLED0_Toggle();
        BOYLED1_Toggle();
        BOYLED2_Toggle();
        BOYBEEP_Toggle();
        delay_ms(1000);
    }
}
