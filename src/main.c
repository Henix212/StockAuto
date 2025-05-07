#include <stm32g4xx_hal.h>
#include <stm32g4xx_hal_i2c.h>
#include <stm32g4xx_hal_gpio.h>

#define OLED_ADDR (0x3C << 1)

int main(int argc, char const *argv[])
{
    HAL_Init();

    __HAL_RCC_GPIOB_CLK_ENABLE(); // Active horloge GPIOB
    __HAL_RCC_GPIOA_CLK_ENABLE(); // Active horloge GPIOA
    __HAL_RCC_I2C1_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;           // Alternate Function, Open Drain
    GPIO_InitStruct.Pull = GPIO_PULLUP;               // Pull-Up activé
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;         // AF4 pour I2C1
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;           // Alternate Function, Open Drain
    GPIO_InitStruct.Pull = GPIO_PULLUP;               // Pull-Up activé
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;         // AF4 pour I2C1
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Configuration de PB7 (SDA)
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    I2C_HandleTypeDef hi2c = {
        .Instance = I2C1,
        .Init = {
            .Timing = 0x00B01A4B,
            .OwnAddress1 = 0x00,
            .AddressingMode = I2C_ADDRESSINGMODE_7BIT,
            .DualAddressMode = I2C_DUALADDRESS_DISABLE,
            .OwnAddress2 = 0x00,
            .OwnAddress2Masks = I2C_OA2_NOMASK,
            .GeneralCallMode = I2C_GENERALCALL_DISABLE,
            .NoStretchMode = I2C_NOSTRETCH_DISABLE
        }
    };
    // INFO Periode SCL 2.8 micro secs 

    // TODO : regler le time clock + mx pour input output + UART pour le printf

    HAL_I2C_Init(&hi2c);

    uint8_t command[] = {
        0xAE,
        0xAF,
        0xA5,
        0xAE,
        0xAF,
        0xA5,
        0xAE,
        0xAF,
        0xA5,
        0xAE,
        0xAF,
        0xA5,
        0xAE,
        0xAF,
        0xA5,
    };

    // uint8_t co = 0xA5;

    for (uint8_t i = 0; i <= sizeof(command); i++) {
        HAL_Delay(10);
        if (HAL_I2C_Master_Transmit(&hi2c, OLED_ADDR, &command[i], sizeof(command[i]), HAL_MAX_DELAY) == HAL_OK) {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
        }
    }

    while (1) {

    }
}