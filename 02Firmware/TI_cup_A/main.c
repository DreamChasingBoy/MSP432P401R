
#include "boylibs\headfile.h"


void main()
{
    char str[100];
    system_init(0);
    set_DCO_48MH();
    EEPROM_init();
    eeprom_anglex_middle=EEPROM_read_float(0,0);
    eeprom_angley_middle=EEPROM_read_float(0,8);
    eeprom_anglex_left_up=EEPROM_read_float(0,16);
    eeprom_angley_left_up=EEPROM_read_float(0,24);
    eeprom_anglex_right_up=EEPROM_read_float(0,32);
    eeprom_angley_right_up=EEPROM_read_float(0,40);
    boy_steer_init(90+eeprom_angley_middle,90+eeprom_anglex_middle);//两个舵机都定在初始位置
    UART_init(UART0,115200);
    boy_encoder_init();
    boy_led_or_beep_init(BOYLEDALL);
    boy_key_init(BOYKEYALL);
    TimerA_CCR0INT_init(TIMERA_A3,100);
    initOK=1;
    while(1)
    {
       if(!boy_key_get(BOYKEY0))//当有按键按下
       {
           delay_ms(10);//延时消抖
           if(!boy_key_get(BOYKEY0))
           {
               eeprom_flag++;
               if(eeprom_flag==1)
               {
                   boy_encoder_clear();
                   eeprom_anglex_middle=add_anglex+eeprom_anglex_middle;
                   eeprom_angley_middle=add_angley+eeprom_angley_middle;
                   EEPROM_write_float(0,0,eeprom_anglex_middle);
                   EEPROM_write_float(0,8,eeprom_angley_middle);
               }
               if(eeprom_flag==3)
               {
                   boy_encoder_clear();
                   eeprom_anglex_left_up=add_anglex+eeprom_anglex_middle;
                   eeprom_angley_left_up=add_angley+eeprom_angley_middle;
                   EEPROM_write_float(0,16,eeprom_anglex_left_up);
                   EEPROM_write_float(0,24,eeprom_angley_left_up);
               }
               if(eeprom_flag==5)
               {
                   boy_encoder_clear();
                   eeprom_anglex_right_up=add_anglex+eeprom_anglex_middle;
                   eeprom_angley_right_up=add_angley+eeprom_angley_middle;
                   EEPROM_write_float(0,32,eeprom_anglex_right_up);
                   EEPROM_write_float(0,40,eeprom_angley_right_up);
               }
               BOYLED0_Toggle();
           }
           while(!boy_key_get(BOYKEY0));//等待松手
       }
       else if(!boy_key_get(BOYKEY1))
       {
           delay_ms(10);
           if(!boy_key_get(BOYKEY1))
           {
//               while(1)
//               {
//
//               }
               sprintf(str,"xmid=%f,ymid=%f,xleft=%f,yup=%f,xright=%f,ydown=%f\n",eeprom_anglex_middle+90,eeprom_angley_middle+90,eeprom_anglex_left_up+90,eeprom_angley_left_up+90,eeprom_anglex_right_up+90,eeprom_angley_right_up+90);
               UART_send_string(UART0,str);
           }
           while(!boy_key_get(BOYKEY1));
       }
    }
}
