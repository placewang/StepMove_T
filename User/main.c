#include "gd32f4xx.h"
#include "systick.h"
#include "Gpio.h"
#include "can.h"
#include "time.h"
#include "morot.h"
#include "morotstep.h"

uint8_t startm=1;
uint8_t   endm=12;

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


//    stepper_move_T(startm,endm,1,-800,1000,2000,1000);  
//    delay_1ms(1400);     
//    myPrint("MotEncoder1  %d\n",MotorPr1.MotEncoder);
//    myPrint("MotEncoder2  %d\n",MotorPr2.MotEncoder);
//    myPrint("MotEncoder3  %d\n",MotorPr3.MotEncoder);
//    myPrint("MotEncoder4  %d\n",MotorPr4.MotEncoder);    
//    stepper_move_T(startm,endm,0,100,1000,2000,1000);     
//    delay_1ms(1400);

    while(1) 
    {
       System_Led(400); 
       stepper_move_T(startm,endm,1,-800*30,10000,9000,1000*10); 
       delay_1ms(1000*3);          
       myPrint("MotEncoder1  %d\n",MotorPr1.MotEncoder);
             delay_1ms(50);  
       myPrint("MotEncoder2  %d\n",MotorPr2.MotEncoder);
               delay_1ms(50); 
       myPrint("MotEncoder3  %d\n",MotorPr3.MotEncoder);
               delay_1ms(50); 
       myPrint("MotEncoder4  %d\n",MotorPr4.MotEncoder);
             delay_1ms(50);
       myPrint("MotEncoder5  %d\n",MotorPr5.MotEncoder);
              delay_1ms(50);  
       myPrint("MotEncoder6  %d\n",MotorPr6.MotEncoder);
               delay_1ms(50); 
       myPrint("MotEncoder7  %d\n",MotorPr7.MotEncoder);
               delay_1ms(50); 
       myPrint("MotEncoder8  %d\n",MotorPr8.MotEncoder);        
             delay_1ms(50);
       myPrint("MotEncoder9  %d\n",MotorPr9.MotEncoder);
              delay_1ms(50);  
       myPrint("MotEncoder10  %d\n",MotorPr10.MotEncoder);
               delay_1ms(50); 
       myPrint("MotEncoder11  %d\n",MotorPr11.MotEncoder);
               delay_1ms(50); 
       myPrint("MotEncoder12  %d\n",MotorPr12.MotEncoder);         
       delay_1ms(50); 
       stepper_move_T(startm,endm,0,0,10000,9000,1000*10); 
       delay_1ms(1000*3);          
       myPrint("MotEncoder1  %d\n",MotorPr1.MotEncoder);
             delay_1ms(50);  
       myPrint("MotEncoder2  %d\n",MotorPr2.MotEncoder);
               delay_1ms(50); 
       myPrint("MotEncoder3  %d\n",MotorPr3.MotEncoder);
               delay_1ms(50); 
       myPrint("MotEncoder4  %d\n",MotorPr4.MotEncoder);
             delay_1ms(50);
       myPrint("MotEncoder5  %d\n",MotorPr5.MotEncoder);
              delay_1ms(50);  
       myPrint("MotEncoder6  %d\n",MotorPr6.MotEncoder);
               delay_1ms(50); 
       myPrint("MotEncoder7  %d\n",MotorPr7.MotEncoder);
               delay_1ms(50); 
       myPrint("MotEncoder8  %d\n",MotorPr8.MotEncoder);        
             delay_1ms(50);
       myPrint("MotEncoder9  %d\n",MotorPr9.MotEncoder);
              delay_1ms(50);  
       myPrint("MotEncoder10  %d\n",MotorPr10.MotEncoder);
               delay_1ms(50); 
       myPrint("MotEncoder11  %d\n",MotorPr11.MotEncoder);
               delay_1ms(50); 
       myPrint("MotEncoder12  %d\n",MotorPr12.MotEncoder);         
       delay_1ms(50);        
    }
}




