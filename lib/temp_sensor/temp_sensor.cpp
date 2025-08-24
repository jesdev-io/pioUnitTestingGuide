#include "temp_sensor.h"
#include "ex_uart.h"

int32_t get_temp(){
    char cmd[] = "GET"; // "get" command as per sensor data sheet
    char buf[8]; // receive buffer
    if(uart_transmit(cmd, sizeof(cmd)) != UART_ERR_NONE){ // send command
        return TEMP_SENSOR_FAIL;
    } 
    if(uart_receive(buf, sizeof(buf)) != UART_ERR_NONE){ // receive answer
        return TEMP_SENSOR_FAIL;
    }
    char dummy_return[] = "0020000"; // imagined return from the sensor
    return atoi(dummy_return); // convert string to integer
}