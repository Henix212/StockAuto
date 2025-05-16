#include "main.h"
#include "keypad.h"

void Error_Handler(void) {
    while (1) {}
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    while (1) {
        char key = keypad_getkey();  // Récupère la touche pressée

        if (key == '1') {
            // 💡 Mets un point d'arrêt ici
            int test = 1;  // tu peux voir "test" dans le débogueur
        }
        else if (key == '2') {
            // 💡 Mets un autre point d'arrêt ici
            int test = 2;
        }
        else if (key == '*') {
            // 💡 Encore un test
            int test = 99;
        }

        HAL_Delay(100);  // petite pause pour éviter répétition
    }
}
