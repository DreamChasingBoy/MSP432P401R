/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2019年1月23日22:29:47
-------------------------------------------------------------------------------------------------------*/
#include "headfile.h"
#include "exinisr.h"
/*************私有变量定义*****************/
uint8_t add_positionx,add_positiony;
uint8_t eeprom_positionx_middle,eeprom_positiony_middle,eeprom_positionx_left_up,eeprom_positiony_left_up,eeprom_positionx_right_up,eeprom_positiony_right_up;
uint8_t eeprom_positionx_left_down,eeprom_positiony_left_down,eeprom_positionx_right_down,eeprom_positiony_right_down;
uint8_t eeprom_flag=0;
uint8_t init_lock;
char str[100];
/*******************************/
extern char IRQ3_5flag;
extern char IRQ4_6flag;
extern char A_flag;
extern char B_flag;
extern uint8 dirf;
void PORT1_IRQHandler(void)
{
    uint8 IRQ_CLR = 0x00;
    if(P1->IFG & BIT1)
    {
        IRQ_CLR |= BIT1;
        gpio_toggle(GPIO_PORT_P1, GPIO_PIN0);
    }
    if(P1->IFG & BIT2)
    {
        IRQ_CLR |= BIT2;
        /*添加程序*/
    }
    if(P1->IFG & BIT3)
    {
        IRQ_CLR |= BIT3;
        /*添加程序*/
    }
    if(P1->IFG & BIT4)
    {
        IRQ_CLR |= BIT4;
        /*添加程序*/
    }
    if(P1->IFG & BIT5)
    {
        IRQ_CLR |= BIT5;
        /*添加程序*/
    }
    if(P1->IFG & BIT6)
    {
        IRQ_CLR |= BIT6;
        /*添加程序*/
    }
    if(P1->IFG & BIT7)
    {
        IRQ_CLR |= BIT7;
        /*添加程序*/
    }
    P1->IFG &= ~IRQ_CLR;
}

void PORT2_IRQHandler(void)
{
    uint8 IRQ_CLR = 0x00;
    if(P2->IFG & BIT1)
    {
        IRQ_CLR |= BIT1;
        /*添加程序*/
    }
    else if(P2->IFG & BIT2)
    {
        IRQ_CLR |= BIT2;
        /*添加程序*/
    }
    else if(P2->IFG & BIT3)
    {
        IRQ_CLR |= BIT3;
        encoder_B.dir=gpio_get(GPIO_PORT_P3,GPIO_PIN0);
        if(encoder_B.dir == 1)
            encoder_B.encoder--;
        else
            encoder_B.encoder++;

        /*添加程序*/
    }
    if(P2->IFG & BIT4)
    {
        IRQ_CLR |= BIT4;
        /*添加程序*/
    }
    if(P2->IFG & BIT5)
    {
        IRQ_CLR |= BIT5;
        /*添加程序*/
    }
    if(P2->IFG & BIT6)
    {
        IRQ_CLR |= BIT6;
        /*添加程序*/
    }
    if(P2->IFG & BIT7)
    {
        IRQ_CLR |= BIT7;
        /*添加程序*/
    }
    P2->IFG &= ~IRQ_CLR;
}

void PORT3_IRQHandler(void)
{
    uint8 IRQ_CLR = 0x00;
    if(P3->IFG & BIT1)
    {
        IRQ_CLR |= BIT1;
        /*添加程序*/
    }
    if(P3->IFG & BIT2)
    {
        IRQ_CLR |= BIT2;
        /*添加程序*/
    }
    if(P3->IFG & BIT3)
    {
        IRQ_CLR |= BIT3;
        /*添加程序*/
    }
    if(P3->IFG & BIT4)
    {
        IRQ_CLR |= BIT4;
        /*添加程序*/
    }
    if(P3->IFG & BIT5)
    {
        IRQ_CLR |= BIT5;
        A_flag=1;
        B_flag=0;
        IRQ3_5flag=1;
    }
    if(P3->IFG & BIT6)
    {
        IRQ_CLR |= BIT6;
        /*添加程序*/
    }
    if(P3->IFG & BIT7)
    {
        IRQ_CLR |= BIT7;
        /*添加程序*/
    }
    P3->IFG &= ~IRQ_CLR;
}
void PORT4_IRQHandler(void)
{
    uint8 IRQ_CLR = 0x00;

    if(P4->IFG & BIT1)
    {
        IRQ_CLR |= BIT1;
        /*添加程序*/
    }
    if(P4->IFG & BIT2)
    {
        IRQ_CLR |= BIT2;
        /*添加程序*/
    }
    if(P4->IFG & BIT3)
    {
        IRQ_CLR |= BIT3;
        /*添加程序*/
    }
    if(P4->IFG & BIT4)
    {
        IRQ_CLR |= BIT4;
        encoder_A.dir=gpio_get(GPIO_PORT_P4,GPIO_PIN5);
        if(encoder_A.dir == 1)
            encoder_A.encoder--;
        else
            encoder_A.encoder++;
    }
    if(P4->IFG & BIT5)
    {
        IRQ_CLR |= BIT5;
        /*添加程序*/
    }
    if(P4->IFG & BIT6)
    {
        IRQ_CLR |= BIT6;
        A_flag=0;
        B_flag=1;
        IRQ4_6flag=1;
    }
    if(P4->IFG & BIT7)
    {
        IRQ_CLR |= BIT7;
        /*添加程序*/
    }
    P4->IFG &= ~IRQ_CLR;
}

void PORT5_IRQHandler(void)
{
    uint8 IRQ_CLR = 0x00;
    if(P5->IFG & BIT1)
    {
        IRQ_CLR |= BIT1;
        encoder_D.dir=gpio_get(GPIO_PORT_P5,GPIO_PIN0);
        if(encoder_D.dir == 1)
            encoder_D.encoder++;
        else
            encoder_D.encoder--;
        /*添加程序*/
    }
    if(P5->IFG & BIT2)
    {
        IRQ_CLR |= BIT2;
        /*添加程序*/
    }
    if(P5->IFG & BIT3)
    {
        IRQ_CLR |= BIT3;
        /*添加程序*/
    }
    if(P5->IFG & BIT4)
    {
        IRQ_CLR |= BIT4;
        /*添加程序*/
    }
    if(P5->IFG & BIT5)
    {
        IRQ_CLR |= BIT5;
        /*添加程序*/
    }
    if(P5->IFG & BIT6)
    {
        IRQ_CLR |= BIT6;
        /*添加程序*/
    }
    if(P5->IFG & BIT7)
    {
        IRQ_CLR |= BIT7;
        /*添加程序*/
    }
    P5->IFG &= ~IRQ_CLR;
}

void PORT6_IRQHandler(void)
{
    uint8 IRQ_CLR = 0x00;
    if(P6->IFG & BIT0)
    {
        IRQ_CLR |= BIT0;
            /*添加程序*/
    }
    if(P6->IFG & BIT1)
    {
        IRQ_CLR |= BIT1;
        /*添加程序*/
    }
    if(P6->IFG & BIT2)
    {
        IRQ_CLR |= BIT2;
        /*添加程序*/
    }
    if(P6->IFG & BIT3)
    {
        IRQ_CLR |= BIT3;
        /*添加程序*/
    }
    if(P6->IFG & BIT4)
    {
        IRQ_CLR |= BIT4;
        /*添加程序*/
    }
    if(P6->IFG & BIT5)
    {
        IRQ_CLR |= BIT5;
        /*添加程序*/
    }
    if(P6->IFG & BIT6)
    {
        IRQ_CLR |= BIT6;
        encoder_C.dir=gpio_get(GPIO_PORT_P6,GPIO_PIN1);
        if(encoder_C.dir == 1)
            encoder_C.encoder++;
        else
            encoder_C.encoder--;
        /*添加程序*/
    }
    if(P6->IFG & BIT7)
    {
        IRQ_CLR |= BIT7;
        /*添加程序*/
    }
    P6->IFG &= ~IRQ_CLR;
}

void TA0_0_IRQHandler(void) {
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    gpio_toggle(GPIO_PORT_P1,GPIO_PIN0);
}


void TA1_0_IRQHandler(void) {
    TIMER_A1->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;


    /*添加程序*/
}
void TA2_0_IRQHandler(void) {
    TIMER_A2->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    /*添加程序*/

}
long int i = 0;
void TA3_0_IRQHandler(void) {
    TIMER_A3->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    char str_oled[50];
    if(init_lock)
    {
        if(eeprom_flag%2==0)
        {
            boy_steer_set_duty(encoder_A.encoder/5+4500,encoder_B.encoder/5+4500);
        }
    }
    else
    {
        X_real_position=RxCamera[0];
        Y_real_position=RxCamera[1];//测
        if(steer_pid_control!=0)
        {
//            if()
//            boy_p_foot=sqrt(((float)(abs)(RxCamera[0]-X_target_position))/((float)(abs)(RxCamera[1]-Y_target_position)));
//            boy_steerpid_init();
            if(steer_pid_control_x)
            {
                if(abs(X_target_position-X_real_position)<=1)
                {
                    boy_kill_integral_and_lasterror(&pidsteerX);
                    X_flag_arrive=1;
                }
                else
                {
                    boy_p_foot=sqrt(((float)(abs)(X_real_position-X_target_position))/((float)(abs)(Y_real_position-Y_target_position)));
                    boy_steerpid_init();
                    X_real_duty-=(int)pid_get_PID(&pidsteerX,X_target_position,X_real_position);
                }
            }
            if(steer_pid_control_y)
            {
                if(abs(Y_target_position-Y_real_position)<=1)
                {
                    boy_kill_integral_and_lasterror(&pidsteerY);
                    Y_flag_arrive=1;
                }
                else
                {
                    boy_p_foot=sqrt(((float)(abs)(X_real_position-X_target_position))/((float)(abs)(Y_real_position-Y_target_position)));
                    boy_steerpid_init();
                    Y_real_duty-=(int)pid_get_PID(&pidsteerY,Y_target_position,Y_real_position);//算
                }
            }

        }
        boy_steer_set_duty(4500+Y_real_duty,4500+X_real_duty);//控
    }
}

void TA0_N_IRQHandler(void)
{
    /*添加程序*/
}

void TA1_N_IRQHandler(void)
{
    /*添加程序*/
}

void TA2_N_IRQHandler(void)
{
    /*添加程序*/
}

void TA3_N_IRQHandler(void)
{
    if((TIMER_A3->CCTL[TIMERA_CCR0]&TIMER_A_CCTLN_CCIFG)&&//判断中断标志位是否有效
          (TIMER_A3->CCTL[TIMERA_CCR0]&TIMER_A_CCTLN_CCIE))//判断CCR1中断是否使能
       {
           /***************将TA3_N用作定时器中断时这几行务必保留****************/
           TIMER_A3->CCTL[TIMERA_CCR0] &= ~TIMER_A_CCTLN_CCIFG;//清除CCR1中断标志位
           TimerA_CCRVAL_set(TIMERA_A3,TIMERA_CCR0,TIMER_A3->CCR[TIMERA_CCR0] + CCRn_period_val[TIMERA_A3][TIMERA_CCR0]);//更新CCR寄存器
           /***************将TA3_N用作定时器中断时这几行务必保留****************/


           /***********************以下添加用户的处理函数*********************/

           /***********************用户处理函数添加结束行*********************/
       }
    if((TIMER_A3->CCTL[TIMERA_CCR1]&TIMER_A_CCTLN_CCIFG)&&//判断中断标志位是否有效
       (TIMER_A3->CCTL[TIMERA_CCR1]&TIMER_A_CCTLN_CCIE))//判断CCR1中断是否使能
    {
        /***************将TA3_N用作定时器中断时这几行务必保留****************/
        TIMER_A3->CCTL[TIMERA_CCR1] &= ~TIMER_A_CCTLN_CCIFG;//清除CCR1中断标志位
        TimerA_CCRVAL_set(TIMERA_A3,TIMERA_CCR1,TIMER_A3->CCR[TIMERA_CCR1] + CCRn_period_val[TIMERA_A3][TIMERA_CCR1]);//更新CCR寄存器
        /***************将TA3_N用作定时器中断时这几行务必保留****************/


        /***********************以下添加用户的处理函数*********************/

        /***********************用户处理函数添加结束行*********************/
    }
    if((TIMER_A3->CCTL[TIMERA_CCR2]&TIMER_A_CCTLN_CCIFG)&&//判断中断标志位是否有效
            (TIMER_A3->CCTL[TIMERA_CCR2]&TIMER_A_CCTLN_CCIE))//判断CCR2中断是否使能
    {
        /***************将TA3_N用作定时器中断时这几行务必保留****************/
        TIMER_A3->CCTL[TIMERA_CCR2] &= ~TIMER_A_CCTLN_CCIFG;//清除CCR2中断标志位
        TimerA_CCRVAL_set(TIMERA_A3,TIMERA_CCR2,TIMER_A3->CCR[TIMERA_CCR2] + CCRn_period_val[TIMERA_A3][TIMERA_CCR2]);//更新CCR寄存器
        /***************将TA3_N用作定时器中断时这几行务必保留****************/


        /***********************以下添加用户的处理函数*********************/

        /***********************用户处理函数添加结束行*********************/
    }
    if((TIMER_A3->CCTL[TIMERA_CCR3]&TIMER_A_CCTLN_CCIFG)&&//判断中断标志位是否有效
            (TIMER_A3->CCTL[TIMERA_CCR3]&TIMER_A_CCTLN_CCIE))//判断CCR3中断是否使能
    {
        /***************将TA3_N用作定时器中断时这几行务必保留****************/
        TIMER_A3->CCTL[TIMERA_CCR3] &= ~TIMER_A_CCTLN_CCIFG;//清除CCR3中断标志位
        TimerA_CCRVAL_set(TIMERA_A3,TIMERA_CCR3,TIMER_A3->CCR[TIMERA_CCR3] + CCRn_period_val[TIMERA_A3][TIMERA_CCR3]);//更新CCR寄存器
        /***************将TA3_N用作定时器中断时这几行务必保留****************/


        /***********************以下添加用户的处理函数*********************/

        /***********************用户处理函数添加结束行*********************/
    }
    if((TIMER_A3->CCTL[TIMERA_CCR4]&TIMER_A_CCTLN_CCIFG)&&//判断中断标志位是否有效
            (TIMER_A3->CCTL[TIMERA_CCR4]&TIMER_A_CCTLN_CCIE))//判断CCR4中断是否使能
    {
        /***************将TA3_N用作定时器中断时这几行务必保留****************/
        TIMER_A3->CCTL[TIMERA_CCR4] &= ~TIMER_A_CCTLN_CCIFG;//清除CCR4中断标志位
        TimerA_CCRVAL_set(TIMERA_A3,TIMERA_CCR4,TIMER_A3->CCR[TIMERA_CCR4] + CCRn_period_val[TIMERA_A3][TIMERA_CCR4]);//更新CCR寄存器
        /***************将TA3_N用作定时器中断时这几行务必保留****************/


        /***********************以下添加用户的处理函数*********************/

        /***********************用户处理函数添加结束行*********************/
    }
}
