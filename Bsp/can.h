#ifndef CAN_H
#define CAN_H

#define CAN_BAUDRATE   1000             //������
#define CANREVIDBASS   0x100            //����֡��ʼID

void Can0_Init(void);
signed char Can0_DataSend(unsigned char *,unsigned char ,unsigned short);    


#endif






