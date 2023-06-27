
#ifndef __MOTORIOSTEP__H
#define	__MOTORIOSTEP__H

#include "gd32f4xx.h"

#define TIM1COUNTCYCLE    0.000001   //计数周期


enum MotorNum
{
    Motor1 =1,
    Motor2,
    Motor3,
    Motor4,
    Motor5,
    
    Motor6,
    Motor7,
    Motor8,
    Motor9,
    
    Motor10,
    Motor11,
    Motor12  
};





/*电机速度决策中的四个状态*/
#define STOP              0 // 停止状态
#define ACCEL             1 // 加速状态
#define DECEL             2 // 减速状态
#define RUN               3 // 匀速状态

/*频率相关参数*/

#define T1_FREQ           (1000000)     // 频率ft值


/*电机单圈参数*/
#define STEP_ANGLE	      1.8			//步进电机的步距角 单位：度
#define FSPR              (200)         //步进电机的一圈所需脉冲数

#define MICRO_STEP        4          	      //细分器细分数 
#define SPR               (FSPR*MICRO_STEP)   //细分后一圈所需脉冲数

/*数学常数,用于简化计算*/

#define ALPHA             ((float)(2*3.14159/SPR))       // α= 2*pi/spr
#define A_T_x10           ((float)(10*ALPHA*T1_FREQ))
#define T1_FREQ_148       ((float)((T1_FREQ*0.676)/10)) // 0.69为误差修正值(计算过程，文档中有写)
#define A_SQ              ((float)(2*100000*ALPHA)) 
#define A_x200            ((float)(200*ALPHA))

/*梯形加减速相关变量*/
typedef struct 
{
    //定时器使用翻转模式，需要进入两次中断才输出一个完整脉冲
	uint8_t i; 
    
    uint8_t MotorState;                
	/*当前电机状态*/
	uint8_t  run_state ; 
	/*旋转方向*/
	uint8_t  dir ;    
	/*脉冲间隔*/
	int  step_delay;  
	/*减速位置*/
	int  decel_start; 
	/*减速步数*/
	int  decel_val;   
	/*最小间隔*/
	int  min_delay;   
	/*加速步数*/
	int  accel_count; 
	// 保存新（下）一个延时周期
	uint16_t new_step_delay;
	// 加速过程中最后一次延时（脉冲周期）.
	uint16_t last_accel_delay;
	// 总移动步数计数器
	 uint32_t step_count;
     //余数补偿
	 int32_t  rest;
     //软件编码器
     int32_t  MotEncoder;
   
}speedRampData;


extern speedRampData MotorPr1,MotorPr2,MotorPr3,MotorPr4;
extern speedRampData MotorPr5,MotorPr6,MotorPr7,MotorPr8;
extern speedRampData MotorPr9,MotorPr10,MotorPr11,MotorPr12;

signed char TIM2_Interrupt_Mt1(void);
signed char TIM5_Interrupt_Mt2(void);
signed char TIM6_Interrupt_Mt3(void);
signed char TIM1_Interrupt_Mt4(void);

signed char TIM8_Interrupt_Mt5(void);
signed char TIM9_Interrupt_Mt6(void);
signed char TIM10_Interrupt_Mt7(void);
signed char TIM11_Interrupt_Mt8(void);

signed char TIM12_Interrupt_Mt9(void);
signed char TIM13_Interrupt_Mt10(void);
signed char TIM7_Interrupt_Mt11_Mt12(void);

#endif








