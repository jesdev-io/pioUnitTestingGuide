// test_temp_sensor_stm32.cpp
#include "stm32g4xx_hal.h"
#include <unity.h>
#include <memory.h>
#include "ex_uart.h"
#include "temp_sensor.h"

void SystemClock_Config(void);

#ifdef __cplusplus
/* A `extern "C"` guard is required because the source files for the sensor and UART
are defined as .cpp files so they can be used with the Arduino framework for the ESP32.
However, the STM32 needs to have its __weak functions overwritten by explicitly C-style
functions, otherwise they are not linked properly (in this case the MCU time never increments.)
*/
extern "C"
{
#endif
void SysTick_Handler(void) {
    HAL_IncTick();
}
#ifdef __cplusplus
}
#endif /* extern "C" */

void setUp(){
	// this is not the Arduino `setup()`!
	// this function gets executed before every test
	// populating this is optional
}

void tearDown(){
	// this function gets executed after every test
	// populating this is optional
}

void test_uart_transmit(){
    // This function tests if the string "dummy" can be transmitted correctly.
    char dummy[] = "dummy";
    int8_t stat = uart_transmit(dummy, sizeof(dummy));
    TEST_ASSERT_EQUAL(0, stat);
};

void test_uart_receive(){
    // This function tests if a pending string in the UART peripheral can be read.
    char buf[RESPONSE_LEN];
    memset(buf, 0, RESPONSE_LEN);
    int8_t stat = uart_receive(buf, sizeof(buf));
    TEST_ASSERT_EQUAL(0, stat);
    TEST_ASSERT_EQUAL(RESPONSE_LEN-1, strlen(buf));
};

void test_get_temp(){
    // This function tests if a temperature can be read from the sensor.
    int32_t t = get_temp();
    t /= 1000; // Sensor returns m°C
    // signature is (delta, expected, actual)
    TEST_ASSERT_INT32_WITHIN(50, 0, t);
    #ifdef DEV_TEST
    TEST_ASSERT_INT32_WITHIN(5, 20, t);
    #endif
}

int main(){
    HAL_Init();             // Init the STM32 HAL
    SystemClock_Config();   // Cnfigure clock tree (defined below)
    HAL_Delay(2000);        // some hardware may need to settle first

	UNITY_BEGIN(); // start a unit test session
	RUN_TEST(test_uart_transmit);
	RUN_TEST(test_uart_receive);
	RUN_TEST(test_get_temp);

	UNITY_END(); // end a unit test session
}

void SystemClock_Config(void){
    // This function sets up the basic clock tree of the controller.
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
    RCC_OscInitStruct.PLL.PLLN = 85;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
}