#include "main.h"

#define OLED_ADDR (0x3C << 1)

void OLED_sendCommand(uint8_t command);

int main(int argc, char const *argv[])
{
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();

    uint8_t init[20] = {
        0xA8, 0x3F,
        0xD3, 0x00,
        0x40,
        0xA0, 0xA1,
        0xC0, 0xC8,
        0xDA, 0x02,
        0x81, 0x7F,
        0xA5,
        0xA6,
        0xD5, 0x80,
        0x8D, 0x14,
        0xAF
    };

    for (uint8_t i = 0; i < sizeof(init); i++) {
        OLED_sendCommand(init[i]);
    }

    while (1) {

    }
}

/// @brief Sends a command th
/// @param command 
void OLED_sendCommand(uint8_t command) {
    uint8_t data[2] = {0x00, command};
    I2C_TransmitDualByte(OLED_ADDR, data);
}

//
//  MX Code for errors and configuring the clock
//

void Error_Handler(void) {
    __disable_irq();
    while (1) {} // CODE PERSO
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

