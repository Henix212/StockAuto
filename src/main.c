#include <stdint.h>
#include "stm32g4_gpio.h"
#include "stm32g4xx_hal.h"


int main(int argc, char const *argv[]) // Correction : int au lieu de void
{
    HAL_Init(); // Initialisation de la HAL

    // Configuration de la broche DIR (PA6)
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 0);

    // Configuration de la broche STEP (PA5)
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 0);

    while (1)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET); // DIR = 1

        for (int i = 0; i < 200; i++) {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);   // STEP HIGH
            HAL_Delay(10); // ou HAL_Delay_us() pour plus précis
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); // STEP LOW
            HAL_Delay(10); // ou HAL_Delay_us() pour plus précis
        }
    }

    return 0; // Ajout d'un retour pour indiquer que le programme s'est terminé correctement
}