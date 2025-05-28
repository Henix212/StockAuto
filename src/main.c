#include "stm32g4xx_hal.h"
#include "servoMoteur.h"

int main(int argc, char const *argv[])
{
    HAL_Init();  // Initialisation de la HAL

    INIT_servo();  // Initialiser le servo

    SET_default_position();  // Position par défaut

    while (1) {
        SET_position_manual(100);
        HAL_Delay(1000);  // Attendre 1 seconde
        SET_position_manual(150);
        HAL_Delay(1000);  // Attendre 1 seconde
    }
}

