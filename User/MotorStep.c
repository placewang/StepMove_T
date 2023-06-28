#include "gd32f4xx.h"
#include "Gpio.h"
#include "morotstep.h"
#include "morot.h"
#include "time.h"
#include "math.h"


speedRampData MotorPr1,MotorPr2,MotorPr3,MotorPr4;
speedRampData MotorPr5,MotorPr6,MotorPr7,MotorPr8;
speedRampData MotorPr9,MotorPr10,MotorPr11,MotorPr12;




/*! \brief 以给定的步数移动步进电机
 *  通过计算加速到最大速度，以给定的步数开始减速
 *  如果加速度和减速度很小，步进电机会移动很慢，还没达到最大速度就要开始减速
 *  \param step   移动的步数 (正数为顺时针，负数为逆时针).
 *  \param accel  加速度,如果取值为10，实际值为10*0.1*rad/sec^2=1rad/sec^2
 *  \param decel  减速度,如果取值为10，实际值为10*0.1*rad/sec^2=1rad/sec^2
 *  \param speed  Hz
 */
int8_t stepper_move_T(uint8_t starnum,uint8_t endnum,uint8_t mode, int32_t step,
                      uint32_t accel, uint32_t decel, uint32_t speed)
{ 
    speedRampData *MtPr[13]={NULL,&MotorPr1,&MotorPr2,&MotorPr3,&MotorPr4,\
                                  &MotorPr5,&MotorPr6,&MotorPr7,&MotorPr8,\
                                  &MotorPr9,&MotorPr10,&MotorPr11,&MotorPr12 
                            };
    volatile MotorRun * Mtcr[13]={NULL,&Mt_Move_1,&Mt_Move_2,&Mt_Move_3,&Mt_Move_4,\
                                        &Mt_Move_5,&Mt_Move_6,&Mt_Move_7,&Mt_Move_8,\
                                        &Mt_Move_9,&Mt_Move_10,&Mt_Move_11,&Mt_Move_12    
                                };    

   int32_t AbsoluteVal=0;
   int32_t  Encoder=0;   
                                   
    //达到最大速度时的步数.
    unsigned int max_s_lim;
    //必须开始减速的步数(如果还没加速到达最大速度时)。
    unsigned int accel_lim;
    if((starnum==0||endnum==0)||(starnum>12||endnum>12))
        return -1;                            
    if(speed>10*10*100)
         return -1;        
    if(speed<10)
        speed=15;
     AbsoluteVal=step<0?-(step):step;
     AbsoluteVal--;   
     speed=0.16*speed;
     for(char i=starnum;i<=endnum;i++)
     {    
         if(mode)
         {
            MtPr[i]->dir=step<0?0:1;    
            Motor_Dir_Set(i,step<0?0:1);
         }   
         else
         {
            Encoder=step-(MtPr[i]->MotEncoder); 
            AbsoluteVal=Encoder<0?-Encoder:Encoder;
            AbsoluteVal--;
            MtPr[i]->dir=MtPr[i]->MotEncoder>step?0:1; 
            Motor_Dir_Set(i,MtPr[i]->MotEncoder>step?0:1);
         } 	
        Motor_Current_Set(i,i,Mtcr[i]->RunCurrent);         
        // 如果只移动一步
        if((AbsoluteVal)==0)
        {
            // 只移动一步
            MtPr[i]->accel_count = -1;
            // 减速状态
            MtPr[i]->run_state = DECEL;
            // 短延时
            MtPr[i]->step_delay = 1000;
            if(MtPr[i]->dir)
                MtPr[i]->MotEncoder--;
            else
                MtPr[i]->MotEncoder++;   
            // 配置电机为运行状态
            Motor_Star_Set(i,i);
        }	
        // 步数不为零才移动
        else if(AbsoluteVal != 0)
        {
            // 设置最大速度极限, 计算得到min_delay用于定时器的计数器的值。
            // min_delay = (alpha / tt)/ w
            MtPr[i]->min_delay = (int32_t)(A_T_x10/speed);

            // 通过计算第一个(c0) 的步进延时来设定加速度，其中accel单位为0.1rad/sec^2
            MtPr[i]->step_delay = (int32_t)((T1_FREQ_148 * sqrt(A_SQ / accel))/10);

            // 计算多少步之后达到最大速度的限制
            // max_s_lim = speed^2 / (2*alpha*accel)
            max_s_lim = (uint32_t)(speed*speed/(A_x200*accel/10));
            // 如果达到最大速度小于0.5步，我们将四舍五入为0
            // 但实际我们必须移动至少一步才能达到想要的速度
            if(max_s_lim == 0)
            {
                    max_s_lim = 1;
            }
            // 计算多少步之后我们必须开始减速
            // n1 = (n1+n2)decel / (accel + decel)
            accel_lim = (uint32_t)(AbsoluteVal*decel/(accel+decel));
            // 我们必须加速至少1步才能才能开始减速.
            if(accel_lim == 0)
            {
                accel_lim = 1;
            }
            // 使用限制条件我们可以计算出第一次开始减速的位置
            //MtPr[i]->decel_val为负数
            if(accel_lim <= max_s_lim)
            {
                MtPr[i]->decel_val = accel_lim - AbsoluteVal;
            }
            else{
                MtPr[i]->decel_val = -(max_s_lim*accel/decel);
            }
            // 当只剩下一步我们必须减速
            if(MtPr[i]->decel_val == 0)
                MtPr[i]->decel_val = -1;
            // 计算开始减速时的步数
            MtPr[i]->decel_start = AbsoluteVal + MtPr[i]->decel_val;

            // 如果最大速度很慢，我们就不需要进行加速运动
            if(MtPr[i]->step_delay <= MtPr[i]->min_delay)
            {
                MtPr[i]->step_delay = MtPr[i]->min_delay;
                MtPr[i]->run_state = RUN;
            }
            else
            {
                MtPr[i]->run_state = ACCEL;
            }
            // 复位加速度计数值
            MtPr[i]->accel_count = 0;
            Motor_Star_Set(i,i);
        }
    }
    return 0;
}

/**
  * @brief  速度决策
	*	@note 	在中断中使用，每进一次中断，决策一次
  * @retval 无
  */
void speed_decision(uint8_t Mnum,speedRampData *srd)
{
    srd->i++;             // 定时器中断次数计数值
    if(srd->i==2)         // 2次，说明已经输出一个完整脉冲
    {
        srd->i=0;         // 清零定时器中断次数计数值
        switch(srd->run_state) 
        {
        /*步进电机停止状态*/
        case STOP:
            // 清零步数计数器
            srd->step_count = 0;  
            // 清零余值
            srd->rest = 0;        
            Motor_Stop_Set(Mnum,Mnum);
            break;
        /*步进电机加速状态*/
        case ACCEL:
            if(srd->dir)
                srd->MotEncoder++;
            else
               srd->MotEncoder--;
            srd->step_count++;    
            srd->accel_count++;
            //计算新(下)一步脉冲周期(时间间隔)
            srd->new_step_delay = srd->step_delay - (((2 *srd->step_delay) + srd->rest)/(4 * srd->accel_count + 1));
            // 计算余数，下次计算补上余数，减少误差
            srd->rest = ((2 * srd->step_delay)+srd->rest)%(4 * srd->accel_count + 1);
            //检查是够应该开始减速
            if(srd->step_count >= srd->decel_start){
                srd->accel_count = srd->decel_val;
                srd->run_state = DECEL;
            }
            //检查是否到达期望的最大速度
            else if(srd->new_step_delay <= srd->min_delay){
                srd->last_accel_delay = srd->new_step_delay;
                srd->new_step_delay = srd->min_delay;    
                srd->rest = 0;                          
                srd->run_state = RUN;
            }
            break;
        /*步进电机最大速度运行状态*/
        case RUN:
            if(srd->dir)
                srd->MotEncoder++;
            else
               srd->MotEncoder--;
            srd->step_count++; 
            srd->new_step_delay = srd->min_delay;
            //检查是否需要开始减速
            if(srd->step_count >= srd->decel_start) 
            {
                srd->accel_count = srd->decel_val;
                //以最后一次加速的延时作为开始减速的延时
                srd->new_step_delay = srd->last_accel_delay;
                srd->run_state = DECEL;
            }
            break;
        /*步进电机减速状态*/
        case DECEL:
            if(srd->dir)
                srd->MotEncoder++;
            else
               srd->MotEncoder--;
        
            srd->step_count++; 
            srd->accel_count++;
            //计算新(下)一步脉冲周期(时间间隔)
            srd->new_step_delay = srd->step_delay - (((2 * srd->step_delay) +srd->rest)/(4 * srd->accel_count + 1)); 
            // 计算余数，下次计算补上余数，减少误差
            srd->rest = ((2 * srd->step_delay)+srd->rest)%(4 * srd->accel_count + 1);
            //检查是否为最后一步
            if(srd->accel_count >= 0)
            {
                if(srd->dir)
                    srd->MotEncoder=(srd->MotEncoder+1); 
                else
                    srd->MotEncoder=srd->MotEncoder-1;                
           
               srd->run_state = STOP;
            }
            break;
        }
    /*求得下一次间隔时间*/
    srd->step_delay = srd->new_step_delay;  
	}
}




/*比较中断处理函数_Mt1*/
signed char TIM2_Interrupt_Mt1(void)
{
    speed_decision(Motor1,&MotorPr1);
    timer_autoreload_value_config(TIMER2,0xffff&(MotorPr1.step_delay));    
    gpio_bit_toggle(MT1_STEP_PORT,MT1_STEP_PIN);   
    return 0;
}
/*
比较中断处理函数_Mt2*/
signed char TIM5_Interrupt_Mt2(void)
{
    speed_decision(Motor2,&MotorPr2);
    timer_autoreload_value_config(TIMER5,0xffff&(MotorPr2.step_delay));    
    gpio_bit_toggle(MT2_STEP_PORT,MT2_STEP_PIN);   
    return 0;
}
/*比较中断处理函数_Mt3*/
signed char TIM6_Interrupt_Mt3(void)
{
    speed_decision(Motor3,&MotorPr3);
    timer_autoreload_value_config(TIMER6,0xffff&(MotorPr3.step_delay));    
    gpio_bit_toggle(MT3_STEP_PORT,MT3_STEP_PIN);   
    return 0;
}
/*比较中断处理函数_Mt4*/

signed char TIM1_Interrupt_Mt4(void)
{       
    speed_decision(Motor4,&MotorPr4);
    timer_autoreload_value_config(TIMER1,0xffff&(MotorPr4.step_delay));
    gpio_bit_toggle(MT4_STEP_PORT,MT4_STEP_PIN);  
    return 0;
}



/*比较中断处理函数_Mt5*/
signed char TIM8_Interrupt_Mt5(void)
{
    speed_decision(Motor5,&MotorPr5);
    timer_autoreload_value_config(TIMER8,0xffff&(MotorPr5.step_delay));    
    gpio_bit_toggle(MT5_STEP_PORT,MT5_STEP_PIN);   
    return 0;
}
/*
比较中断处理函数_Mt6*/
signed char TIM9_Interrupt_Mt6(void)
{
    speed_decision(Motor6,&MotorPr6);
    timer_autoreload_value_config(TIMER9,0xffff&(MotorPr6.step_delay));    
    gpio_bit_toggle(MT6_STEP_PORT,MT6_STEP_PIN);   
    return 0;
}
/*比较中断处理函数_Mt7*/
signed char TIM10_Interrupt_Mt7(void)
{
    speed_decision(Motor7,&MotorPr7);
    timer_autoreload_value_config(TIMER10,0xffff&(MotorPr7.step_delay));    
    gpio_bit_toggle(MT7_STEP_PORT,MT7_STEP_PIN);   
    return 0;
}
/*比较中断处理函数_Mt8*/

signed char TIM11_Interrupt_Mt8(void)
{ 
    speed_decision(Motor8,&MotorPr8);
    timer_autoreload_value_config(TIMER11,0xffff&(MotorPr8.step_delay));    
    gpio_bit_toggle(MT8_STEP_PORT,MT8_STEP_PIN);   
    return 0;
}


/*比较中断处理函数_Mt9*/
signed char TIM12_Interrupt_Mt9(void)
{
    speed_decision(Motor9,&MotorPr9);
    timer_autoreload_value_config(TIMER12,0xffff&(MotorPr9.step_delay));    
    gpio_bit_toggle(MT9_STEP_PORT,MT9_STEP_PIN);   
    return 0;
}
/*
比较中断处理函数_Mt10*/
signed char TIM13_Interrupt_Mt10(void)
{
    speed_decision(Motor10,&MotorPr10);
    timer_autoreload_value_config(TIMER13,0xffff&(MotorPr10.step_delay));    
    gpio_bit_toggle(MT10_STEP_PORT,MT10_STEP_PIN);   
    return 0;
}

/*比较中断处理函数_Mt11 and 12*/

signed char TIM7_Interrupt_Mt11_Mt12(void)
{  
    uint16_t val1,val2;    
    if(timer_interrupt_flag_get(TIMER7,TIMER_INT_FLAG_CH2))
    {
        timer_interrupt_flag_clear(TIMER7,TIMER_INT_FLAG_CH2); 
        val1=timer_counter_read(TIMER7);
        timer_channel_output_pulse_value_config(TIMER7,TIMER_CH_2,0xffff&(MotorPr11.step_delay+val1));        
        speed_decision(Motor11,&MotorPr11); 
    }
    if(timer_interrupt_flag_get(TIMER7,TIMER_INT_FLAG_CH3))
    {
        timer_interrupt_flag_clear(TIMER7,TIMER_INT_FLAG_CH3);  
        val2=timer_counter_read(TIMER7);
        timer_channel_output_pulse_value_config(TIMER7,TIMER_CH_3,0xffff&(MotorPr12.step_delay+val2));        
        speed_decision(Motor12,&MotorPr12);
    }
    return 0;
}
