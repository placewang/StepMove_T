/*!
    \file    gd32f4xx_it.c
    \brief   interrupt service routines

    \version 2016-08-15, V1.0.0, firmware for GD32F4xx
    \version 2018-12-12, V2.0.0, firmware for GD32F4xx
    \version 2020-09-30, V2.1.0, firmware for GD32F4xx
    \version 2022-03-09, V3.0.0, firmware for GD32F4xx
*/

/*
    Copyright (c) 2022, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32f4xx_it.h"
#include "systick.h"
#include "queue.h"
#include "morotstep.h"
/*!
    \brief    this function handles NMI exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void NMI_Handler(void)
{
}

/*!
    \brief    this function handles HardFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void HardFault_Handler(void)
{
    /* if Hard Fault exception occurs, go to infinite loop */
    while(1) {
    }
}

/*!
    \brief    this function handles MemManage exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void MemManage_Handler(void)
{
    /* if Memory Manage exception occurs, go to infinite loop */
    while(1) {
    }
}

/*!
    \brief    this function handles BusFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void BusFault_Handler(void)
{
    /* if Bus Fault exception occurs, go to infinite loop */
    while(1) {
    }
}

/*!
    \brief    this function handles UsageFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void UsageFault_Handler(void)
{
    /* if Usage Fault exception occurs, go to infinite loop */
    while(1) {
    }
}

/*!
    \brief    this function handles SVC exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SVC_Handler(void)
{
    
}

/*!
    \brief    this function handles DebugMon exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void DebugMon_Handler(void)
{
}

/*!
    \brief    this function handles PendSV exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PendSV_Handler(void)
{
    
}
/*!
    \brief      this function handles CAN0 RX0 exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void CAN0_RX0_IRQHandler(void)
{
    /* check the receive message */
    can_receive_message_struct  receive_message;
    if(can_interrupt_flag_get(CAN0,CAN_INT_FLAG_RFL0))
    {
        can_message_receive(CAN0,CAN_FIFO0,&receive_message);
        EnQueue(&Can1_revQueuebuff,receive_message);
        can_interrupt_flag_clear(CAN0,CAN_INT_FLAG_RFL0);
    } 
}

/*
MT1
*/
void TIMER2_IRQHandler(void)
{

    timer_interrupt_flag_clear(TIMER2,TIMER_INT_FLAG_UP);
    TIM2_Interrupt_Mt1();
}

/*
MT2
*/
void TIMER5_DAC_IRQHandler(void)
{
    timer_interrupt_flag_clear(TIMER5,TIMER_INT_UP);
    TIM5_Interrupt_Mt2();
}
/*MT3*/
void TIMER6_IRQHandler(void)
{
    timer_interrupt_flag_clear(TIMER6,TIMER_INT_UP);
    TIM6_Interrupt_Mt3();
}
/*MT4*/
void TIMER1_IRQHandler(void)
{
    timer_interrupt_flag_clear(TIMER1,TIMER_INT_UP);
    TIM1_Interrupt_Mt4();

}
/*MT5*/
void TIMER0_BRK_TIMER8_IRQHandler(void)
{
    timer_interrupt_flag_clear(TIMER8,TIMER_INT_UP);
    TIM8_Interrupt_Mt5();
}
/*MT6*/
void TIMER0_UP_TIMER9_IRQHandler(void)
{
    timer_interrupt_flag_clear(TIMER9,TIMER_INT_UP);
    TIM9_Interrupt_Mt6();
}

/*MT7*/
void TIMER0_TRG_CMT_TIMER10_IRQHandler(void)
{
    timer_interrupt_flag_clear(TIMER10,TIMER_INT_UP);
    TIM10_Interrupt_Mt7();
}
/*MT8*/
void TIMER7_BRK_TIMER11_IRQHandler(void)
{    
    timer_interrupt_flag_clear(TIMER11,TIMER_INT_UP);
    TIM11_Interrupt_Mt8();
}
/*MT9*/
void TIMER7_UP_TIMER12_IRQHandler(void)
{
    timer_interrupt_flag_clear(TIMER12,TIMER_INT_UP);
    TIM12_Interrupt_Mt9();
}
/*MT10*/
void TIMER7_TRG_CMT_TIMER13_IRQHandler(void)
{
    timer_interrupt_flag_clear(TIMER13,TIMER_INT_UP);
    TIM13_Interrupt_Mt10();
}

/*MT11/12*/
void TIMER7_Channel_IRQHandler(void)
{
    if(timer_interrupt_flag_get(TIMER7,TIMER_INT_FLAG_CH2))
    {

        TIM7_Interrupt_Mt11_Mt12(); 
    }
    if(timer_interrupt_flag_get(TIMER7,TIMER_INT_FLAG_CH3))
    {
        TIM7_Interrupt_Mt11_Mt12();    
    }
}

/*!
    \brief    this function handles SysTick exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SysTick_Handler(void)
{
    //Led灯状态翻转计时
    LedTimeCount++;
    //Can0fa发送计时 
    Can0sendtimeout++;
    delay_decrement();
}
