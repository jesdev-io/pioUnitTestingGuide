#include "ex_uart.h"
#include <string.h>

#ifdef EXAMPLE_ESP32
int8_t uart_init(uint32_t baud){
    if(baud > 115200){
        return UART_ERR_PARAM;
    }

    // Actual init would happen here

    return UART_ERR_NONE;
}

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
#endif // EXAMPLE_ESP32

#ifdef EXAMPLE_STM32

UART_HandleTypeDef huart2;

int8_t uart_init(uint32_t baud){
    if(baud > 115200){
        return UART_ERR_PARAM;
    }
    // STM32 specific UART init code
    huart2.Instance = USART2;
    huart2.Init.BaudRate = baud;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart2) != HAL_OK) {
        return UART_ERR_PARAM;
    }

    return UART_ERR_NONE;
}

int8_t uart_transmit(char* buf, uint8_t len){
    if(buf == NULL){
        return (int8_t)UART_ERR_BUF_NULL;
    }
    if(len > UART_MAX_DATA_LEN){
        return (int8_t)UART_ERR_LEN_OVR;
    }
    
    HAL_UART_Transmit(&huart2, (uint8_t*)buf, len, HAL_MAX_DELAY);

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

void HAL_UART_MspInit(UART_HandleTypeDef* huart) {
    // STM32 specific UART init callback code
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(huart->Instance == USART2) {
        __HAL_RCC_USART2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
}

#endif