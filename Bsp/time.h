#ifndef TIME_H
#define TIME_H


#define  PWM_MAXVAL                  4999                        //PWM占空比最大值
#define  CURRENT_REFERENCE           3000                        //最小电流启动基准

//电机电流
#define MOTORCUR1_Port  GPIOA
#define MOTORCUR2_Port  GPIOA
#define MOTORCUR3_Port  GPIOA
#define MOTORCUR4_Port  GPIOA

#define MOTORCUR5_Port  GPIOE
#define MOTORCUR6_Port  GPIOE
#define MOTORCUR7_Port  GPIOE
#define MOTORCUR8_Port  GPIOE

#define MOTORCUR9_Port   GPIOD
#define MOTORCUR10_Port  GPIOD
#define MOTORCUR11_Port  GPIOD
#define MOTORCUR12_Port  GPIOD

//pin
#define MOTORCUR1_Pin 	GPIO_PIN_0
#define MOTORCUR2_Pin 	GPIO_PIN_1
#define MOTORCUR3_Pin 	GPIO_PIN_2
#define MOTORCUR4_Pin 	GPIO_PIN_3

#define MOTORCUR5_Pin 	GPIO_PIN_9
#define MOTORCUR6_Pin 	GPIO_PIN_11
#define MOTORCUR7_Pin 	GPIO_PIN_13
#define MOTORCUR8_Pin 	GPIO_PIN_14

#define MOTORCUR9_Pin 	GPIO_PIN_12
#define MOTORCUR10_Pin 	GPIO_PIN_13
#define MOTORCUR11_Pin 	GPIO_PIN_14
#define MOTORCUR12_Pin 	GPIO_PIN_15


#define  MT1_STEP_PORT  GPIOB
#define  MT1_STEP_PIN   GPIO_PIN_0
#define  MT2_STEP_PORT  GPIOB
#define  MT2_STEP_PIN   GPIO_PIN_1
#define  MT3_STEP_PORT  GPIOE
#define  MT3_STEP_PIN   GPIO_PIN_7
#define  MT4_STEP_PORT  GPIOE
#define  MT4_STEP_PIN   GPIO_PIN_8


#define  MT5_STEP_PORT  GPIOD
#define  MT5_STEP_PIN   GPIO_PIN_8
#define  MT6_STEP_PORT  GPIOD
#define  MT6_STEP_PIN   GPIO_PIN_9
#define  MT7_STEP_PORT  GPIOD
#define  MT7_STEP_PIN   GPIO_PIN_10
#define  MT8_STEP_PORT  GPIOD
#define  MT8_STEP_PIN   GPIO_PIN_11

#define  MT9_STEP_PORT   GPIOC
#define  MT9_STEP_PIN    GPIO_PIN_6
#define  MT10_STEP_PORT  GPIOC
#define  MT10_STEP_PIN   GPIO_PIN_7
#define  MT11_STEP_PORT  GPIOC
#define  MT11_STEP_PIN   GPIO_PIN_8
#define  MT12_STEP_PORT  GPIOC
#define  MT12_STEP_PIN   GPIO_PIN_9

void Timer4_PWM1_Config(void);
void Timer0_PWM2_Config(void);
void Timer3_PWM3_Config(void);

void Timer2_Step1_Config(void);
void Timer5_Step2_Config(void);
void Timer6_Step3_Config(void);
void Timer1_Step4_Config(void);

void Timer8_Step5_Config(void);
void Timer9_Step6_Config(void);
void Timer10_Step7_Config(void);
void Timer11_Step8_Config(void);

void Timer12_Step9_Config(void);
void Timer13_Step10_Config(void);
void Timer7_Step11And12_config(void);

#endif

















