#include "morotstep.h"
#include "morot.h"
#include "Gpio.h"


volatile MotorRun Mt_Move_1={0};
volatile MotorRun Mt_Move_2={0};
volatile MotorRun Mt_Move_3={0};
volatile MotorRun Mt_Move_4={0};

volatile MotorRun Mt_Move_5={0};
volatile MotorRun Mt_Move_6={0};
volatile MotorRun Mt_Move_7={0};
volatile MotorRun Mt_Move_8={0};

volatile MotorRun Mt_Move_9={0};
volatile MotorRun Mt_Move_10={0};
volatile MotorRun Mt_Move_11={0};
volatile MotorRun Mt_Move_12={0};
/*
回零计时
*/
void Motor_Home_CountTime(void)
{

    Mt_Move_1.HomeTimeOut++;
    Mt_Move_2.HomeTimeOut++;
    Mt_Move_3.HomeTimeOut++;
    Mt_Move_4.HomeTimeOut++;
    Mt_Move_5.HomeTimeOut++;
    Mt_Move_6.HomeTimeOut++;
    Mt_Move_7.HomeTimeOut++;
    Mt_Move_8.HomeTimeOut++;
    Mt_Move_9.HomeTimeOut++;
    Mt_Move_10.HomeTimeOut++;    
    Mt_Move_11.HomeTimeOut++;
    Mt_Move_12.HomeTimeOut++;      
}

/*
电机运行状态赋值
num:电机编号（1-8）0:全部
flag:标志
*/

void  SetRuningFlag(uint8_t num,uint8_t flag)
{
    volatile  MotorRun *Mflag[13]={NULL,&Mt_Move_1,&Mt_Move_2,&Mt_Move_3,&Mt_Move_4,\
                                        &Mt_Move_5,&Mt_Move_6,&Mt_Move_7,&Mt_Move_8,\
                                        &Mt_Move_9,&Mt_Move_10,&Mt_Move_11,&Mt_Move_12    
                                          };                                                                     
    if(num!=0)
    {
        Mflag[num]->MotorSta=flag;
    }
    else
    {
        for(int i=1;i<=12;i++)
        {
           Mflag[i]->MotorSta=flag;         
        }
    }
}
/*
电机初始化
*/
uint32_t runspeed=100*5*10;
uint32_t restspeed=100*10*5;
uint16_t runcurrent=1000;   
int32_t pos1=200;
int32_t pos2=2600;
int16_t Moffset=-45;
void Motor_12B_Init(void)
{
    volatile MotorRun * mtp[13]={NULL,&Mt_Move_1,&Mt_Move_2,&Mt_Move_3,&Mt_Move_4,\
                                        &Mt_Move_5,&Mt_Move_6,&Mt_Move_7,&Mt_Move_8,\
                                        &Mt_Move_9,&Mt_Move_10,&Mt_Move_11,&Mt_Move_12    
                                };                                     
    for(int i=1;i<=12;i++)                                       
    {
        mtp[i]->RunSpeed=runspeed;
        mtp[i]->RestSpeed=restspeed;
        mtp[i]->RunCurrent=runcurrent; 
        mtp[i]->HomeOffset=Moffset;
        mtp[i]->RestPos=800*2;
        mtp[i]->H_accel=10*10*100;
        mtp[i]->H_decel=10*10*90;
        mtp[i]->R_accel=10*10*20;
        mtp[i]->R_decel=10*10*20;        
    }    
}  

/*
检测电机停止状态设置锁定电流
*/
void Motor_ClockCurrentSet_loop(void)
{

    volatile speedRampData *MtClk[13]={NULL,&MotorPr1,&MotorPr2,&MotorPr3,&MotorPr4,\
                                            &MotorPr5,&MotorPr6,&MotorPr7,&MotorPr8,\
                                            &MotorPr9,&MotorPr10,&MotorPr11,&MotorPr12 
                                       };  
    volatile MotorRun * MtCu[13]={NULL,&Mt_Move_1,&Mt_Move_2,&Mt_Move_3,&Mt_Move_4,\
                                        &Mt_Move_5,&Mt_Move_6,&Mt_Move_7,&Mt_Move_8,\
                                        &Mt_Move_9,&Mt_Move_10,&Mt_Move_11,&Mt_Move_12    
                                 };
    for(int i=1;i<=12;i++)
    {
        if(MtClk[i]->MotorState ==0)
        {
            Motor_Current_Set(i,i,(MtCu[i]->RunCurrent/2)+200);
        }
    }   
}   


/*
电机复位找零点
starnum:  电机开始编号
endnum:   电机结束编号
speed  回零速度
offset 偏移量
*/

signed char MotorRest(uint8_t starnum,uint8_t endnum,uint16_t speed,int32_t offset)
{
    uint8_t mtsta_R[13]={0,INPUT_1_STATE(),INPUT_2_STATE(),INPUT_3_STATE(),INPUT_4_STATE(),\
                         INPUT_5_STATE(),INPUT_6_STATE(),INPUT_7_STATE(),INPUT_8_STATE(),\
                         INPUT_9_STATE(),INPUT_10_STATE(),INPUT_11_STATE(),INPUT_12_STATE()
                      };
    volatile  MotorRun *Home_R[13]={NULL,&Mt_Move_1,&Mt_Move_2,&Mt_Move_3,&Mt_Move_4,\
                                       &Mt_Move_5,&Mt_Move_6,&Mt_Move_7,&Mt_Move_8,\
                                       &Mt_Move_9,&Mt_Move_10,&Mt_Move_11,&Mt_Move_12    
                                          };
    
    if((starnum==0||endnum==0)||(starnum>12||endnum>12))
        return -1;       
    for(char num=starnum;num<=endnum;num++)
    {
        if(!mtsta_R[num]&&offset==0)
        {
            SetRuningFlag(num,HomeEnd);
            continue;
        }
        else if(!mtsta_R[num]&&offset!=0)
        {
            Home_R[num]->HomeOffset=offset;
            Home_R[num]->HomeSta=2;          
            continue;            
        }
        if(Home_R[num]->HomeSta==0)
        {
            Home_R[num]->HomeTimeOut=0;            
            Home_R[num]->HomeSta=1;  
        }
        if(offset !=0)
        {
            Home_R[num]->HomeOffset=offset;
            Home_R[num]->HomeSta=2;
        } 

        stepper_move_T(num,num,1,Home_R[num]->RestPos,Home_R[num]->H_accel,Home_R[num]->H_decel,speed);                 
    }
    return 0;
}





/*
电机回零任务
*/
void Motor_HomeZero_Task_Loop(void)
{
    
    uint8_t mtsta[13]={0,INPUT_1_STATE(),INPUT_2_STATE(),INPUT_3_STATE(),INPUT_4_STATE(),\
                         INPUT_5_STATE(),INPUT_6_STATE(),INPUT_7_STATE(),INPUT_8_STATE(),\
                         INPUT_9_STATE(),INPUT_10_STATE(),INPUT_11_STATE(),INPUT_12_STATE()
                      };
    volatile  MotorRun *Home[13]={NULL,&Mt_Move_1,&Mt_Move_2,&Mt_Move_3,&Mt_Move_4,\
                                       &Mt_Move_5,&Mt_Move_6,&Mt_Move_7,&Mt_Move_8,\
                                       &Mt_Move_9,&Mt_Move_10,&Mt_Move_11,&Mt_Move_12    
                                          };
    volatile speedRampData *Mtp[13]={NULL,&MotorPr1,&MotorPr2,&MotorPr3,&MotorPr4,\
                                          &MotorPr5,&MotorPr6,&MotorPr7,&MotorPr8,\
                                          &MotorPr9,&MotorPr10,&MotorPr11,&MotorPr12 
                                     };  
    uint32_t speed=1000*2;
    uint8_t  time=50;
    
    for(int num=1;num<=12;num++)
    {
        if(Home[num]->HomeSta==1&&!mtsta[num])
        {   
            Motor_Stop_Set(num,num); 
            Home[num]->HomeSta=0;
            Mtp[num]->MotEncoder=0;
            SetRuningFlag(num,HomeEnd); 
       
        }
         //走偏移量
        else if(Home[num]->HomeSta==2&&!mtsta[num])
        {
            Motor_Stop_Set(num,num);            
            Mtp[num]->MotEncoder=0;            
            stepper_move_T(num,num,1,Home[num]->HomeOffset,Home[num]->H_accel,Home[num]->H_decel,Home[num]->RestSpeed); 
            Home[num]->HomeSta=3;            
        }
        //偏移量走完
        else if(Home[num]->HomeSta==3&&Mtp[num]->MotorState==0)
        {
             Home[num]->HomeSta=0; 
             SetRuningFlag(num,HomeEnd);             
        }            
        //回零超时
        else if(Home[num]->HomeSta==1&&mtsta[num]&&Home[num]->HomeTimeOut>10*10*time)
        {
           Home[num]->HomeTimeOut=0;      
           Motor_Stop_Set(num,num); 
           Home[num]->HomeSta=0;           
           SetRuningFlag(num,HomeEr); 
           
        }
    }

}







