
#include "boylibs\headfile.h"

uint8_t xmiddle[5],ymiddle[5];
uint8_t kernel_task=0;

void mySystemInit()//自定义一个SystemInit函数,函数体为空,这样错误即可消除
{
      #if (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2) |                 /* set CP10 Full Access */
                   (3UL << 11*2)  );               /* set CP11 Full Access */
  #endif

#ifdef UNALIGNED_SUPPORT_DISABLE
  SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
#endif


}
uint8_t three_xy(uint8_t x1,uint8_t x2,uint8_t n)
{
    // 计算三等分点的x坐标
    uint8_t third_x = x1 + (x2 - x1) / 3;
    uint8_t third_2 = x1 + n * (x2 - x1) / 3;
    // 根据参数n返回相应的三等分点x坐标
    switch (n) {
        case 1:
            return third_x;
        case 2:
            return third_2;
        default:
            // 对于不在1~3范围内的n，可以返回一个合理的默认值或者进行错误处理
            return 0;
    }
}
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
void if_black()
{
    if(RxCamera[2]==0)
        black_ground=0;//任务2
    else if((abs)((int)RxCamera[2]-(int)RxCamera[4])<=5||(abs)((int)RxCamera[3]-(int)RxCamera[5])<=5)
        black_ground=1;//任务3
    else//任务4
        black_ground=2;
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
    X_target_position=eeprom_positionx_middle=EEPROM_read_Byte(0,0);
    X_last_position=X_target_position+1;
    Y_target_position=eeprom_positiony_middle=EEPROM_read_Byte(0,8);
    Y_last_position==Y_target_position+1;
    eeprom_positionx_left_up=EEPROM_read_Byte(0,16);
    eeprom_positiony_left_up=EEPROM_read_Byte(0,24);
    eeprom_positionx_left_down=EEPROM_read_Byte(0,32);
    eeprom_positiony_left_down=EEPROM_read_Byte(0,40);
    eeprom_positionx_right_down=EEPROM_read_Byte(0,48);
    eeprom_positiony_right_down=EEPROM_read_Byte(0,56);
    eeprom_positionx_right_up=EEPROM_read_Byte(0,64);
    eeprom_positiony_right_up=EEPROM_read_Byte(0,72);
    UART_init(UART0,115200);
    UART_init(UART2,115200);
    boy_encoder_init();
    boy_led_or_beep_init(BOYLEDALL);
    boy_key_init(BOYKEYALL);
    boy_steer_init_duty(5000,4500);
    delay_ms(1000);
    EUSCI_A2->TXBUF=0x01;
    TimerA_CCR0INT_init(TIMERA_A3,10);
    initOK=1;
    while(1)
    {
       if(init_lock)
           BOYLED1_ON();
       else
           BOYLED1_OFF();


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
                   if_control_start=0;
                   boy_p_foot=1;
                   boy_steerpid_init();
                   steer_pid_control_x=steer_pid_control_y=1;
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
               if_control_start=1;
           }
           while(!boy_key_get(BOYKEY2));
       }
       else if(!boy_key_get(BOYKEY3))//当有按键3按下,暂停
       {
          delay_ms(10);
          if(!boy_key_get(BOYKEY3))
          {
              if(steer_pid_control==0) steer_pid_control=1;
              else steer_pid_control=0;
          }
          while(!boy_key_get(BOYKEY3));
       }
       else if(!boy_key_get(BOYKEY4))//当有按键3按下,暂停
       {
         delay_ms(10);
         if(!boy_key_get(BOYKEY4))
         {
             EUSCI_A2->TXBUF=0x05;
         }
         while(!boy_key_get(BOYKEY4));
       }
    }
}
