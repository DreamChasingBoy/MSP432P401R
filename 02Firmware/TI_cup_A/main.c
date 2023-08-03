
#include "boylibs\headfile.h"
uint8_t xmiddle[5],ymiddle[5];
uint8_t kernel_task=0;
void eeprom_clear()
{
    EEPROM_write_Byte(0,0,0);
    EEPROM_write_Byte(0,8,0);
    EEPROM_write_Byte(0,16,0);
    EEPROM_write_Byte(0,24,0);
    EEPROM_write_Byte(0,32,0);
    EEPROM_write_Byte(0,40,0);
    EEPROM_write_Byte(0,48,0);
    EEPROM_write_Byte(0,56,0);
    EEPROM_write_Byte(0,64,0);
    EEPROM_write_Byte(0,72,0);
}
void main()
{
    char str[100];
    char str_oled_x[50];
    char str_oled[100];
    boy_steerpid_init();
    system_init(0);
    set_DCO_48MH();
    OLED_init();
    OLED_clr();
    EEPROM_init();
    eeprom_positionx_middle=X_target_position=EEPROM_read_Byte(0,0);
    eeprom_positiony_middle=Y_target_position=EEPROM_read_Byte(0,8);
//    X_target_position=0x47;
//    Y_target_position=0x48;
    eeprom_positionx_left_up=EEPROM_read_Byte(0,16);
    eeprom_positiony_left_up=EEPROM_read_Byte(0,24);
    eeprom_positionx_left_down=EEPROM_read_Byte(0,32);
    eeprom_positiony_left_down=EEPROM_read_Byte(0,40);
    eeprom_positionx_right_down=EEPROM_read_Byte(0,48);
    eeprom_positiony_right_down=EEPROM_read_Byte(0,56);
    eeprom_positionx_right_up=EEPROM_read_Byte(0,64);
    eeprom_positiony_right_up=EEPROM_read_Byte(0,72);
    boy_steer_init_duty(4500,4500);
    UART_init(UART0,115200);
    UART_init(UART2,115200);
    boy_encoder_init();
    boy_led_or_beep_init(BOYLEDALL);
    boy_key_init(BOYKEYALL);
    TimerA_CCR0INT_init(TIMERA_A3,10);
    initOK=1;
    while(1)
    {
       if(init_lock)
           BOYLED1_ON();
       else
           BOYLED1_OFF();
       UART_send_Byte(UART0,RxCamera[0]);
       UART_send_Byte(UART0,RxCamera[1]);
       delay_ms(100);
       if(!boy_key_get(BOYKEY0))//当有按键0按下
       {
           delay_ms(10);//延时消抖
           if(!boy_key_get(BOYKEY0))
           {
               if(init_lock)
               {
                  eeprom_flag++;
                  if(eeprom_flag==1)//中间
                  {
                      OLED_clr();
                      EEPROM_write_Byte(0,0,RxCamera[0]);
                      EEPROM_write_Byte(0,8,RxCamera[1]);
                      sprintf(str_oled,"xmid=%d,ymid=%d",RxCamera[0],RxCamera[1]);
                      OLED_Show_String(0,0,str_oled,8);
                  }
                  if(eeprom_flag==3)//左上
                  {
                      OLED_clr();
                      EEPROM_write_Byte(0,16,RxCamera[0]);
                      EEPROM_write_Byte(0,24,RxCamera[1]);
                      sprintf(str_oled,"xupl=%d,yupl=%d",RxCamera[0],RxCamera[1]);
                      OLED_Show_String(0,0,str_oled,8);
                  }
                  if(eeprom_flag==5)//左下
                  {
                      OLED_clr();
                      EEPROM_write_Byte(0,32,RxCamera[0]);
                      EEPROM_write_Byte(0,40,RxCamera[1]);
                      sprintf(str_oled,"xdnl=%d,ydnl=%d",RxCamera[0],RxCamera[1]);
                      OLED_Show_String(0,0,str_oled,8);
                  }
                  if(eeprom_flag==7)//右下
                  {
                      OLED_clr();
                      EEPROM_write_Byte(0,48,RxCamera[0]);
                      EEPROM_write_Byte(0,56,RxCamera[1]);
                      sprintf(str_oled,"xdnr=%d,ydnr=%d",RxCamera[0],RxCamera[1]);
                      OLED_Show_String(0,0,str_oled,8);
                  }
                  if(eeprom_flag==9)//右上
                  {
                      OLED_clr();
                      EEPROM_write_Byte(0,64,RxCamera[0]);
                      EEPROM_write_Byte(0,72,RxCamera[1]);
                      sprintf(str_oled,"xupr=%d,yupr=%d",RxCamera[0],RxCamera[1]);
                      OLED_Show_String(0,0,str_oled,8);
                  }
                  BOYLED0_Toggle();
               }
               else
               {
                   X_target_position=eeprom_positionx_middle;
                   Y_target_position=eeprom_positiony_middle;
               }

           }
           while(!boy_key_get(BOYKEY0));//等待松手
       }
       else if(!boy_key_get(BOYKEY1))//当有按键1按下
       {
           delay_ms(10);
           if(!boy_key_get(BOYKEY1))
           {
               init_lock=~init_lock;
           }
           while(!boy_key_get(BOYKEY1));
       }
       else if(!boy_key_get(BOYKEY2))//当有按键2按下
       {
           delay_ms(10);
           if(!boy_key_get(BOYKEY2))
           {
               X_target_position=eeprom_positionx_left_up;
               Y_target_position=eeprom_positiony_left_up;
           }
           while(!boy_key_get(BOYKEY2));
       }
       else if(!boy_key_get(BOYKEY3))//当有按键3按下
      {
          delay_ms(10);
          if(!boy_key_get(BOYKEY3))
          {
              X_target_position=eeprom_positionx_left_down;
              Y_target_position=eeprom_positiony_left_down;
          }
          while(!boy_key_get(BOYKEY3));
      }
    }
}
