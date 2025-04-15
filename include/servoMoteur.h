#ifndef SERVOMOTEUR_H
#define SERVOMOTEUR_H

#include <stdint.h>

#define DEFAULT_POSITION 0
#define CLOSE_STEP 1
#define OPEN_STEP 2
#define MAX_STEP 90

void INIT_servo(void);
void SET_position(uint16_t position, char mouvement);
void SET_default_position(void);
void close_(void);
void open_(void);

#endif // SERVOMOTEUR_H