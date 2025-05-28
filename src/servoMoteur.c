#include "config.h"
#include "servoMoteur.h"
#include "stm32g4_adc.h"  // Inclure le fichier pour l'ADC
#include "stm32g4_timer.h"

void INIT_servo(void) {
    BSP_ADC_init();  // Initialiser l'ADC ici
    BSP_TIMER_run_us(TIMER1_ID, PERIOD * 1000, false);
    BSP_TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_1, DEFAULT_POSITION, false, false);
}

void SET_position_manual(uint16_t position) {
    // Position manuelle
    if (position >= MIN_STEP && position <= MAX_STEP) {
        BSP_TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, position);
    } else {
        position = DEFAULT_POSITION;  // Si la position est invalide, revenir à la position par défaut
    }
}

void SET_position(uint16_t position, char mouvement) {
    uint16_t step_position = 0;  // Initialize step_position to avoid undefined behavior

    BSP_ADC_init();  // Initialiser l'ADC

    switch (mouvement) {
    case 'c':
        step_position = MIN_STEP;  // Départ à la position minimale
        while (step_position <= position) {
            uint32_t adc_value = Read_ADC_Averaged(10);  // Moyenne sur 10 lectures
            uint32_t voltage_mv = (adc_value * 3300) / 4096;

            if (voltage_mv > 10) {
                hold_(step_position);  // Sortir de la boucle si la valeur ADC dépasse 10 mV
                break;
            }

            BSP_TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, step_position);
            step_position++;
        }
        break;

    case 'o':
        step_position = MAX_STEP;  // Départ à la position maximale
        while (step_position >= position && step_position >= MIN_STEP) {
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

void hold_(uint32_t position) {
    // Maintenir la position actuelle
    BSP_TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, position);
    HAL_Delay(5000);  // Attendre 10 ms pour stabiliser la position
}

uint32_t Read_ADC_Averaged(uint8_t num_samples) {
    uint32_t sum = 0;
    for (uint8_t i = 0; i < num_samples; i++) {
        sum += BSP_ADC_getValue(ADC_1);
        HAL_Delay(1);  // Petite pause entre les lectures
    }
    return sum / num_samples;
}