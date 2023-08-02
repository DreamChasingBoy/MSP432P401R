
#include "boylibs\headfile.h"
uint8_t xmiddle[5],ymiddle[5];
void eeprom_clear()
{
    EEPROM_write_Byte(0,0,4500);
    EEPROM_write_Byte(0,8,4500);
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
    system_init(0);
    set_DCO_48MH();
    EEPROM_init();
    eeprom_positionx_middle=EEPROM_read_Byte(0,0);
    eeprom_positiony_middle=EEPROM_read_Byte(0,8);
    eeprom_positionx_left_up=EEPROM_read_Byte(0,16);
    eeprom_positiony_left_up=EEPROM_read_Byte(0,24);
    eeprom_positionx_right_up=EEPROM_read_Byte(0,32);
    eeprom_positiony_right_up=EEPROM_read_Byte(0,40);
    eeprom_positionx_left_down=EEPROM_read_Byte(0,48);
    eeprom_positiony_left_down=EEPROM_read_Byte(0,56);
    eeprom_positionx_right_down=EEPROM_read_Byte(0,64);
    eeprom_positiony_right_down=EEPROM_read_Byte(0,72);
    boy_steer_init_duty(4500,4500);
    UART_init(UART0,115200);
    UART_init(UART2,115200);
    boy_encoder_init();
    boy_led_or_beep_init(BOYLEDALL);
    boy_key_init(BOYKEYALL);
    TimerA_CCR0INT_init(TIMERA_A3,100);
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
       if(!boy_key_get(BOYKEY0))//���а���0����
       {
           delay_ms(10);//��ʱ����
           if(!boy_key_get(BOYKEY0))
           {
               if(init_lock)
               {
                  eeprom_flag++;
                  if(eeprom_flag==1)//�м�
                  {
                      eeprom_positionx_middle=add_positionx+eeprom_positionx_middle;
                      eeprom_positiony_middle=add_positiony+eeprom_positiony_middle;
                      EEPROM_write_Byte(0,0,eeprom_positionx_middle);
                      EEPROM_write_Byte(0,8,eeprom_positiony_middle);
                  }
                  if(eeprom_flag==3)//����
                  {
                      eeprom_positionx_left_up=encoder_A.encoder/10+eeprom_positionx_middle;
                      eeprom_positiony_left_up=encoder_B.encoder/10+eeprom_positiony_middle;
                      EEPROM_write_Byte(0,16,eeprom_positionx_left_up);
                      EEPROM_write_Byte(0,24,eeprom_positiony_left_up);
                  }
                  if(eeprom_flag==5)//����
                    {
                        __disable_interrupt();
                        eeprom_positionx_left_down=encoder_A.encoder/10+eeprom_positionx_middle;
                        eeprom_positiony_left_down=encoder_B.encoder/10+eeprom_positiony_middle;
                        boy_encoder_clear();
                        EEPROM_write_Byte(0,32,eeprom_positionx_left_down);
                        EEPROM_write_Byte(0,40,eeprom_positiony_left_down);
                        __enable_interrupt();
                    }
//                  if(eeprom_flag==5)//����
//                  {
//                      boy_encoder_clear();
//                      eeprom_positionx_left_down=add_positionx+eeprom_positionx_middle;
//                      eeprom_positiony_left_down=add_positiony+eeprom_positiony_middle;
//                      EEPROM_write_Byte(0,48,eeprom_positionx_left_down);
//                      EEPROM_write_Byte(0,56,eeprom_positiony_left_down);
//                      boy_steer_set(90+eeprom_positiony_middle,90+eeprom_positionx_middle);//�ص��м�
//                      add_positionx=add_positiony=0;
//                  }
//                  if(eeprom_flag==7)//����
//                  {
//                      boy_encoder_clear();
//                      eeprom_positionx_right_down=add_positionx+eeprom_positionx_middle;
//                      eeprom_positiony_right_down=add_positiony+eeprom_positiony_middle;
//                      EEPROM_write_Byte(0,64,eeprom_positionx_right_down);
//                      EEPROM_write_Byte(0,72,eeprom_positiony_right_down);
//                      boy_steer_set(90+eeprom_positiony_middle,90+eeprom_positionx_middle);//�ص��м�
//                      add_positionx=add_positiony=0;
//                  }
//                  if(eeprom_flag==9)//����
//                  {
//                      boy_encoder_clear();
//                      eeprom_positionx_right_up=add_positionx+eeprom_positionx_middle;
//                      eeprom_positiony_right_up=add_positiony+eeprom_positiony_middle;
//                      EEPROM_write_Byte(0,64,eeprom_positionx_right_up);
//                      EEPROM_write_Byte(0,72,eeprom_positiony_right_up);
//                      add_positionx=add_positiony=0;
//                  }
                  BOYLED0_Toggle();
               }
               else
               {
//                   boy_steer_set_duty(eeprom_positiony_middle,eeprom_positionx_middle);//�ص��м�
               }

           }
           while(!boy_key_get(BOYKEY0));//�ȴ�����
       }
       else if(!boy_key_get(BOYKEY1))//���а���1����
       {
           delay_ms(10);
           if(!boy_key_get(BOYKEY1))
           {
               init_lock=~init_lock;
           }
           while(!boy_key_get(BOYKEY1));
       }
       else if(!boy_key_get(BOYKEY2))//���а���2����
       {
           delay_ms(10);
           if(!boy_key_get(BOYKEY2))
           {
           }
           while(!boy_key_get(BOYKEY2));
       }
       else if(!boy_key_get(BOYKEY3))//���а���2����
      {
          delay_ms(10);
          if(!boy_key_get(BOYKEY3))
          {
          }
          while(!boy_key_get(BOYKEY3));
      }
    }
}
