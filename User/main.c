#include "gd32f4xx.h"
#include "systick.h"
#include "Gpio.h"
#include "can.h"
#include "time.h"
#include "morot.h"
#include "morotstep.h"

int main(void)
{    
    systick_config();
    gpio_init();
    uart1_int(115200);                           
    Can0_Init();    
   
    Timer2_Step1_Config();    
    Timer5_Step2_Config();
    Timer6_Step3_Config();
    Timer1_Step4_Config();    
    Timer8_Step5_Config();   
    Timer9_Step6_Config();  
    Timer10_Step7_Config();   
    Timer11_Step8_Config();    
    Timer12_Step9_Config();   
    Timer13_Step10_Config();    
    Timer7_Step11And12_config();   
    Timer4_PWM1_Config();
    Timer0_PWM2_Config();
    Timer3_PWM3_Config(); 
    
    TestFunction();  
    delay_1ms(500);                             




     
    while(1) 
    {
       System_Led(400); 
       stepper_move_T(4,1,1*800,1000,2000,1000);  
       delay_1ms(1400);
       myPrint("MotEncoder4  %d\n",MotorPr4.MotEncoder);
    }
}




