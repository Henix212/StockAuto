#include "stm32g4xx_hal.h"
#include "servoMoteur.h"

int main(int argc, char const *argv[])
{
    HAL_Init();  // Initialisation de la HAL

    INIT_servo();  // Initialiser le servo

    SET_default_position();  // Position par défaut

    while(1) {
        HAL_Delay(20);  // Attendre 1 seconde

        close_();

        HAL_Delay(20);

        open_();
    }
}

