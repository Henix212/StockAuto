#include "config.h"
#include "servoMoteur.h"
#include "stm32g4_timer.h"

void INIT_servo(void) {
    // Initialiser le timer avec une période de 10 ms
    BSP_TIMER_run_us(TIMER1_ID, PERIOD * 1000, false);

    // Activer le PWM sur le canal 1 avec un duty cycle par défaut
    BSP_TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_1, DEFAULT_POSITION, false, false);
}

void SET_position(uint16_t position, char mouvement) {
    uint16_t step_position = 0;  // Initialize step_position to avoid undefined behavior
    switch (mouvement) {
    case 'c':
        step_position = MIN_STEP;  // Départ à la position minimale
        while (step_position <= position) {
            BSP_TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, step_position);
            step_position++;
            HAL_Delay(10);  // Attendre 10 ms entre chaque incrément
        }
        break;

    case 'o':
        step_position = MAX_STEP;  // Départ à la position maximale
        while (step_position >= position) {
            BSP_TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, step_position);
            step_position--;
            HAL_Delay(10);  // Attendre 10 ms entre chaque décrément
        }
        break;

    default:
        // Si le mouvement est invalide, ne rien faire
        break;
    }
}

void SET_default_position(void) {
    // Position de base (par défaut)
    BSP_TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, DEFAULT_POSITION);
}

void close_(void) {
    // Fermer le servo (aller à la position maximale)
    SET_position(MAX_STEP, 'c');
}

void open_(void) {
    // Ouvrir le servo (aller à la position minimale)
    SET_position(MIN_STEP, 'o');
}