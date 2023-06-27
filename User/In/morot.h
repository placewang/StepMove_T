#ifndef MOROT_H
#define MOROT_H

#include "gd32f4xx.h"


/*电机上下使能*/
#define  MOROT_UPEN     RESET
#define  MOROT_DOWNEN   SET






signed char Motor_Dir_Set(unsigned char Munm,char Dr);
signed char Motor_DirS_Set(unsigned char ,unsigned char , char );
signed char Motor_Current_Set(unsigned char,unsigned char,unsigned short);
signed char Motor_Enbl_Set(unsigned char , char );
signed char Motor_Microstep_Set(unsigned char, unsigned char);
signed char Motor_Fault_Get(void);
unsigned short GetSensorSta(void);
signed char Motor_Star_Set(unsigned char,unsigned char);
signed char Motor_Stop_Set(unsigned char,unsigned char);
/*motor step*/
signed char Motor_MovePos(unsigned char, unsigned int ,signed int ,unsigned char);
int8_t stepper_move_T( uint8_t starnum,uint8_t endnum,uint8_t mode, int32_t step,
                       uint32_t accel, uint32_t decel, uint32_t speed);

void TestFunction(void);
#endif




