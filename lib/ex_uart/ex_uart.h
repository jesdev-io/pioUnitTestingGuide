#ifndef _EX_UART_H
#define _EX_UART_H

#include <stdlib.h>

#define UART_MAX_DATA_LEN 64

typedef enum {
    UART_ERR_NONE,
    UART_ERR_BUF_NULL,
    UART_ERR_LEN_OVR
}uart_err_t;

/// @brief Send data via UART terminal.
/// @param buf Buffer to send data from.
/// @param len Length of data in byte.
/// @return Status message, 0 if OK.
/// @note This is a dummy function for demonstrative purposes.
int8_t uart_transmit(char* buf, uint8_t len);


/// @brief Receive data via UART terminal.
/// @param buf Buffer to store data to.
/// @param len Length of data in byte.
/// @return Status message, 0 if OK.
/// @note This is a dummy function for demonstrative purposes.
int8_t uart_receive(char* buf, uint8_t len);

#endif