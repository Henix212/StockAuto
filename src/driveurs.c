#include <stdint.h>
#include "gpio.h"
#include "stm32g4xx_hal.h"

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
