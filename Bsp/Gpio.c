#include "gd32f4xx.h"
#include "gd32f4xx_gpio.h"
#include "Gpio.h"

uint32_t LedTimeCount=0;                            //Led灯状态翻转计时


/*
传感器检测初始化
*/
void Sensor_12bitInit(void)
{

    /* enable the key clock */
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOD);    
    rcu_periph_clock_enable(RCU_SYSCFG);

    /* configure button pin as input */
    gpio_mode_set(MOTOR_IN1_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,MOTOR_IN1_PIN);
    gpio_mode_set(MOTOR_IN2_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,MOTOR_IN2_PIN);
    gpio_mode_set(MOTOR_IN3_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,MOTOR_IN3_PIN);
    gpio_mode_set(MOTOR_IN4_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,MOTOR_IN4_PIN);    
    
    gpio_mode_set(MOTOR_IN5_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,MOTOR_IN5_PIN);    
    gpio_mode_set(MOTOR_IN6_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,MOTOR_IN6_PIN);
    gpio_mode_set(MOTOR_IN7_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,MOTOR_IN7_PIN);
    gpio_mode_set(MOTOR_IN8_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,MOTOR_IN8_PIN);
    
    gpio_mode_set(MOTOR_IN9_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,MOTOR_IN9_PIN);    
    gpio_mode_set(MOTOR_IN10_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,MOTOR_IN10_PIN);   
    gpio_mode_set(MOTOR_IN11_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,MOTOR_IN11_PIN);    
    gpio_mode_set(MOTOR_IN12_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,MOTOR_IN12_PIN);      
}

/*
电机方向控制初始化
*/
void MotorDir_12bitInit(void)
{

    /* enable the key clock */
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOA);        
    rcu_periph_clock_enable(RCU_SYSCFG);

    /* configure button pin as input */
    gpio_output_options_set(MOTORDIR1_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTORDIR1_Pin);     
    gpio_output_options_set(MOTORDIR2_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTORDIR2_Pin);  
    gpio_output_options_set(MOTORDIR3_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTORDIR3_Pin);  
    gpio_output_options_set(MOTORDIR4_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTORDIR4_Pin);  

    gpio_output_options_set(MOTORDIR5_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTORDIR5_Pin);  
    gpio_output_options_set(MOTORDIR6_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTORDIR6_Pin);  
    gpio_output_options_set(MOTORDIR7_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTORDIR7_Pin);  
    gpio_output_options_set(MOTORDIR8_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTORDIR8_Pin);  
 
    gpio_output_options_set(MOTORDIR9_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTORDIR9_Pin);  
    gpio_output_options_set(MOTORDIR10_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTORDIR10_Pin);  
    gpio_output_options_set(MOTORDIR11_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTORDIR11_Pin);  
    gpio_output_options_set(MOTORDIR12_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTORDIR12_Pin);  
    
    gpio_mode_set(MOTORDIR1_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MOTORDIR1_Pin);
    gpio_mode_set(MOTORDIR2_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MOTORDIR2_Pin);
    gpio_mode_set(MOTORDIR3_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MOTORDIR3_Pin);
    gpio_mode_set(MOTORDIR4_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MOTORDIR4_Pin); 

    gpio_mode_set(MOTORDIR5_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MOTORDIR5_Pin);
    gpio_mode_set(MOTORDIR6_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MOTORDIR6_Pin);
    gpio_mode_set(MOTORDIR7_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MOTORDIR7_Pin);
    gpio_mode_set(MOTORDIR8_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MOTORDIR8_Pin); 

    gpio_mode_set(MOTORDIR9_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MOTORDIR9_Pin);
    gpio_mode_set(MOTORDIR10_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MOTORDIR10_Pin);
    gpio_mode_set(MOTORDIR11_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MOTORDIR11_Pin);
    gpio_mode_set(MOTORDIR12_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MOTORDIR12_Pin);     
}



/*
电机细分控制初始化
*/
void Motor_Microstep_Init(void)
{

    /* enable the key clock */
    rcu_periph_clock_enable(RCU_GPIOE);       
    rcu_periph_clock_enable(RCU_SYSCFG);

    /* configure button pin as input */
    gpio_output_options_set(MOTOR_MS1_1_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTOR_MS1_1_Pin);  
    gpio_output_options_set(MOTOR_MS2_1_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTOR_MS2_1_Pin);
    
    gpio_output_options_set(MOTOR_MS1_2_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTOR_MS1_2_Pin);  
    gpio_output_options_set(MOTOR_MS2_2_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTOR_MS2_2_Pin);
    
    gpio_output_options_set(MOTOR_MS1_3_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTOR_MS1_3_Pin);  
    gpio_output_options_set(MOTOR_MS2_3_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTOR_MS2_3_Pin);
    
    gpio_mode_set(MOTOR_MS1_1_Port,GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MOTOR_MS1_1_Pin);
    gpio_mode_set(MOTOR_MS2_1_Port,GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MOTOR_MS2_1_Pin);
    
    gpio_mode_set(MOTOR_MS1_2_Port,GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MOTOR_MS1_2_Pin);
    gpio_mode_set(MOTOR_MS2_2_Port,GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MOTOR_MS2_2_Pin);

    gpio_mode_set(MOTOR_MS1_3_Port,GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MOTOR_MS1_3_Pin);
    gpio_mode_set(MOTOR_MS2_3_Port,GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MOTOR_MS2_3_Pin);    
}
/*
电机报警检测初始化
*/
void Motor_Fault_Init(void)
{
    /* enable the clock */
    rcu_periph_clock_enable(RCU_GPIOE);  
    rcu_periph_clock_enable(RCU_GPIOB); 
    rcu_periph_clock_enable(RCU_GPIOA);

    rcu_periph_clock_enable(RCU_SYSCFG);

    /* configure button pin as input */
    gpio_mode_set(MOTOR_FAULT1_Port, GPIO_MODE_INPUT, GPIO_PUPD_NONE,MOTORFAULT1_Pin);
    gpio_mode_set(MOTOR_FAULT2_Port, GPIO_MODE_INPUT, GPIO_PUPD_NONE,MOTORFAULT2_Pin);    
    gpio_mode_set(MOTOR_FAULT3_Port, GPIO_MODE_INPUT, GPIO_PUPD_NONE,MOTORFAULT3_Pin);
}

/*
电机使能控制初始化
*/
void Motor_Nenbl_Init(void)
{
    /* enable the clock */
    rcu_periph_clock_enable(RCU_GPIOE);  
    rcu_periph_clock_enable(RCU_GPIOD); 
    rcu_periph_clock_enable(RCU_SYSCFG);

    /* configure button pin as input */
    gpio_output_options_set(MOTOR_EN1_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTOR_EN1_Pin);    
    gpio_output_options_set(MOTOR_EN2_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTOR_EN2_Pin); 
    gpio_output_options_set(MOTOR_EN3_Port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,MOTOR_EN3_Pin); 
    
    gpio_mode_set(MOTOR_EN1_Port, GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,MOTOR_EN1_Pin);
    gpio_mode_set(MOTOR_EN2_Port, GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,MOTOR_EN2_Pin);    
    gpio_mode_set(MOTOR_EN3_Port, GPIO_MODE_OUTPUT,GPIO_PUPD_PULLUP,MOTOR_EN3_Pin);
    
    gpio_bit_write(MOTOR_EN1_Port,MOTOR_EN1_Pin,SET);
    gpio_bit_write(MOTOR_EN2_Port,MOTOR_EN2_Pin,SET);
    gpio_bit_write(MOTOR_EN3_Port,MOTOR_EN3_Pin,SET);
    
}

/*
拨码开关初始化
*/
void DipSwitch_4bitInit(void)
{
    /* enable the key clock */
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_SYSCFG);

    /* configure button pin as input */
    gpio_mode_set(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_0);
    gpio_mode_set(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_1);
    gpio_mode_set(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_2);
    gpio_mode_set(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_3);    
}

/*
拨码ID获取
*/
uint8_t GetDipSwitch_4bit(void)
{
    uint8_t Id4bit=0;
//    uint16_t Senbit=0;
    Id4bit|=gpio_input_bit_get(GPIOC,GPIO_PIN_0);
    Id4bit|=gpio_input_bit_get(GPIOC,GPIO_PIN_1)<<1;    
    Id4bit|=gpio_input_bit_get(GPIOC,GPIO_PIN_2)<<2;   
    Id4bit|=gpio_input_bit_get(GPIOC,GPIO_PIN_3)<<3;
    return Id4bit;
}

/*
系统灯初始化
*/
void  led_init (void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOE);
    /* configure led GPIO port */ 
    gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO_PIN_2);
    gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_2);

}

/*
指示灯状态翻转
time:间隔时间
*/

void System_Led(uint16_t time)
{
    if(LedTimeCount>=time)
    {
        gpio_bit_toggle(GPIOE,GPIO_PIN_2);
        LedTimeCount=0;
    }

}

void gpio_init(void)
{
    led_init ();
    DipSwitch_4bitInit();
    Sensor_12bitInit();
    MotorDir_12bitInit();
    Motor_Nenbl_Init();    
    Motor_Fault_Init();    
    Motor_Microstep_Init();    
}    

