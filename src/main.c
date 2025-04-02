#include "stm32g4xx_hal.h"
#include "servoMoteur.h"
int main(int argc, char const *argv[])
{
    HAL_Init();  // Initialisation de la HAL

    INIT_servo();

    int position = 0;

    while(1){
        while (position <= 100){
            position += 3;
            SET_position(position);
            HAL_Delay(10);  // Attendre 1 seconde
        }
        HAL_Delay(250);  // Attendre 1 seconde
        position = 0;
        HAL_Delay(2000);
    }
}
