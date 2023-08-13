/*****************************************************************************************************
  * @project    key
  * @author     BoyLuc追梦少年南南
  * @version    V1.0
  * @date       2023-08-13
  * @brief      按键
  * @phenomenon 按下KEY0和KYE1会在oled上显示效果
  * @attention  编译前注意自己的dirverlib路径；
  *             在e芯工作室的代码基础上进行二次封装与算法设计，可以视为为该板的BSP；
  *             非商业用途，盗版侵权必究！
  ****************************************************************************************************/
#include "boylibs\headfile.h"

//void main()
//{
//    system_init(0);
//    set_DCO_48MH();
//    boy_led_or_beep_init(BOYLEDALL);
//    boy_led_or_beep_init(BOYBEEP);
//    UART_init(UART3,9600);
//    UART_init(UART2,115200);
//    UART_init(UART0,115200);
//    boy_ultrasonic_init();
//    boy_speedpid_init();
//    boy_positionpid_init();
//    boy_anglepid_init();
//    boy_grayscale_init();
//    boy_motor_init();
//    boy_encoder_init();
//    BOYBEEP_OFF();
//    boy_steer_init(90,90);
//    TimerA_CCR0INT_init(TIMERA_A3,100);
//    while(1)
//    {
//        boy_bluetooth_send_data(1,2,3,4);
//        boy_steer_set(90,90);
//        delay_ms(1000);
//        boy_steer_set(45,45);
//        delay_ms(1000);
//    }
//}
//void main()
//{
//    system_init(1);
//    set_DCO_48MH();
//    I2C_Init();
//    boy_led_or_beep_init(BOYLED0);
//    while(MPU6050Init());
//    BOYLED0_ON();
//    UART_init(UART0,115200);
//    TimerA_CCR0INT_init(TIMERA_A3,100);
//    initOK=1;
//    while(1)
//    {
////        GetMPU6050Data();
////
////        sprintf(str, "p:%d,r:%d,y:%d\r\n",g_MPUManager.accX,g_MPUManager.accY,g_MPUManager.accZ);
////        sprintf(str, "pg:%d,rg:%d,yg:%d\r\n",g_MPUManager.gyroX,g_MPUManager.gyroY,g_MPUManager.gyroZ);
////        UART_send_string(UART0, str);
////        delay_ms(500);
//    }
//}
void main()
{
    system_init(0);
    set_DCO_48MH();
    boy_steer_init(90,90);
    UART_init(UART0,115200);
    TimerA_CCR0INT_init(TIMERA_A3,100);
    initOK=1;
    while(1)
    {

    }
}
