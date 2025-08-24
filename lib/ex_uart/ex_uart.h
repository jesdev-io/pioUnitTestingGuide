#ifndef _EX_UART_H_
#define _EX_UART_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <stdint.h>

#define UART_MAX_DATA_LEN 64

typedef enum {
    UART_ERR_NONE,
    UART_ERR_BUF_NULL,
    UART_ERR_LEN_OVR,
    UART_ERR_PARAM
}uart_err_t;

/// @brief Initialize the UART peripheral.
/// @param baud Baudrate.
/// @return Status message, 0 if OK.
int8_t uart_init(uint32_t baud);

/// @brief Send data via UART terminal.
/// @param buf Buffer to send data from.
/// @param len Length of data in byte.
/// @return Status message, 0 if OK.
int8_t uart_transmit(char* buf, uint8_t len);


/// @brief Receive data via UART terminal.
/// @param buf Buffer to store data to.
/// @param len Length of data in byte.
/// @return Status message, 0 if OK.
int8_t uart_receive(char* buf, uint8_t len);

#ifdef EXAMPLE_STM32

#include "stm32g4xx_hal.h"
void HAL_UART_MspInit(UART_HandleTypeDef* huart);

#endif // EXAMPLE_STM32

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // _EX_UART_H_