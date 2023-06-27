#include "gd32f4xx.h"
#include "time.h"


void Time2_Step1_Gpio_Config(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);
   
    gpio_mode_set(MT1_STEP_PORT,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,MT1_STEP_PIN);
    gpio_output_options_set(MT1_STEP_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT1_STEP_PIN);
//    gpio_af_set(MT1_STEP_PORT,GPIO_AF_2,MT1_STEP_PIN);
}

void Time5_Step2_Gpio_Config(void)
{
    
//    rcu_periph_clock_enable(RCU_GPIOE);
//    gpio_mode_set(MT4_STEP_PORT,GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, MT4_STEP_PIN );
//    gpio_output_options_set(MT4_STEP_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT4_STEP_PIN);    
    rcu_periph_clock_enable(RCU_GPIOB);  
    gpio_mode_set(MT2_STEP_PORT,GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, MT2_STEP_PIN );
    gpio_output_options_set(MT2_STEP_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT2_STEP_PIN);
}

void Time6_Step3_Gpio_Config(void)
{
    rcu_periph_clock_enable(RCU_GPIOE);
   
    gpio_mode_set(MT3_STEP_PORT,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,MT3_STEP_PIN);
    gpio_output_options_set(MT3_STEP_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT3_STEP_PIN);
//    gpio_af_set(MT1_STEP_PORT,GPIO_AF_2,MT1_STEP_PIN);
}

void Time1_Step4_Gpio_Config(void)
{
    rcu_periph_clock_enable(RCU_GPIOE);
   
    gpio_mode_set(MT4_STEP_PORT,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,MT4_STEP_PIN);
    gpio_output_options_set(MT4_STEP_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT4_STEP_PIN);
//    gpio_af_set(MT1_STEP_PORT,GPIO_AF_2,MT1_STEP_PIN);
}
void Time8_Step5_Gpio_Config(void)
{
    rcu_periph_clock_enable(RCU_GPIOD);
   
    gpio_mode_set(MT5_STEP_PORT,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,MT5_STEP_PIN);
    gpio_output_options_set(MT5_STEP_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT5_STEP_PIN);
//    gpio_af_set(MT1_STEP_PORT,GPIO_AF_2,MT1_STEP_PIN);
}

void Time9_Step6_Gpio_Config(void)
{
    rcu_periph_clock_enable(RCU_GPIOD);
   
    gpio_mode_set(MT6_STEP_PORT,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,MT6_STEP_PIN);
    gpio_output_options_set(MT6_STEP_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT6_STEP_PIN);
//    gpio_af_set(MT1_STEP_PORT,GPIO_AF_2,MT1_STEP_PIN);
}
void Time10_Step7_Gpio_Config(void)
{
    rcu_periph_clock_enable(RCU_GPIOD);
   
    gpio_mode_set(MT7_STEP_PORT,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,MT7_STEP_PIN);
    gpio_output_options_set(MT7_STEP_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT7_STEP_PIN);
//    gpio_af_set(MT1_STEP_PORT,GPIO_AF_2,MT1_STEP_PIN);
}
void Time11_Step8_Gpio_Config(void)
{
    rcu_periph_clock_enable(RCU_GPIOD);
   
    gpio_mode_set(MT8_STEP_PORT,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,MT8_STEP_PIN);
    gpio_output_options_set(MT8_STEP_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT8_STEP_PIN);
//    gpio_af_set(MT1_STEP_PORT,GPIO_AF_2,MT1_STEP_PIN);
}
void Time12_Step9_Gpio_Config(void)
{
    rcu_periph_clock_enable(RCU_GPIOC);
   
    gpio_mode_set(MT9_STEP_PORT,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,MT9_STEP_PIN);
    gpio_output_options_set(MT9_STEP_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT9_STEP_PIN);
//    gpio_af_set(MT1_STEP_PORT,GPIO_AF_2,MT1_STEP_PIN);
}
void Time13_Step10_Gpio_Config(void)
{
    rcu_periph_clock_enable(RCU_GPIOC);
   
    gpio_mode_set(MT10_STEP_PORT,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,MT10_STEP_PIN);
    gpio_output_options_set(MT10_STEP_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT10_STEP_PIN);
//    gpio_af_set(MT1_STEP_PORT,GPIO_AF_2,MT1_STEP_PIN);
}
void Time7_Step11And12_Gpio_Config(void)
{
    rcu_periph_clock_enable(RCU_GPIOC);

    /*configure PB3(TIMER1 CH1) as alternate function*/
    gpio_mode_set(MT11_STEP_PORT, GPIO_MODE_AF,GPIO_PUPD_NONE, MT11_STEP_PIN);
    gpio_mode_set(MT12_STEP_PORT, GPIO_MODE_AF,GPIO_PUPD_NONE, MT12_STEP_PIN);
    
    gpio_output_options_set(MT11_STEP_PORT,GPIO_OTYPE_OD,GPIO_OSPEED_50MHZ,MT11_STEP_PIN);
    gpio_output_options_set(MT12_STEP_PORT,GPIO_OTYPE_OD,GPIO_OSPEED_50MHZ,MT12_STEP_PIN);
    
    gpio_af_set(MT11_STEP_PORT,GPIO_AF_3,MT11_STEP_PIN);
    gpio_af_set(MT12_STEP_PORT,GPIO_AF_3,MT12_STEP_PIN);
}

/*
电机电流GPIO初始化
*/

void Timer4_gpio_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);
 
    gpio_mode_set(MOTORCUR1_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, MOTORCUR1_Pin);
    gpio_mode_set(MOTORCUR2_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, MOTORCUR2_Pin);
    gpio_mode_set(MOTORCUR3_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, MOTORCUR3_Pin);
    gpio_mode_set(MOTORCUR4_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, MOTORCUR4_Pin);
    
    gpio_output_options_set(MOTORCUR1_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MOTORCUR1_Pin);
    gpio_output_options_set(MOTORCUR2_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MOTORCUR2_Pin);
    gpio_output_options_set(MOTORCUR3_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MOTORCUR3_Pin);
    gpio_output_options_set(MOTORCUR4_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MOTORCUR4_Pin);
    
    gpio_af_set(MOTORCUR1_Port, GPIO_AF_2, MOTORCUR1_Pin);
    gpio_af_set(MOTORCUR2_Port, GPIO_AF_2, MOTORCUR2_Pin);
    gpio_af_set(MOTORCUR3_Port, GPIO_AF_2, MOTORCUR3_Pin);
    gpio_af_set(MOTORCUR4_Port, GPIO_AF_2, MOTORCUR4_Pin);    
    
}

/*
电机电流GPIO初始化
*/

void Timer0_gpio_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOE);

   
    gpio_mode_set(MOTORCUR5_Port,GPIO_MODE_AF,GPIO_PUPD_NONE,MOTORCUR5_Pin);
    gpio_mode_set(MOTORCUR6_Port,GPIO_MODE_AF,GPIO_PUPD_NONE,MOTORCUR6_Pin);
    gpio_mode_set(MOTORCUR7_Port,GPIO_MODE_AF,GPIO_PUPD_NONE,MOTORCUR7_Pin);
    gpio_mode_set(MOTORCUR8_Port,GPIO_MODE_AF,GPIO_PUPD_NONE,MOTORCUR8_Pin);
    
    gpio_output_options_set(MOTORCUR5_Port,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MOTORCUR5_Pin);
    gpio_output_options_set(MOTORCUR6_Port,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MOTORCUR6_Pin);
    gpio_output_options_set(MOTORCUR7_Port,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MOTORCUR7_Pin);
    gpio_output_options_set(MOTORCUR8_Port,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MOTORCUR8_Pin);
    
    gpio_af_set(MOTORCUR5_Port, GPIO_AF_1, MOTORCUR5_Pin);
    gpio_af_set(MOTORCUR6_Port, GPIO_AF_1, MOTORCUR6_Pin);
    gpio_af_set(MOTORCUR7_Port, GPIO_AF_1, MOTORCUR7_Pin);
    gpio_af_set(MOTORCUR8_Port, GPIO_AF_1, MOTORCUR8_Pin);    
}
/*
电机电流GPIO初始化
*/

void Timer3_gpio_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOE);

    gpio_mode_set(MOTORCUR9_Port,GPIO_MODE_AF,GPIO_PUPD_NONE,MOTORCUR9_Pin);
    gpio_mode_set(MOTORCUR10_Port,GPIO_MODE_AF,GPIO_PUPD_NONE,MOTORCUR10_Pin);
    gpio_mode_set(MOTORCUR11_Port,GPIO_MODE_AF,GPIO_PUPD_NONE,MOTORCUR11_Pin);
    gpio_mode_set(MOTORCUR12_Port,GPIO_MODE_AF,GPIO_PUPD_NONE,MOTORCUR12_Pin);
    
    gpio_output_options_set(MOTORCUR9_Port,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MOTORCUR9_Pin);
    gpio_output_options_set(MOTORCUR10_Port,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MOTORCUR10_Pin);
    gpio_output_options_set(MOTORCUR11_Port,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MOTORCUR11_Pin);
    gpio_output_options_set(MOTORCUR12_Port,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MOTORCUR12_Pin);
    
    gpio_af_set(MOTORCUR9_Port, GPIO_AF_2, MOTORCUR9_Pin);
    gpio_af_set(MOTORCUR10_Port, GPIO_AF_2, MOTORCUR10_Pin);
    gpio_af_set(MOTORCUR11_Port, GPIO_AF_2, MOTORCUR11_Pin);
    gpio_af_set(MOTORCUR12_Port, GPIO_AF_2, MOTORCUR12_Pin);    
}
void Timer2_Step1_Config(void)
{
    /* ---------------------------------------------------------------------------*/
  
    timer_parameter_struct timer_initpara;
    
    rcu_periph_clock_enable(RCU_TIMER2);
    
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    
    timer_internal_clock_config(TIMER2);
    
    timer_deinit(TIMER2);
    
    Time2_Step1_Gpio_Config();
    
    /* TIMER2 configuration */
    timer_initpara.prescaler         = 200-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER2,&timer_initpara);
    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER2);
    
    timer_interrupt_flag_clear(TIMER2, TIMER_INT_FLAG_UP);
    
    nvic_irq_enable(TIMER2_IRQn,0,0);
    
}

void Timer5_Step2_Config(void)
{
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER5);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    
    timer_internal_clock_config(TIMER5);
    
    timer_deinit(TIMER5);
    Time5_Step2_Gpio_Config();
    
    /* TIMER5 configuration */
    timer_initpara.prescaler         = 200-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER5,&timer_initpara);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER5);
    
    timer_interrupt_flag_clear(TIMER5,TIMER_INT_FLAG_UP);
    
    nvic_irq_enable(TIMER5_DAC_IRQn,0,0);
    

}



void Timer6_Step3_Config(void)
{
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER6);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    
    timer_internal_clock_config(TIMER6);
    
    timer_deinit(TIMER6);
    Time6_Step3_Gpio_Config();
    
    /* TIMER5 configuration */
    timer_initpara.prescaler         = 200-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER6,&timer_initpara);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER6);
    timer_interrupt_flag_clear(TIMER6, TIMER_INT_FLAG_UP); 
    nvic_irq_enable(TIMER6_IRQn,0,0);
}


void Timer1_Step4_Config(void)
{
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER1);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    
    timer_internal_clock_config(TIMER1);
    
    timer_deinit(TIMER1);
    Time1_Step4_Gpio_Config();
    
    /* TIMER5 configuration */
    timer_initpara.prescaler         = 200-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER1,&timer_initpara);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER1);
    timer_interrupt_flag_clear(TIMER1, TIMER_INT_FLAG_UP);   
    nvic_irq_enable(TIMER1_IRQn,0,0);
}


void Timer8_Step5_Config(void)
{
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER8);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    
    timer_internal_clock_config(TIMER8);
    
    timer_deinit(TIMER8);
    Time8_Step5_Gpio_Config();
    
    /* TIMER8 configuration */
    timer_initpara.prescaler         = 200-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER8,&timer_initpara);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER8);
    timer_interrupt_flag_clear(TIMER8, TIMER_INT_FLAG_UP);        
    nvic_irq_enable(TIMER0_BRK_TIMER8_IRQn,0,0);
}


void Timer9_Step6_Config(void)
{
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER9);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    
    timer_internal_clock_config(TIMER9);
    
    timer_deinit(TIMER9);
    
    Time9_Step6_Gpio_Config();
    
    /* TIMER9 configuration */
    timer_initpara.prescaler         = 200-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER9,&timer_initpara);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER9);
    timer_interrupt_flag_clear(TIMER9, TIMER_INT_FLAG_UP);   
    nvic_irq_enable(TIMER0_UP_TIMER9_IRQn ,0,0);
}


void Timer10_Step7_Config(void)
{
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER10);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    
    timer_internal_clock_config(TIMER10);
    
    timer_deinit(TIMER10);
    
    Time10_Step7_Gpio_Config();
    
    /* TIMER10 configuration */
    timer_initpara.prescaler         = 200-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER10,&timer_initpara);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER10);
    timer_interrupt_flag_clear(TIMER10, TIMER_INT_FLAG_UP); 
    nvic_irq_enable(TIMER0_TRG_CMT_TIMER10_IRQn,0,0);
}

void Timer11_Step8_Config(void)
{
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER11);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    
    timer_internal_clock_config(TIMER11);
    
    timer_deinit(TIMER11);
    
    Time11_Step8_Gpio_Config();
    
    /* TIMER11 configuration */
    timer_initpara.prescaler         = 200-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER11,&timer_initpara);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER11);
    timer_interrupt_flag_clear(TIMER11, TIMER_INT_FLAG_UP);
    nvic_irq_enable(TIMER7_BRK_TIMER11_IRQn,0,0);
}

void Timer12_Step9_Config(void)
{
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER12);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    
    timer_internal_clock_config(TIMER12);
    
    timer_deinit(TIMER12);
    
    Time12_Step9_Gpio_Config();
    
    /* TIMER12 configuration */
    timer_initpara.prescaler         = 200-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER12,&timer_initpara);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER12);
    timer_interrupt_flag_clear(TIMER12, TIMER_INT_FLAG_UP);   
    nvic_irq_enable(TIMER7_UP_TIMER12_IRQn,0,0);
}

void Timer13_Step10_Config(void)
{
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER13);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    
    timer_internal_clock_config(TIMER13);
    timer_deinit(TIMER13);

    Time13_Step10_Gpio_Config();
    
    /* TIMER13 configuration */
    timer_initpara.prescaler         = 200-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER13,&timer_initpara);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER13);
    timer_interrupt_flag_clear(TIMER13, TIMER_INT_FLAG_UP);   
    nvic_irq_enable(TIMER7_TRG_CMT_TIMER13_IRQn,0,0);
}

void Timer7_Step11And12_config(void)
{

    timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER7);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);

    timer_deinit(TIMER7);
    
    Time7_Step11And12_Gpio_Config();
    
    /* TIMER7 configuration */
    timer_initpara.prescaler         = 200-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 65535;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER7,&timer_initpara);

     /*configuration in OC TOGGLE mode */
    timer_ocintpara.ocpolarity  = TIMER_OC_POLARITY_HIGH;
    timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
    timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
    
    timer_channel_output_config(TIMER7,TIMER_CH_2,&timer_ocintpara);
    timer_channel_output_config(TIMER7,TIMER_CH_3,&timer_ocintpara);
    
    timer_channel_output_pulse_value_config(TIMER7,TIMER_CH_2,0);
    timer_channel_output_mode_config(TIMER7,TIMER_CH_2,TIMER_OC_MODE_TOGGLE);
    timer_channel_output_shadow_config(TIMER7,TIMER_CH_2,TIMER_OC_SHADOW_DISABLE);

    timer_channel_output_pulse_value_config(TIMER7,TIMER_CH_3,0);
    timer_channel_output_mode_config(TIMER7,TIMER_CH_3,TIMER_OC_MODE_TOGGLE);
    timer_channel_output_shadow_config(TIMER7,TIMER_CH_3,TIMER_OC_SHADOW_DISABLE);
    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER7);
    
    timer_primary_output_config(TIMER7,ENABLE);
    
    timer_interrupt_flag_clear(TIMER7,TIMER_INT_FLAG_CH2);
    timer_interrupt_flag_clear(TIMER7,TIMER_INT_FLAG_CH3); 
    
    nvic_irq_enable(TIMER7_Channel_IRQn,0,0);
}

/*
PWM_1
*/
void Timer4_PWM1_Config(void)
{
    timer_oc_parameter_struct timer_ocintpara;

    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER4);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);

    timer_deinit(TIMER4);
    Timer4_gpio_config();
    /* TIMER2 configuration */
    timer_initpara.prescaler         = 2-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = PWM_MAXVAL;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER4,&timer_initpara);


     /* CH1,CH2 and CH3 CH4 configuration in PWM mode */
    timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE ;
    timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_LOW;
    timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_LOW;
    timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_HIGH;
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_HIGH;

    timer_channel_output_config(TIMER4,TIMER_CH_0,&timer_ocintpara);
    timer_channel_output_config(TIMER4,TIMER_CH_1,&timer_ocintpara);
    timer_channel_output_config(TIMER4,TIMER_CH_2,&timer_ocintpara);
    timer_channel_output_config(TIMER4,TIMER_CH_3,&timer_ocintpara);    


    timer_channel_output_pulse_value_config(TIMER4,TIMER_CH_0,0);
    timer_channel_output_mode_config(TIMER4,TIMER_CH_0,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER4,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);

    timer_channel_output_pulse_value_config(TIMER4,TIMER_CH_1,0);
    timer_channel_output_mode_config(TIMER4,TIMER_CH_1,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER4,TIMER_CH_1,TIMER_OC_SHADOW_DISABLE);

    timer_channel_output_pulse_value_config(TIMER4,TIMER_CH_2,0);
    timer_channel_output_mode_config(TIMER4,TIMER_CH_2,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER4,TIMER_CH_2,TIMER_OC_SHADOW_DISABLE);

    timer_channel_output_pulse_value_config(TIMER4,TIMER_CH_3,0);
    timer_channel_output_mode_config(TIMER4,TIMER_CH_3,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER4,TIMER_CH_3,TIMER_OC_SHADOW_DISABLE);
    /* TIMER4 counter enable */
    timer_enable(TIMER4);
}
/*
PWM_2
*/
void Timer0_PWM2_Config(void)
{
    timer_oc_parameter_struct timer_ocintpara;

    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER0);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    timer_deinit(TIMER0);
    
    Timer0_gpio_config();
    
    /* TIMER0 configuration */
    timer_initpara.prescaler         = 2-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = PWM_MAXVAL;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER0,&timer_initpara);

     /* CH1,CH2 and CH3 CH4 configuration in PWM mode */
    timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE ;
    timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_LOW;
    timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_LOW;
    timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_HIGH;
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_HIGH;

    timer_channel_output_config(TIMER0,TIMER_CH_0,&timer_ocintpara);
    timer_channel_output_config(TIMER0,TIMER_CH_1,&timer_ocintpara);
    timer_channel_output_config(TIMER0,TIMER_CH_2,&timer_ocintpara);
    timer_channel_output_config(TIMER0,TIMER_CH_3,&timer_ocintpara);    
    
    timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_0,0);
    timer_channel_output_mode_config(TIMER0,TIMER_CH_0,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER0,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);

    timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_1,0);
    timer_channel_output_mode_config(TIMER0,TIMER_CH_1,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER0,TIMER_CH_1,TIMER_OC_SHADOW_DISABLE);

    timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_2,0);
    timer_channel_output_mode_config(TIMER0,TIMER_CH_2,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER0,TIMER_CH_2,TIMER_OC_SHADOW_DISABLE);

    timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_3,0);
    timer_channel_output_mode_config(TIMER0,TIMER_CH_3,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER0,TIMER_CH_3,TIMER_OC_SHADOW_DISABLE);
    
     timer_primary_output_config(TIMER0,ENABLE);
    /* TIMER0 counter enable */
    timer_enable(TIMER0);
}
/*
PWM_3
*/
void Timer3_PWM3_Config(void)
{
    timer_oc_parameter_struct timer_ocintpara;

    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER3);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);

    timer_deinit(TIMER3);
    Timer3_gpio_config();
    /* TIMER2 configuration */
    timer_initpara.prescaler         = 2-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = PWM_MAXVAL;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER3,&timer_initpara);


     /* CH1,CH2 and CH3 CH4 configuration in PWM mode */
    timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE ;
    timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_LOW;
    timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_LOW;
    timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_HIGH;
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_HIGH;

    timer_channel_output_config(TIMER3,TIMER_CH_0,&timer_ocintpara);
    timer_channel_output_config(TIMER3,TIMER_CH_1,&timer_ocintpara);
    timer_channel_output_config(TIMER3,TIMER_CH_2,&timer_ocintpara);
    timer_channel_output_config(TIMER3,TIMER_CH_3,&timer_ocintpara);    


    timer_channel_output_pulse_value_config(TIMER3,TIMER_CH_0,0);
    timer_channel_output_mode_config(TIMER3,TIMER_CH_0,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER3,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);

    timer_channel_output_pulse_value_config(TIMER3,TIMER_CH_1,0);
    timer_channel_output_mode_config(TIMER3,TIMER_CH_1,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER3,TIMER_CH_1,TIMER_OC_SHADOW_DISABLE);

    timer_channel_output_pulse_value_config(TIMER3,TIMER_CH_2,0);
    timer_channel_output_mode_config(TIMER3,TIMER_CH_2,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER3,TIMER_CH_2,TIMER_OC_SHADOW_DISABLE);

    timer_channel_output_pulse_value_config(TIMER3,TIMER_CH_3,0);
    timer_channel_output_mode_config(TIMER3,TIMER_CH_3,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER3,TIMER_CH_3,TIMER_OC_SHADOW_DISABLE);
    /* TIMER3 counter enable */
    timer_enable(TIMER3);
}
















