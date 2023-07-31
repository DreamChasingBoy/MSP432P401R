/*****************************************************************************************************
  * @project    led
  * @author     BoyLuc追梦少年南南
  * @version    V1.0
  * @date       2023-08-01
  * @brief      led与蜂鸣器
  * @phenomenon 三个led与一个蜂鸣器每个一秒亮灭（响）一次。
  * @attention  编译前注意自己的dirverlib路径；
  *             在e芯工作室的代码基础上进行二次封装与算法设计，可以视为为该板的BSP；
  *             非商业用途，盗版侵权必究！
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
