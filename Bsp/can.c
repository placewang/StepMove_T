#include "gd32f4xx.h"
#include "can.h"
#include "Gpio.h"
#include "queue.h"

Queue Can1_revQueuebuff;
QUEUE_DATA_T CAN1Buff[CAN1LEN];			 //CAN1队列缓存区

void can_config()
{
    can_parameter_struct            can_parameter;
    can_filter_parameter_struct     can_filter;
    
    can_struct_para_init(CAN_INIT_STRUCT, &can_parameter);
    can_struct_para_init(CAN_FILTER_STRUCT, &can_filter);
    /* initialize CAN register */
    can_deinit(CAN0);
    
    /* initialize CAN parameters */
    can_parameter.time_triggered = DISABLE;
    can_parameter.auto_bus_off_recovery = ENABLE;
    can_parameter.auto_wake_up = DISABLE;
    can_parameter.auto_retrans = ENABLE;
    can_parameter.rec_fifo_overwrite = DISABLE;
    can_parameter.trans_fifo_order = DISABLE;
    can_parameter.working_mode = CAN_NORMAL_MODE;
    can_parameter.resync_jump_width = CAN_BT_SJW_1TQ;
    can_parameter.time_segment_1 = CAN_BT_BS1_7TQ;
    can_parameter.time_segment_2 = CAN_BT_BS2_2TQ;
    
    /* 1MBps */
#if CAN_BAUDRATE == 1000
    can_parameter.prescaler = 5;
    /* 500KBps */
#elif CAN_BAUDRATE == 500
    can_parameter.prescaler = 10;
    /* 250KBps */
#elif CAN_BAUDRATE == 250
    can_parameter.prescaler = 20;
    /* 125KBps */
#elif CAN_BAUDRATE == 125
    can_parameter.prescaler = 40;
#else
    #error "please select list can baudrate in private defines in main.c "
#endif  
    /* initialize CAN */
    can_init(CAN0, &can_parameter);
    
    /* initialize filter */ 
    can_filter.filter_number=0;
    can_filter.filter_mode = CAN_FILTERMODE_MASK;
    can_filter.filter_bits = CAN_FILTERBITS_32BIT;
    can_filter.filter_list_high = (CANREVIDBASS+GetDipSwitch_4bit())<<5;
    can_filter.filter_list_low = 0x0000;
    can_filter.filter_mask_high = (CANREVIDBASS+GetDipSwitch_4bit())<<5;
    can_filter.filter_mask_low = 0x0000;
    can_filter.filter_fifo_number = CAN_FIFO0;
    can_filter.filter_enable = ENABLE;    
    can_filter_init(&can_filter);

    nvic_irq_enable(CAN0_RX0_IRQn,0,0);
    can_interrupt_enable(CAN0, CAN_INT_RFNE0);
    InitQueue(&Can1_revQueuebuff,CAN1Buff,CAN1LEN);

}


void can_gpio_config(void)
{
    /* enable CAN clock */
    rcu_periph_clock_enable(RCU_CAN0);
    rcu_periph_clock_enable(RCU_GPIOA);
    
    /* configure CAN0 GPIO */
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_11);
    gpio_af_set(GPIOA, GPIO_AF_9, GPIO_PIN_11);
    
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_12);
    gpio_af_set(GPIOA, GPIO_AF_9, GPIO_PIN_12);
}

void Can0_Init(void)
{
    can_gpio_config();
    can_config();
}

/*
发送CAN0数据
data:发送数据
len: 发送长度
id: 发送CANID
*/
uint8_t  Can0transmit_mailbox = 0;
uint16_t Can0sendtimeout=0;
int8_t Can0_DataSend(uint8_t *data,uint8_t len,uint16_t id)
{
    can_trasnmit_message_struct transmit_message;
    transmit_message.tx_sfid = id;
    transmit_message.tx_efid = 0x00;
    transmit_message.tx_ft = CAN_FT_DATA;
    transmit_message.tx_ff = CAN_FF_STANDARD;
    transmit_message.tx_dlen = len;   
    
    for(char i=0;i<len;i++)
    {
        transmit_message.tx_data[i] = data[i];
    }
    Can0transmit_mailbox=can_message_transmit(CAN0, &transmit_message);  
    Can0sendtimeout=0;
    while(can_transmit_states(CAN0,Can0transmit_mailbox)!=CAN_TRANSMIT_OK&&Can0sendtimeout<=100)
    {
        ;
    }

    return 0;
}


