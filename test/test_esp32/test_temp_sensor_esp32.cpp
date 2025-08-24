// test_temp_sensor_esp32.cpp
#include <Arduino.h>
#include <unity.h>
#include <memory.h>
#include "ex_uart.h"
#include "temp_sensor.h"

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

void setup(){
	delay(2000); // some hardware may need to settle first

	UNITY_BEGIN(); // start a unit test session
	RUN_TEST(test_uart_transmit);
	RUN_TEST(test_uart_receive);
	RUN_TEST(test_get_temp);

	UNITY_END(); // end a unit test session
}

void loop(){
	// stays empty
}
