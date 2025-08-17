#include "ex_uart.h"
#include <string.h>

int8_t uart_transmit(char* buf, uint8_t len){
    if(buf == NULL){
        return (int8_t)UART_ERR_BUF_NULL;
    }
    if(len > UART_MAX_DATA_LEN){
        return (int8_t)UART_ERR_LEN_OVR;
    }
    
    // Actual sending would happen here

    return (int8_t)UART_ERR_NONE;
}

int8_t uart_receive(char* buf, uint8_t len){
    if(buf == NULL){
        return (int8_t)UART_ERR_BUF_NULL;
    }
    if(len > UART_MAX_DATA_LEN){
        return (int8_t)UART_ERR_LEN_OVR;
    }
    
    // Actual receiving would happen here

    strcpy(buf, "dummyXX");
    return (int8_t)UART_ERR_NONE;
}