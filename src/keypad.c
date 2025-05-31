#include "keypad.h"
#include "main.h"

volatile char last_key = 0;

// Wait for press
static volatile uint8_t pressed_flag = 0;

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

char keypad_getkey(void) {
    while(!pressed_flag) HAL_Delay(25);

    pressed_flag = 0;
    HAL_Delay(50);

    return last_key;
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

                    pressed_flag = 1;
                    
                    last_key = touche;
                }
            }
        }
    }

    // Réarme les lignes
    for (int i = 0; i < 4; i++)
        HAL_GPIO_WritePin(rowPorts[i], rowPins[i], GPIO_PIN_RESET);
}
