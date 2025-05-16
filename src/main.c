#include <stm32g4xx_hal.h>
#include <stm32g4xx_hal_i2c.h>
#include <stm32g4xx_hal_gpio.h>
// LCD 0x3F
#define OLED_ADDR (0x3C << 1)

int main(int argc, char const *argv[])
{
    HAL_Init();

    // SystemClock_Config();

    // MX_GPIO_Init();

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

    HAL_I2C_Init(&hi2c);

    uint8_t init[22][2] = {
        {0x00, 0xA8},  {0x00, 0x3F},  // Multiplex ratio
        {0x00, 0xD3},  {0x00, 0x00},  // Display offset
        {0x00, 0x40},                 // Start line
        {0x00, 0xA0},  {0x00, 0xA1},  // Segment remap
        {0x00, 0x20},  {0x00, 0x00},  // Memory addressing mode
        {0x00, 0xC0},  {0x00, 0xC8},  // COM scan direction
        {0x00, 0xDA},  {0x00, 0x02},  // COM pins hardware config
        {0x00, 0x81},  {0x00, 0x7F},  // Contrast
        {0x00, 0xA5},  
        {0x00, 0xA6},                 // Normal display
        {0x00, 0xD5},  {0x00, 0x80},
        {0x00, 0x8D},  {0x00, 0x14},  // Pre-charge
        {0x00, 0xAF}                  // Display ON
    };

    for (uint8_t i = 0; i < sizeof(init); i++) {
        HAL_I2C_Master_Transmit(&hi2c, OLED_ADDR, init[i], sizeof(init[i]), HAL_MAX_DELAY);
    }

    while (1) {

    }
}

void sendComand(I2C_HandleTypeDef* hi2c, uint8_t command) {
    uint8_t data[2] = {0x00, command};
    HAL_I2C_Master_Transmit(hi2c, OLED_ADDR, data, sizeof(data), HAL_MAX_DELAY);
}
