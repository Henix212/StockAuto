#include <stdint.h>

#include "driveurs.h"
#include "gpio.h"
#include "stm32g4xx_hal.h"

// Stepper A
static uint16_t PIN_EN_A = GPIO_PIN_7; 
static uint16_t PIN_DIR_A = GPIO_PIN_0;
static uint16_t PIN_STEP_A = GPIO_PIN_2; 

// Stepper B
static uint16_t PIN_EN_B = GPIO_PIN_4; 
static uint16_t PIN_DIR_B = GPIO_PIN_1;
static uint16_t PIN_STEP_B = GPIO_PIN_0; 

void GPIO_step(int number_step, int direction, char driveur) {
    switch (driveur) {
        case 'A':
            HAL_GPIO_WritePin(GPIOA, PIN_EN_A, GPIO_PIN_RESET); // ENABLE A
            
            if (direction == 1) {
                HAL_GPIO_WritePin(GPIOB, PIN_DIR_A, GPIO_PIN_SET); // DIR A = 1
            } else {
                HAL_GPIO_WritePin(GPIOB, PIN_DIR_A, GPIO_PIN_RESET); // DIR A = 0
            }
            for (int i = 0; i < number_step; i++) {
                HAL_GPIO_WritePin(GPIOA, PIN_STEP_A, GPIO_PIN_SET);   // STEP HIGH
                HAL_Delay(1);
                HAL_GPIO_WritePin(GPIOA, PIN_STEP_A, GPIO_PIN_RESET); // STEP LOW
                HAL_Delay(1);
            }
            HAL_GPIO_WritePin(GPIOA, PIN_EN_A, GPIO_PIN_SET); // Désactiver ENABLE A
            break;

        case 'B':
            HAL_GPIO_WritePin(GPIOA, PIN_EN_B, GPIO_PIN_RESET); // ENABLE B
            if (direction == 1) {
                HAL_GPIO_WritePin(GPIOA, PIN_DIR_B, GPIO_PIN_SET); // DIR B = 1
            } else {
                HAL_GPIO_WritePin(GPIOA, PIN_DIR_B, GPIO_PIN_RESET); // DIR B = 0
            }
            for (int i = 0; i < number_step; i++) {
                HAL_GPIO_WritePin(GPIOA, PIN_STEP_B, GPIO_PIN_SET);   // STEP HIGH
                HAL_Delay(1);
                HAL_GPIO_WritePin(GPIOA, PIN_STEP_B, GPIO_PIN_RESET); // STEP LOW
                HAL_Delay(1);
            }
            HAL_GPIO_WritePin(GPIOA, PIN_EN_B, GPIO_PIN_SET); // Désactiver ENABLE B
            break;

        default:
            Error_Handler();
            break;
    }
}
