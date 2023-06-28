#include "gd32f4xx.h"
#include "Gpio.h"
#include "morotstep.h"
#include "morot.h"
#include "time.h"
#include "math.h"


speedRampData MotorPr1,MotorPr2,MotorPr3,MotorPr4;
speedRampData MotorPr5,MotorPr6,MotorPr7,MotorPr8;
speedRampData MotorPr9,MotorPr10,MotorPr11,MotorPr12;




/*! \brief �Ը����Ĳ����ƶ��������
 *  ͨ��������ٵ�����ٶȣ��Ը����Ĳ�����ʼ����
 *  ������ٶȺͼ��ٶȺ�С������������ƶ���������û�ﵽ����ٶȾ�Ҫ��ʼ����
 *  \param step   �ƶ��Ĳ��� (����Ϊ˳ʱ�룬����Ϊ��ʱ��).
 *  \param accel  ���ٶ�,���ȡֵΪ10��ʵ��ֵΪ10*0.1*rad/sec^2=1rad/sec^2
 *  \param decel  ���ٶ�,���ȡֵΪ10��ʵ��ֵΪ10*0.1*rad/sec^2=1rad/sec^2
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
                                   
    //�ﵽ����ٶ�ʱ�Ĳ���.
    unsigned int max_s_lim;
    //���뿪ʼ���ٵĲ���(�����û���ٵ�������ٶ�ʱ)��
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
        // ���ֻ�ƶ�һ��
        if((AbsoluteVal)==0)
        {
            // ֻ�ƶ�һ��
            MtPr[i]->accel_count = -1;
            // ����״̬
            MtPr[i]->run_state = DECEL;
            // ����ʱ
            MtPr[i]->step_delay = 1000;
            if(MtPr[i]->dir)
                MtPr[i]->MotEncoder--;
            else
                MtPr[i]->MotEncoder++;   
            // ���õ��Ϊ����״̬
            Motor_Star_Set(i,i);
        }	
        // ������Ϊ����ƶ�
        else if(AbsoluteVal != 0)
        {
            // ��������ٶȼ���, ����õ�min_delay���ڶ�ʱ���ļ�������ֵ��
            // min_delay = (alpha / tt)/ w
            MtPr[i]->min_delay = (int32_t)(A_T_x10/speed);

            // ͨ�������һ��(c0) �Ĳ�����ʱ���趨���ٶȣ�����accel��λΪ0.1rad/sec^2
            MtPr[i]->step_delay = (int32_t)((T1_FREQ_148 * sqrt(A_SQ / accel))/10);

            // ������ٲ�֮��ﵽ����ٶȵ�����
            // max_s_lim = speed^2 / (2*alpha*accel)
            max_s_lim = (uint32_t)(speed*speed/(A_x200*accel/10));
            // ����ﵽ����ٶ�С��0.5�������ǽ���������Ϊ0
            // ��ʵ�����Ǳ����ƶ�����һ�����ܴﵽ��Ҫ���ٶ�
            if(max_s_lim == 0)
            {
                    max_s_lim = 1;
            }
            // ������ٲ�֮�����Ǳ��뿪ʼ����
            // n1 = (n1+n2)decel / (accel + decel)
            accel_lim = (uint32_t)(AbsoluteVal*decel/(accel+decel));
            // ���Ǳ����������1�����ܲ��ܿ�ʼ����.
            if(accel_lim == 0)
            {
                accel_lim = 1;
            }
            // ʹ�������������ǿ��Լ������һ�ο�ʼ���ٵ�λ��
            //MtPr[i]->decel_valΪ����
            if(accel_lim <= max_s_lim)
            {
                MtPr[i]->decel_val = accel_lim - AbsoluteVal;
            }
            else{
                MtPr[i]->decel_val = -(max_s_lim*accel/decel);
            }
            // ��ֻʣ��һ�����Ǳ������
            if(MtPr[i]->decel_val == 0)
                MtPr[i]->decel_val = -1;
            // ���㿪ʼ����ʱ�Ĳ���
            MtPr[i]->decel_start = AbsoluteVal + MtPr[i]->decel_val;

            // �������ٶȺ��������ǾͲ���Ҫ���м����˶�
            if(MtPr[i]->step_delay <= MtPr[i]->min_delay)
            {
                MtPr[i]->step_delay = MtPr[i]->min_delay;
                MtPr[i]->run_state = RUN;
            }
            else
            {
                MtPr[i]->run_state = ACCEL;
            }
            // ��λ���ٶȼ���ֵ
            MtPr[i]->accel_count = 0;
            Motor_Star_Set(i,i);
        }
    }
    return 0;
}

/**
  * @brief  �ٶȾ���
	*	@note 	���ж���ʹ�ã�ÿ��һ���жϣ�����һ��
  * @retval ��
  */
void speed_decision(uint8_t Mnum,speedRampData *srd)
{
    srd->i++;             // ��ʱ���жϴ�������ֵ
    if(srd->i==2)         // 2�Σ�˵���Ѿ����һ����������
    {
        srd->i=0;         // ���㶨ʱ���жϴ�������ֵ
        switch(srd->run_state) 
        {
        /*�������ֹͣ״̬*/
        case STOP:
            // ���㲽��������
            srd->step_count = 0;  
            // ������ֵ
            srd->rest = 0;        
            Motor_Stop_Set(Mnum,Mnum);
            break;
        /*�����������״̬*/
        case ACCEL:
            if(srd->dir)
                srd->MotEncoder++;
            else
               srd->MotEncoder--;
            srd->step_count++;    
            srd->accel_count++;
            //������(��)һ����������(ʱ����)
            srd->new_step_delay = srd->step_delay - (((2 *srd->step_delay) + srd->rest)/(4 * srd->accel_count + 1));
            // �����������´μ��㲹���������������
            srd->rest = ((2 * srd->step_delay)+srd->rest)%(4 * srd->accel_count + 1);
            //����ǹ�Ӧ�ÿ�ʼ����
            if(srd->step_count >= srd->decel_start){
                srd->accel_count = srd->decel_val;
                srd->run_state = DECEL;
            }
            //����Ƿ񵽴�����������ٶ�
            else if(srd->new_step_delay <= srd->min_delay){
                srd->last_accel_delay = srd->new_step_delay;
                srd->new_step_delay = srd->min_delay;    
                srd->rest = 0;                          
                srd->run_state = RUN;
            }
            break;
        /*�����������ٶ�����״̬*/
        case RUN:
            if(srd->dir)
                srd->MotEncoder++;
            else
               srd->MotEncoder--;
            srd->step_count++; 
            srd->new_step_delay = srd->min_delay;
            //����Ƿ���Ҫ��ʼ����
            if(srd->step_count >= srd->decel_start) 
            {
                srd->accel_count = srd->decel_val;
                //�����һ�μ��ٵ���ʱ��Ϊ��ʼ���ٵ���ʱ
                srd->new_step_delay = srd->last_accel_delay;
                srd->run_state = DECEL;
            }
            break;
        /*�����������״̬*/
        case DECEL:
            if(srd->dir)
                srd->MotEncoder++;
            else
               srd->MotEncoder--;
        
            srd->step_count++; 
            srd->accel_count++;
            //������(��)һ����������(ʱ����)
            srd->new_step_delay = srd->step_delay - (((2 * srd->step_delay) +srd->rest)/(4 * srd->accel_count + 1)); 
            // �����������´μ��㲹���������������
            srd->rest = ((2 * srd->step_delay)+srd->rest)%(4 * srd->accel_count + 1);
            //����Ƿ�Ϊ���һ��
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
    /*�����һ�μ��ʱ��*/
    srd->step_delay = srd->new_step_delay;  
	}
}




/*�Ƚ��жϴ�����_Mt1*/
signed char TIM2_Interrupt_Mt1(void)
{
    speed_decision(Motor1,&MotorPr1);
    timer_autoreload_value_config(TIMER2,0xffff&(MotorPr1.step_delay));    
    gpio_bit_toggle(MT1_STEP_PORT,MT1_STEP_PIN);   
    return 0;
}
/*
�Ƚ��жϴ�����_Mt2*/
signed char TIM5_Interrupt_Mt2(void)
{
    speed_decision(Motor2,&MotorPr2);
    timer_autoreload_value_config(TIMER5,0xffff&(MotorPr2.step_delay));    
    gpio_bit_toggle(MT2_STEP_PORT,MT2_STEP_PIN);   
    return 0;
}
/*�Ƚ��жϴ�����_Mt3*/
signed char TIM6_Interrupt_Mt3(void)
{
    speed_decision(Motor3,&MotorPr3);
    timer_autoreload_value_config(TIMER6,0xffff&(MotorPr3.step_delay));    
    gpio_bit_toggle(MT3_STEP_PORT,MT3_STEP_PIN);   
    return 0;
}
/*�Ƚ��жϴ�����_Mt4*/

signed char TIM1_Interrupt_Mt4(void)
{       
    speed_decision(Motor4,&MotorPr4);
    timer_autoreload_value_config(TIMER1,0xffff&(MotorPr4.step_delay));
    gpio_bit_toggle(MT4_STEP_PORT,MT4_STEP_PIN);  
    return 0;
}



/*�Ƚ��жϴ�����_Mt5*/
signed char TIM8_Interrupt_Mt5(void)
{
    speed_decision(Motor5,&MotorPr5);
    timer_autoreload_value_config(TIMER8,0xffff&(MotorPr5.step_delay));    
    gpio_bit_toggle(MT5_STEP_PORT,MT5_STEP_PIN);   
    return 0;
}
/*
�Ƚ��жϴ�����_Mt6*/
signed char TIM9_Interrupt_Mt6(void)
{
    speed_decision(Motor6,&MotorPr6);
    timer_autoreload_value_config(TIMER9,0xffff&(MotorPr6.step_delay));    
    gpio_bit_toggle(MT6_STEP_PORT,MT6_STEP_PIN);   
    return 0;
}
/*�Ƚ��жϴ�����_Mt7*/
signed char TIM10_Interrupt_Mt7(void)
{
    speed_decision(Motor7,&MotorPr7);
    timer_autoreload_value_config(TIMER10,0xffff&(MotorPr7.step_delay));    
    gpio_bit_toggle(MT7_STEP_PORT,MT7_STEP_PIN);   
    return 0;
}
/*�Ƚ��жϴ�����_Mt8*/

signed char TIM11_Interrupt_Mt8(void)
{ 
    speed_decision(Motor8,&MotorPr8);
    timer_autoreload_value_config(TIMER11,0xffff&(MotorPr8.step_delay));    
    gpio_bit_toggle(MT8_STEP_PORT,MT8_STEP_PIN);   
    return 0;
}


/*�Ƚ��жϴ�����_Mt9*/
signed char TIM12_Interrupt_Mt9(void)
{
    speed_decision(Motor9,&MotorPr9);
    timer_autoreload_value_config(TIMER12,0xffff&(MotorPr9.step_delay));    
    gpio_bit_toggle(MT9_STEP_PORT,MT9_STEP_PIN);   
    return 0;
}
/*
�Ƚ��жϴ�����_Mt10*/
signed char TIM13_Interrupt_Mt10(void)
{
    speed_decision(Motor10,&MotorPr10);
    timer_autoreload_value_config(TIMER13,0xffff&(MotorPr10.step_delay));    
    gpio_bit_toggle(MT10_STEP_PORT,MT10_STEP_PIN);   
    return 0;
}

/*�Ƚ��жϴ�����_Mt11 and 12*/

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
