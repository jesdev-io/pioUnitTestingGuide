#ifndef _TEMP_SENSOR_H_
#define _TEMP_SENSOR_H_

#include <stdlib.h>
#include <stdint.h>

#define TEMP_SENSOR_FAIL -999
#define RESPONSE_LEN 8 // defined in data sheet of sensor

/// @brief Read the current temperature at the UART-connected sensor.
/// @return Temperature value in m°C
/// @note This is a dummy function for demonstrative purposes.
int32_t get_temp(void);

#endif