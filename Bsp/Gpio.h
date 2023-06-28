#ifndef GPIO_H
#define GPIO_H

//传感器
#define MOTOR_IN1_PIN   GPIO_PIN_7  
#define MOTOR_IN2_PIN   GPIO_PIN_6  
#define MOTOR_IN3_PIN   GPIO_PIN_5  
#define MOTOR_IN4_PIN   GPIO_PIN_4  
#define MOTOR_IN5_PIN   GPIO_PIN_3

#define MOTOR_IN6_PIN   GPIO_PIN_7  
#define MOTOR_IN7_PIN   GPIO_PIN_6  
#define MOTOR_IN8_PIN   GPIO_PIN_5  
#define MOTOR_IN9_PIN   GPIO_PIN_4  
#define MOTOR_IN10_PIN  GPIO_PIN_3  
#define MOTOR_IN11_PIN  GPIO_PIN_2  
#define MOTOR_IN12_PIN  GPIO_PIN_1  

//电机方向
#define MOTORDIR1_Pin 	GPIO_PIN_6
#define MOTORDIR2_Pin 	GPIO_PIN_7
#define MOTORDIR3_Pin 	GPIO_PIN_4
#define MOTORDIR4_Pin 	GPIO_PIN_5

#define MOTORDIR5_Pin 	GPIO_PIN_12
#define MOTORDIR6_Pin 	GPIO_PIN_13
#define MOTORDIR7_Pin 	GPIO_PIN_14
#define MOTORDIR8_Pin 	GPIO_PIN_15

#define MOTORDIR9_Pin 	GPIO_PIN_15
#define MOTORDIR10_Pin 	GPIO_PIN_10
#define MOTORDIR11_Pin 	GPIO_PIN_11
#define MOTORDIR12_Pin 	GPIO_PIN_12

//电机故障
#define MOTORFAULT1_Pin 	GPIO_PIN_15
#define MOTORFAULT2_Pin 	GPIO_PIN_10
#define MOTORFAULT3_Pin 	GPIO_PIN_8

#define MOTOR_FAULT1_Port  GPIOE
#define MOTOR_FAULT2_Port  GPIOB
#define MOTOR_FAULT3_Port  GPIOA

//电机微步
#define MOTOR_MS1_1_Pin 	GPIO_PIN_5
#define MOTOR_MS2_1_Pin 	GPIO_PIN_6
#define MOTOR_MS1_2_Pin 	GPIO_PIN_3
#define MOTOR_MS2_2_Pin 	GPIO_PIN_4
#define MOTOR_MS1_3_Pin 	GPIO_PIN_0
#define MOTOR_MS2_3_Pin 	GPIO_PIN_1

#define MOTOR_MS1_1_Port  GPIOE
#define MOTOR_MS2_1_Port  GPIOE
#define MOTOR_MS1_2_Port  GPIOE
#define MOTOR_MS2_2_Port  GPIOE
#define MOTOR_MS1_3_Port  GPIOE
#define MOTOR_MS2_3_Port  GPIOE

//电机使能
#define MOTOR_EN1_Pin 	GPIO_PIN_10
#define MOTOR_EN2_Pin 	GPIO_PIN_12
#define MOTOR_EN3_Pin 	GPIO_PIN_0

#define MOTOR_EN1_Port  GPIOE
#define MOTOR_EN2_Port  GPIOE
#define MOTOR_EN3_Port  GPIOD

//传感器
#define MOTOR_IN1_PORT  GPIOB 
#define MOTOR_IN2_PORT  GPIOB 
#define MOTOR_IN3_PORT  GPIOB 
#define MOTOR_IN4_PORT  GPIOB 
#define MOTOR_IN5_PORT  GPIOB 

#define MOTOR_IN6_PORT  GPIOD 
#define MOTOR_IN7_PORT  GPIOD 
#define MOTOR_IN8_PORT  GPIOD 
#define MOTOR_IN9_PORT  GPIOD 
#define MOTOR_IN10_PORT GPIOD 
#define MOTOR_IN11_PORT GPIOD 
#define MOTOR_IN12_PORT GPIOD 

//电机方向
#define MOTORDIR1_Port  GPIOA
#define MOTORDIR2_Port  GPIOA
#define MOTORDIR3_Port  GPIOC
#define MOTORDIR4_Port  GPIOC

#define MOTORDIR5_Port  GPIOB
#define MOTORDIR6_Port  GPIOB
#define MOTORDIR7_Port  GPIOB
#define MOTORDIR8_Port  GPIOB

#define MOTORDIR9_Port   GPIOA
#define MOTORDIR10_Port  GPIOC
#define MOTORDIR11_Port  GPIOC
#define MOTORDIR12_Port  GPIOC




#define INPUT_1_STATE()      gpio_input_bit_get(MOTOR_IN1_PORT,MOTOR_IN1_PIN)
#define INPUT_2_STATE()      gpio_input_bit_get(MOTOR_IN2_PORT,MOTOR_IN2_PIN)
#define INPUT_3_STATE()      gpio_input_bit_get(MOTOR_IN3_PORT,MOTOR_IN3_PIN)
#define INPUT_4_STATE()      gpio_input_bit_get(MOTOR_IN4_PORT,MOTOR_IN4_PIN)
#define INPUT_5_STATE()      gpio_input_bit_get(MOTOR_IN5_PORT,MOTOR_IN5_PIN)
#define INPUT_6_STATE()      gpio_input_bit_get(MOTOR_IN6_PORT,MOTOR_IN6_PIN)
#define INPUT_7_STATE()      gpio_input_bit_get(MOTOR_IN7_PORT,MOTOR_IN7_PIN)
#define INPUT_8_STATE()      gpio_input_bit_get(MOTOR_IN8_PORT,MOTOR_IN8_PIN)
#define INPUT_9_STATE()      gpio_input_bit_get(MOTOR_IN9_PORT,MOTOR_IN9_PIN)
#define INPUT_10_STATE()     gpio_input_bit_get(MOTOR_IN10_PORT,MOTOR_IN10_PIN)
#define INPUT_11_STATE()     gpio_input_bit_get(MOTOR_IN11_PORT,MOTOR_IN11_PIN)
#define INPUT_12_STATE()     gpio_input_bit_get(MOTOR_IN12_PORT,MOTOR_IN12_PIN)  



void gpio_init(void);
unsigned char GetDipSwitch_4bit(void);
void System_Led(unsigned short time);



#endif





