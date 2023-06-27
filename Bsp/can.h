#ifndef CAN_H
#define CAN_H

#define CAN_BAUDRATE   1000             //波特率
#define CANREVIDBASS   0x100            //接受帧起始ID

void Can0_Init(void);
signed char Can0_DataSend(unsigned char *,unsigned char ,unsigned short);    


#endif






