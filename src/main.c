#include <stm32g4xx_hal.h>
#include <stm32g4xx_hal_i2c.h>

#define OLED_ADDR (0x3C << 1)

int main(int argc, char const *argv[])
{
    HAL_Init();

    I2C_HandleTypeDef hi2c = {
        .Instance = I2C1,
        .Init = {
            .Timing = 0x00B01A4B,
            .OwnAddress1 = 0x00,
            .AddressingMode = I2C_ADDRESSINGMODE_7BIT,
            .DualAddressMode = I2C_DUALADDRESS_DISABLE,
            .OwnAddress2 = 0x00,
            .OwnAddress2Masks = 0x00,
            .GeneralCallMode = I2C_GENERALCALL_DISABLE,
            .NoStretchMode = I2C_NOSTRETCH_DISABLE
        }
    };

    HAL_I2C_Init(&hi2c);

    uint8_t data[2] = {0x00, 0xFF};

    HAL_I2C_Master_Transmit(&hi2c, OLED_ADDR, data, 2, HAL_MAX_DELAY);
}