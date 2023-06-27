
#ifndef UART_H
#define UART_H

#define PRINTSWITCH    1  

#if PRINTSWITCH 
    #define  myPrint  printf
#else    
    #define  myPrint(...)
#endif


void uart1_int(unsigned int br);

#endif


