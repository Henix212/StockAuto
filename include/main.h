/**
 * A project to ease the storage of items
 * 
 * @authors StockAuto
 */

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32g4xx_hal.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"
#include "oled.h"
#include "pages.h"
#include "keypad.h"
#include "servo_moteur.h"
#include "driveurs.h"

#include <stdio.h>

// Structures
typedef enum {
    START = 0,
    ACTION,
    LOCKER,
    EXECUTING
} StockAuto_State;

typedef enum StockAuto_Action {
    GRAB = 0,
    PUT
} StockAuto_Action;

/**
 * Functions' prototypes
 */

void StockAuto_Grab(void);
void StockAuto_Put(void);

/* System fonctions by MX */

void Error_Handler(void);
void SystemClock_Config(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
