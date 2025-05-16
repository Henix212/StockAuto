#include <stdint.h>
#include "stm32g4_gpio.h"
#include "stm32g4xx_hal.h"

#define DIR_1 1


int main(int argc, char const *argv[]) // Correction : int au lieu de void
{
    HAL_Init(); // Initialisation de la HAL

        // Forcer la configuration de PA3 comme GPIO
    __HAL_RCC_GPIOA_CLK_ENABLE(); // Activer l'horloge pour GPIOA
    
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Mode sortie push-pull
    GPIO_InitStruct.Pull = GPIO_NOPULL;         // Pas de pull-up/pull-down
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // Vitesse élevée
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Configuration des broches DIR 
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 0);
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 0);

    // Configuration des broches STEP 
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 0);
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 0);

    // Configuration des broches ENABLE
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 1); // Configuration de la broche ENABLE (PA7)
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 1); // Configuration

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); // DIR = 1
    
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET); // ENABLE 
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // ENABLE

    while (1)
    {
        for (int i = 0; i < 1000; i++) {
         
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);   // STEP HIGH
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET); 
            HAL_Delay(10); // ou HAL_Delay_us() pour plus précis
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET); // STEP LOW
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
            HAL_Delay(10); // ou HAL_Delay_us() pour plus précis
        }  
    }

    return 0; // Ajout d'un retour pour indiquer que le programme s'est terminé correctement
}