#include <stdint.h>
#include "driveurs.h"
#include "stm32g4xx_hal.h"
#include "stm32g4_gpio.h"



int main(int argc, char const *argv[]) {
    HAL_Init();

    GPIO_config();

    while (1) {
        GPIO_step(500,1,'A');
        HAL_Delay(1000);
        GPIO_step(500,1,'B');
        HAL_Delay(1000);
        GPIO_step(500,0,'A');
        HAL_Delay(1000);
        GPIO_step(100,0,'B');
        HAL_Delay(1000);
    }

    return 0;
}
