#include "unity_config.h"
#include "stm32g4xx_hal.h"
#include "ex_uart.h"

void unityOutputStart(){
    uart_init(115200);
}

void unityOutputChar(char c){
    char s[] = {0, 0};
    s[0] = c;
    uart_transmit(s, 1);
}

void unityOutputFlush() {
    
}

void unityOutputComplete(){
    
}