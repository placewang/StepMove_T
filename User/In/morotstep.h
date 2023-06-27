
#ifndef __MOTORIOSTEP__H
#define	__MOTORIOSTEP__H

#include "gd32f4xx.h"

#define TIM1COUNTCYCLE    0.000001   //��������


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





/*����ٶȾ����е��ĸ�״̬*/
#define STOP              0 // ֹͣ״̬
#define ACCEL             1 // ����״̬
#define DECEL             2 // ����״̬
#define RUN               3 // ����״̬

/*Ƶ����ز���*/

#define T1_FREQ           (1000000)     // Ƶ��ftֵ


/*�����Ȧ����*/
#define STEP_ANGLE	      1.8			//��������Ĳ���� ��λ����
#define FSPR              (200)         //���������һȦ����������

#define MICRO_STEP        4          	      //ϸ����ϸ���� 
#define SPR               (FSPR*MICRO_STEP)   //ϸ�ֺ�һȦ����������

/*��ѧ����,���ڼ򻯼���*/

#define ALPHA             ((float)(2*3.14159/SPR))       // ��= 2*pi/spr
#define A_T_x10           ((float)(10*ALPHA*T1_FREQ))
#define T1_FREQ_148       ((float)((T1_FREQ*0.676)/10)) // 0.69Ϊ�������ֵ(������̣��ĵ�����д)
#define A_SQ              ((float)(2*100000*ALPHA)) 
#define A_x200            ((float)(200*ALPHA))

/*���μӼ�����ر���*/
typedef struct 
{
    //��ʱ��ʹ�÷�תģʽ����Ҫ���������жϲ����һ����������
	uint8_t i; 
    
    uint8_t MotorState;                
	/*��ǰ���״̬*/
	uint8_t  run_state ; 
	/*��ת����*/
	uint8_t  dir ;    
	/*������*/
	int  step_delay;  
	/*����λ��*/
	int  decel_start; 
	/*���ٲ���*/
	int  decel_val;   
	/*��С���*/
	int  min_delay;   
	/*���ٲ���*/
	int  accel_count; 
	// �����£��£�һ����ʱ����
	uint16_t new_step_delay;
	// ���ٹ��������һ����ʱ���������ڣ�.
	uint16_t last_accel_delay;
	// ���ƶ�����������
	 uint32_t step_count;
     //��������
	 int32_t  rest;
     //���������
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








