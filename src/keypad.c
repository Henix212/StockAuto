#include "keypad.h"
#include "main.h"

volatile char last_key = 0;

// Lignes (sorties) 
GPIO_TypeDef* rowPorts[4] = {GPIOA, GPIOA, GPIOB, GPIOB};
uint16_t rowPins[4] = {GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_0, GPIO_PIN_6};

// Colonnes (entrées avec pull-up) 
GPIO_TypeDef* colPorts[4] = {GPIOA, GPIOA, GPIOB, GPIOB};
uint16_t colPins[4] = {GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_4, GPIO_PIN_5};

// Mappage des touches
char keymap[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

int keypad_getkey(void) {
    for (int row = 0; row < 4; row++) {
        // Toutes les lignes à HIGH
        for (int i = 0; i < 4; i++) {
            HAL_GPIO_WritePin(rowPorts[i], rowPins[i], GPIO_PIN_SET);
        }

        // Active la ligne en cours
        HAL_GPIO_WritePin(rowPorts[row], rowPins[row], GPIO_PIN_RESET);

        for (int col = 0; col < 4; col++) {
            if (HAL_GPIO_ReadPin(colPorts[col], colPins[col]) == GPIO_PIN_RESET) {
                HAL_Delay(20);  // anti-rebond

                // Attendre le relâchement
                while (HAL_GPIO_ReadPin(colPorts[col], colPins[col]) == GPIO_PIN_RESET);

                return keymap[row][col];
            }
        }
    }

    return 0;  // aucune touche pressée
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    // Scanner les lignes pour trouver la touche pressée
    for (int row = 0; row < 4; row++) {
        // Mettre toutes les lignes à HIGH
        for (int i = 0; i < 4; i++)
            HAL_GPIO_WritePin(rowPorts[i], rowPins[i], GPIO_PIN_SET);

        // Activer la ligne courante
        HAL_GPIO_WritePin(rowPorts[row], rowPins[row], GPIO_PIN_RESET);

        // Vérifier si la colonne déclenchée est LOW
        for (int col = 0; col < 4; col++) {
            if (colPins[col] == GPIO_Pin) {
                if (HAL_GPIO_ReadPin(colPorts[col], colPins[col]) == GPIO_PIN_RESET) {
                    char touche = keymap[row][col];

                    OLED_PutChar(touche, OLED_FONT_COLOR_COLORED);
                    
                    last_key = touche;
                }
            }
        }
    }

    // Réarme les lignes
    for (int i = 0; i < 4; i++)
        HAL_GPIO_WritePin(rowPorts[i], rowPins[i], GPIO_PIN_RESET);
}
