#include "gd32f4xx.h"
#include "Gpio.h"
#include "systick.h"
#include "morot.h"
#include "morotstep.h"
#include "time.h"


/*
电机方向设置
Mnum:电机编号
Dr： 设置反向
*/
signed char Motor_Dir_Set(unsigned char Munm,char Dr)
{
    uint32_t prot[13]= {0,MOTORDIR1_Port,MOTORDIR2_Port,MOTORDIR3_Port,\
                          MOTORDIR4_Port,MOTORDIR5_Port,MOTORDIR6_Port,\
                          MOTORDIR7_Port,MOTORDIR8_Port,MOTORDIR9_Port,\
                          MOTORDIR10_Port,MOTORDIR11_Port,MOTORDIR12_Port       
                        };
    uint32_t Pin[13]={0,MOTORDIR1_Pin,MOTORDIR2_Pin,MOTORDIR3_Pin,\
                        MOTORDIR4_Pin,MOTORDIR5_Pin,MOTORDIR6_Pin,\
                        MOTORDIR7_Pin,MOTORDIR8_Pin,MOTORDIR9_Pin,\
                        MOTORDIR10_Pin,MOTORDIR11_Pin,MOTORDIR12_Pin       
                     };     
    if((Munm>12||Munm==0)||(Dr!=1&&Dr!=0))
    {
        return -1;
    }
    if(Dr)
    {
         gpio_bit_write(prot[Munm],Pin[Munm] ,RESET);
    }
    else        
    {
         gpio_bit_write(prot[Munm],Pin[Munm] ,SET);
    }       
    return 1;
}

/*
电机方向设置批量
start:电机起始编号西安
end:  电机结束编号
Dr： 设置反向
*/
signed char Motor_DirS_Set(unsigned char start,uint8_t end, char Dr)
{
    uint32_t prot[13]= {0,MOTORDIR1_Port,MOTORDIR2_Port,MOTORDIR3_Port,\
                          MOTORDIR4_Port,MOTORDIR5_Port,MOTORDIR6_Port,\
                          MOTORDIR7_Port,MOTORDIR8_Port,MOTORDIR9_Port,\
                          MOTORDIR10_Port,MOTORDIR11_Port,MOTORDIR12_Port       
                       };
    uint32_t Pin[13]={0,MOTORDIR1_Pin,MOTORDIR2_Pin,MOTORDIR3_Pin,\
                        MOTORDIR4_Pin,MOTORDIR5_Pin,MOTORDIR6_Pin,\
                        MOTORDIR7_Pin,MOTORDIR8_Pin,MOTORDIR9_Pin,\
                        MOTORDIR10_Pin,MOTORDIR11_Pin,MOTORDIR12_Pin       
                     };     
    if((start>0&&start<=12)&&(end>0&&end<=12))
    {
        if(Dr)
        {
            for(char i=start;i<=end;i++)
              gpio_bit_write(prot[i],Pin[i],RESET);
        }
        else        
        {
            for(char i=start;i<=end;i++) 
              gpio_bit_write(prot[i],Pin[i],SET);
        }
    }    
    return 1;
}

/*
电机使能设置
Gr:电机组号（1-3） 0：全部
Enb：  使/失能
*/
signed char Motor_Enbl_Set(unsigned char Grp, char Enb)
{   
	switch (Grp)
	{
		case 1:
            gpio_bit_write(MOTOR_EN1_Port,MOTOR_EN1_Pin,(bit_status)Enb);
			break;
		case 2:
            gpio_bit_write(MOTOR_EN2_Port,MOTOR_EN2_Pin,(bit_status)Enb);
			break;
		case 3:
            gpio_bit_write(MOTOR_EN3_Port,MOTOR_EN3_Pin,(bit_status)Enb);        
		    break;
		case 0:
            gpio_bit_write(MOTOR_EN1_Port,MOTOR_EN1_Pin,(bit_status)Enb);
            gpio_bit_write(MOTOR_EN2_Port,MOTOR_EN2_Pin,(bit_status)Enb);           
            gpio_bit_write(MOTOR_EN3_Port,MOTOR_EN3_Pin,(bit_status)Enb);   
			break;		
		default:
				break;		
	}   
    return 1;
}
/*
电机微步设置
Gr:电机组号（1-3） 0：全部
step:0:全步
     1：1/2步
     2：1/4步
     3：1/8步   
*/
signed char Motor_Microstep_Set(unsigned char Grp, unsigned char step)
{    
    bit_status MS1,MS2;
    if(step>3)
        return -1;
    
    MS1=(step&0x01)?SET:RESET;    
    MS2=(step&0x02)?SET:RESET;       
	switch (Grp)
	{
		case 1:
            gpio_bit_write(MOTOR_MS1_1_Port,MOTOR_MS1_1_Pin,MS1);
            gpio_bit_write(MOTOR_MS2_1_Port,MOTOR_MS2_1_Pin,MS2);
			break;
		case 2:
            gpio_bit_write(MOTOR_MS1_2_Port,MOTOR_MS1_2_Pin,MS1);
            gpio_bit_write(MOTOR_MS2_2_Port,MOTOR_MS2_2_Pin,MS2);
			break;
		case 3:
            gpio_bit_write(MOTOR_MS1_3_Port,MOTOR_MS1_3_Pin,MS1);
            gpio_bit_write(MOTOR_MS2_3_Port,MOTOR_MS2_3_Pin,MS2);       
		    break;
		case 0:
            gpio_bit_write(MOTOR_MS1_1_Port,MOTOR_MS1_1_Pin,MS1);
            gpio_bit_write(MOTOR_MS2_1_Port,MOTOR_MS2_1_Pin,MS2);
            gpio_bit_write(MOTOR_MS1_2_Port,MOTOR_MS1_2_Pin,MS1);
            gpio_bit_write(MOTOR_MS2_2_Port,MOTOR_MS2_2_Pin,MS2);
            gpio_bit_write(MOTOR_MS1_3_Port,MOTOR_MS1_3_Pin,MS1);
            gpio_bit_write(MOTOR_MS2_3_Port,MOTOR_MS2_3_Pin,MS2);  
			break;		
		default:
				break;		
	}   
    return 1;
}



/*
电机IC故障状态获取
Gr:电机组号（1-3） 0：全部
Enb：  使/失能
*/
signed char Motor_Fault_Get(void)
{
    uint8_t fault=0xf8;
    
   fault|=gpio_input_bit_get(MOTOR_FAULT1_Port,MOTORFAULT1_Pin);
   fault|=gpio_input_bit_get(MOTOR_FAULT1_Port,MOTORFAULT1_Pin)<<1;
   fault|=gpio_input_bit_get(MOTOR_FAULT1_Port,MOTORFAULT1_Pin)<<2;  
   myPrint("fault %x\n",fault);    
   return fault;
}


/*
获取传感器状态
start:起始编号
end:  结束编号
returnval:状态值（0-11）bit每一位代表一个sensor 
*/

uint16_t GetSensorSta(void)
{
    uint16_t SensorVal=0;
 
    SensorVal|=gpio_input_bit_get(MOTOR_IN1_PORT,MOTOR_IN1_PIN);
    SensorVal|=gpio_input_bit_get(MOTOR_IN2_PORT,MOTOR_IN2_PIN)<<1;
    SensorVal|=gpio_input_bit_get(MOTOR_IN3_PORT,MOTOR_IN3_PIN)<<2;
    SensorVal|=gpio_input_bit_get(MOTOR_IN4_PORT,MOTOR_IN4_PIN)<<3;
    SensorVal|=gpio_input_bit_get(MOTOR_IN5_PORT,MOTOR_IN5_PIN)<<4;
    SensorVal|=gpio_input_bit_get(MOTOR_IN6_PORT,MOTOR_IN6_PIN)<<5;
    SensorVal|=gpio_input_bit_get(MOTOR_IN7_PORT,MOTOR_IN7_PIN)<<6;
    SensorVal|=gpio_input_bit_get(MOTOR_IN8_PORT,MOTOR_IN8_PIN)<<7;
    SensorVal|=gpio_input_bit_get(MOTOR_IN9_PORT,MOTOR_IN9_PIN)<<8;
    SensorVal|=gpio_input_bit_get(MOTOR_IN10_PORT,MOTOR_IN10_PIN)<<9;
    SensorVal|=gpio_input_bit_get(MOTOR_IN11_PORT,MOTOR_IN11_PIN)<<10;
    SensorVal|=gpio_input_bit_get(MOTOR_IN12_PORT,MOTOR_IN12_PIN)<<11;    
//    myPrint("SensorVal %x\n",SensorVal);
    return SensorVal;
}
/*
电机电流设置
start:起始编号(1-12)
end:  结束编号(1-12)
current:电流值(1-2000ma)
*/
signed char Motor_Current_Set(unsigned char start,unsigned char end,unsigned short current)
{
    uint16_t  CurrentVal=0;
    uint16_t  CurrentCorrection=227;
    uint32_t  Time[4]={0,TIMER4,TIMER0,TIMER3};
    uint16_t  CHNum[4]={TIMER_CH_0,TIMER_CH_1,TIMER_CH_2,TIMER_CH_3};  
    
    if((start==0||end==0)||(start>12||end>12)||current>2000)
    {
        return -1;
    }
    
    CurrentVal=CURRENT_REFERENCE+(current+CurrentCorrection);
    
    for(char i=start;i<=end;i++)
        timer_channel_output_pulse_value_config(Time[((i-1)/4)+1],CHNum[(i-1)%4],CurrentVal);
    return 0;
}

/*
电机启动
start:起始编号(1-12)
end:  结束编号(1-12)
*/
signed char Motor_Star_Set(unsigned char start,unsigned char end)
{
    uint32_t  handle[13]={0,TIMER2,TIMER5,TIMER6,TIMER1,\
                            TIMER8,TIMER9,TIMER10,TIMER11,\
                            TIMER12,TIMER13,TIMER7,TIMER7
                          };
    uint32_t source[13]={0,TIMER_INT_UP,TIMER_INT_UP,TIMER_INT_UP,TIMER_INT_UP,\
                           TIMER_INT_UP,TIMER_INT_UP,TIMER_INT_UP,TIMER_INT_UP,\
                           TIMER_INT_UP,TIMER_INT_UP,TIMER_INT_CH2,TIMER_INT_CH3
                        };
    speedRampData *MtSt_S[13]={NULL,&MotorPr1,&MotorPr2,&MotorPr3,&MotorPr4,\
                                  &MotorPr5,&MotorPr6,&MotorPr7,&MotorPr8,\
                                  &MotorPr9,&MotorPr10,&MotorPr11,&MotorPr12 
                            };
    if((start==0||end==0)||(start>12||end>12))
    {
        return -1;
    }
    for(char i=start;i<=end;i++)
    {
       timer_interrupt_enable(handle[i],source[i]);
       timer_enable(handle[i]);
       MtSt_S[i]->MotorState=1; 
       /*此处为了规避芯片缺陷
         比较输出状态停止后仍然输出低频翻转造成的抖动
         启动时恢复状态管脚正常状态*/ 
       if(i==11)
       {           
         gpio_output_options_set(MT11_STEP_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT11_STEP_PIN);
         timer_channel_output_pulse_value_config(handle[i],source[i],1);
       }      
      else if(i==12) 
      {    
         gpio_output_options_set(MT12_STEP_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT12_STEP_PIN);
         timer_channel_output_pulse_value_config(handle[i],source[i],1); 
      }
      else
         timer_autoreload_value_config(handle[i],1);  
    }
    return 0;
}

/*
电机停止
start:起始编号(1-12)
end:  结束编号(1-12)
*/
signed char Motor_Stop_Set(unsigned char start,unsigned char end)
{
    uint32_t  handle[13]={0,TIMER2,TIMER5,TIMER6,TIMER1,\
                            TIMER8,TIMER9,TIMER10,TIMER11,\
                            TIMER12,TIMER13,TIMER7,TIMER7
                         };
    uint32_t source[13]={0,TIMER_INT_UP,TIMER_INT_UP,TIMER_INT_UP,TIMER_INT_UP,\
                           TIMER_INT_UP,TIMER_INT_UP,TIMER_INT_UP,TIMER_INT_UP,\
                           TIMER_INT_UP,TIMER_INT_UP,TIMER_INT_CH2,TIMER_INT_CH3
                        };
    speedRampData *MtSt_P[13]={NULL,&MotorPr1,&MotorPr2,&MotorPr3,&MotorPr4,\
                                  &MotorPr5,&MotorPr6,&MotorPr7,&MotorPr8,\
                                  &MotorPr9,&MotorPr10,&MotorPr11,&MotorPr12 
                            };  
    
    if((start==0||end==0)||(start>12||end>12))
    {
        return -1;
    }
    for(char i=start;i<=end;i++)
    {
       timer_interrupt_disable(handle[i],source[i]);
       timer_interrupt_flag_clear(handle[i],source[i]);
       MtSt_P[i]->MotorState=0;
       MtSt_P[i]->rest=0;
       MtSt_P[i]->step_count=0;        
       
        /*此处为了规避芯片缺陷
         比较输出状态停止后仍然输出低频翻转造成的抖动
         停止时强制变换管脚模式*/  
       if(i==11)
         gpio_output_options_set(MT11_STEP_PORT,GPIO_OTYPE_OD,GPIO_OSPEED_50MHZ,MT11_STEP_PIN);
       else if(i==12) 
         gpio_output_options_set(MT12_STEP_PORT,GPIO_OTYPE_OD,GPIO_OSPEED_50MHZ,MT12_STEP_PIN);
       else
         timer_autoreload_value_config(handle[i],0);   
    }
    return 0;
}


void TestFunction(void) 
{
      Motor_Enbl_Set(0,MOROT_UPEN);   
//    Motor_Enbl_Set(2,MOROT_UPEN); 
//    Motor_Enbl_Set(3,MOROT_UPEN);     
//    GetSensorSta();
//    delay_1ms(600);    
//    Motor_Fault_Get();
//    delay_1ms(600);
      Motor_Microstep_Set(0,2);
//      Motor_Microstep_Set(2,2);
//      Motor_Microstep_Set(3,2);    
      Motor_Current_Set(1,12,550);
//      Motor_Star_Set(1,4);
//      delay_1ms(2*100*10);
//      Motor_Stop_Set(11,11);


//    delay_1ms(100);
}















