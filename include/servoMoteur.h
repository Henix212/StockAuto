#ifndef SERVOMOTEUR_H
#define SERVOMOTEUR_H

#include <stdint.h>

#define PERIOD 10               // Période PWM en ms
#define MIN_STEP 60             // Duty cycle minimum (1 ms pour position 0°)
#define MAX_STEP 160            // Duty cycle maximum (2 ms pour position 90°)
#define DEFAULT_POSITION 50    // Duty cycle par défaut (1.5 ms pour position neutre)

void INIT_servo(void);
void SET_position(uint16_t position, char mouvement);
void SET_default_position(void);
void close_(void);
void open_(void);
void hold_(uint32_t position);
uint32_t Read_ADC_Averaged(uint8_t num_samples);
void SET_position_manual(uint16_t position);

#endif // SERVOMOTEUR_H