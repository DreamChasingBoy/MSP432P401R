
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
    X_last_position=X_target_position=eeprom_positionx_middle=EEPROM_read_Byte(0,0);
    Y_last_position=Y_target_position=eeprom_positiony_middle=EEPROM_read_Byte(0,8);
//    X_target_position=118;
//    Y_target_position=10;
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
//    sprintf(str,"youshangx=%d,youshangy=%d\r\n",eeprom_positionx_right_up,eeprom_positiony_right_up);
//    UART_send_string(UART0,str);
//    sprintf(str,"youxiax=%d,youxiay=%d\r\n",eeprom_positionx_right_down,eeprom_positiony_right_down);
//    UART_send_string(UART0,str);
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
       if(if_control_start==1)
       {
           X_flag_arrive=Y_flag_arrive=0;
           switch(task_state)
           {
//           case 0: task_state=go_where(60,24,task_state,2); break;
//          case 1: task_state=go_where(120,24,task_state,1); break;
//          case 2: task_state=go_where(120,64,task_state,0); break;
//          case 3: task_state=go_where(60,64,task_state,1); break;
//          case 4: task_state=go_where(60,24,task_state,0); break;
           case 0: task_state=go_where(eeprom_positionx_left_up,eeprom_positiony_left_up,task_state,2); break;
           case 1: task_state=go_where(eeprom_positionx_right_up,eeprom_positiony_right_up,task_state,1); break;
           case 2: task_state=go_where(eeprom_positionx_right_down,eeprom_positiony_right_down,task_state,0); break;
           case 3: task_state=go_where(eeprom_positionx_left_down,eeprom_positiony_left_down,task_state,1); break;
           case 4: task_state=go_where(eeprom_positionx_left_up,eeprom_positiony_left_up,task_state,0); break;
           default: break;
           }
       }

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
                      OLED_clr();
                      EEPROM_write_Byte(0,0,RxCamera[0]);
                      EEPROM_write_Byte(0,8,RxCamera[1]);
                      sprintf(str_oled,"xmid=%d,ymid=%d",RxCamera[0],RxCamera[1]);
                      OLED_Show_String(0,0,str_oled,8);
                  }
                  if(eeprom_flag==3)//����
                  {
                      OLED_clr();
                      EEPROM_write_Byte(0,16,RxCamera[0]);
                      EEPROM_write_Byte(0,24,RxCamera[1]);
                      sprintf(str_oled,"xupl=%d,yupl=%d",RxCamera[0],RxCamera[1]);
                      OLED_Show_String(0,0,str_oled,8);
                  }
                  if(eeprom_flag==5)//����
                  {
                      OLED_clr();
                      EEPROM_write_Byte(0,32,RxCamera[0]);
                      EEPROM_write_Byte(0,40,RxCamera[1]);
                      sprintf(str_oled,"xdnl=%d,ydnl=%d",RxCamera[0],RxCamera[1]);
                      OLED_Show_String(0,0,str_oled,8);
                  }
                  if(eeprom_flag==7)//����
                  {
                      OLED_clr();
                      EEPROM_write_Byte(0,48,RxCamera[0]);
                      EEPROM_write_Byte(0,56,RxCamera[1]);
                      sprintf(str_oled,"xdnr=%d,ydnr=%d",RxCamera[0],RxCamera[1]);
                      OLED_Show_String(0,0,str_oled,8);
                  }
                  if(eeprom_flag==9)//����
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
                   if_control_start=0;
                   boy_p_foot=1;
                   boy_steerpid_init();
                   steer_pid_control_x=steer_pid_control_y=1;
                   X_target_position=eeprom_positionx_middle;
                   Y_target_position=eeprom_positiony_middle;
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
               if_control_start=1;
           }
           while(!boy_key_get(BOYKEY2));
       }
       else if(!boy_key_get(BOYKEY3))//���а���3����,��ͣ
      {
          delay_ms(10);
          if(!boy_key_get(BOYKEY3))
          {
              if(steer_pid_control==0) steer_pid_control=1;
              else steer_pid_control=0;
//              boy_kill_integral_and_lasterror(&pidsteerX);boy_kill_integral_and_lasterror(&pidsteerY);
//              X_target_position=118;
//              Y_target_position=96;
          }
          while(!boy_key_get(BOYKEY3));
      }
    }
}
