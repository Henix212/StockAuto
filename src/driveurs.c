#include <stdint.h>
#include "stm32g4_gpio.h"
#include "stm32g4xx_hal.h"

void GPIO_config(void) {
    // Configuration des broches DIR 
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 0); // DIR A
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_1, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 0); // DIR B

    // Configuration des broches STEP 
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 0); // STEP A
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 0); // STEP B

    // Configuration des broches ENABLE
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 1); // ENABLE A
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 1); // ENABLE B
}

void GPIO_step(int number_step, int direction, char driveur) {
    switch (driveur) {
        case 'A':
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET); // ENABLE A
            
            if (direction == 1) {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); // DIR A = 1
            } else {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); // DIR A = 0
            }
            for (int i = 0; i < number_step; i++) {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);   // STEP HIGH
                HAL_Delay(1);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET); // STEP LOW
                HAL_Delay(1);
            }
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET); // Désactiver ENABLE A
            break;

        case 'B':
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // ENABLE B
            if (direction == 1) {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET); // DIR B = 1
            } else {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET); // DIR B = 0
            }
            for (int i = 0; i < number_step; i++) {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);   // STEP HIGH
                HAL_Delay(1);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET); // STEP LOW
                HAL_Delay(1);
            }
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); // Désactiver ENABLE B
            break;

        default:
            // Gestion d'erreur si le driveur est invalide
            break;
    }
}
