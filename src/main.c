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

    uint8_t buffer[1024];
    memset(buffer, 0xFF, sizeof(buffer));

    OLED_DisplayFull(&hi2c, &buffer);
}

void OLED_DisplayFull(I2C_HandleTypeDef *hi2c, uint8_t* buffer) {
    for (uint8_t page = 0; page < 8; page++) {
        uint8_t set_page_cmds[] = {
            0x00,                   // Control byte: command
            0xB0 | page,            // Set page address (B0 to B7)
            0x00,                   // Set lower column address
            0x10                    // Set higher column address
        };
        HAL_I2C_Master_Transmit(hi2c, OLED_ADDR, set_page_cmds, sizeof(set_page_cmds), HAL_MAX_DELAY);

        // Data: 128 bytes for the current page
        uint8_t data[129];
        data[0] = 0x40; // Control byte for data
        memcpy(&data[1], &buffer[page * 128], 128);

        HAL_I2C_Master_Transmit(hi2c, OLED_ADDR, data, sizeof(data), HAL_MAX_DELAY);
    }
}