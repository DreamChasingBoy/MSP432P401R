#include "boylibs\headfile.h"


/**
 * main.c
 */
void main()
{
    system_init(0);
    set_DCO_48MH();
    boy_led_or_beep_init(BOYLEDALL);
    boy_led_or_beep_init(BOYBEEP);
    UART_init(UART3,9600);
    UART_init(UART2,115200);
    UART_init(UART0,115200);
    boy_ultrasonic_init();
    boy_speedpid_init();
    boy_positionpid_init();
    boy_anglepid_init();
    boy_grayscale_init();
    boy_motor_init();
    boy_encoder_init();
    BOYBEEP_OFF();
    boy_steer_init(90,90);
    TimerA_CCR0INT_init(TIMERA_A3,100);
    while(1)
    {
        boy_bluetooth_send_data(1,2,3,4);
        boy_steer_set(90,90);
        delay_ms(1000);
        boy_steer_set(45,45);
        delay_ms(1000);
    }
}
