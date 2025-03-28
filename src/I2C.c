#include <stdint.h>
#include "stm32g4xx_hal.h"
#include <stm32g4xx_hal_conf.h>
#include <stm32g4xx_hal_gpio.h>
#include <stm32g4xx_hal_i2c.h>

#include "I2C.h"

/*
    @brief: Initializes the I2C peripheral.
    @author: Pereira de Almeida Hugo Gabriel
    @param: None
    @return: 1 if successful, 0 if failed
*/
int I2C_Init(void) {
    // Enable the I2C1 clock
    __HAL_RCC_I2C1_CLK_ENABLE();

    // Enable GPIO clocks for GPIOA (assuming PA6 and PA5 are used for I2C)
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configure GPIO pins for I2C SCL (PA6) and SDA (PA5)
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Configure PA6 as I2C SCL (Alternate Function Open-Drain)
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD; // Alternate Function Open-Drain
    GPIO_InitStruct.Pull = GPIO_PULLUP;    // Enable pull-up resistors
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // High speed
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;    // I2C1 alternate function
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Configure PA5 as I2C SDA (Alternate Function Open-Drain)
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    return 1; // Return true if initialization is successful
}